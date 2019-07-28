#include "pointposition.h"

showPointPosition::showPointPosition(QChart* chart):
    QGraphicsItem (chart),
    chart(chart)
{

}

QRectF showPointPosition::boundingRect() const{
    QPointF _anchor = mapFromParent(chart->mapToPosition(this->anchor));
    QRectF rect;
    rect.setLeft(qMin(this->rect.left(),_anchor.x()));
    rect.setRight(qMax(this->rect.right(),_anchor.x()));
    rect.setTop(qMin(this->rect.top(),_anchor.y()));
    rect.setBottom(qMax(this->rect.bottom(),_anchor.y()));

    return rect;
}

void showPointPosition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //用painterpath直接添加一组绘图操作
    QPainterPath path;
    path.addRoundedRect(rect, 5, 5);

    QPointF anchor = mapFromParent(chart->mapToPosition(this->anchor));
    if (!rect.contains(anchor)) {
        QPointF point1, point2;

        // 根据鼠标位置与图像的相对位置来构建绘图区
        bool above = anchor.y() <= rect.top();
        bool aboveCenter = anchor.y() > rect.top() && anchor.y() <= rect.center().y();
        bool belowCenter = anchor.y() > rect.center().y() && anchor.y() <= rect.bottom();
        bool below = anchor.y() > rect.bottom();

        bool onLeft = anchor.x() <= rect.left();
        bool leftOfCenter = anchor.x() > rect.left() && anchor.x() <= rect.center().x();
        bool rightOfCenter = anchor.x() > rect.center().x() && anchor.x() <= rect.right();
        bool onRight = anchor.x() > rect.right();

        // 得到rect的另外两个角(鼠标位置为其中一个)，三个角确定画图的矩形
        qreal x = (onRight + rightOfCenter) * rect.width();
        qreal y = (below + belowCenter) * rect.height();
        bool cornerCase = (above && onLeft) || (above && onRight) || (below && onLeft) || (below && onRight);
        bool vertical = qAbs(anchor.x() - x) > qAbs(anchor.y() - y);

        qreal x1 = x + leftOfCenter * 10 - rightOfCenter * 20 + cornerCase * !vertical * (onLeft * 10 - onRight * 20);
        qreal y1 = y + aboveCenter * 10 - belowCenter * 20 + cornerCase * vertical * (above * 10 - below * 20);;
        point1.setX(x1);
        point1.setY(y1);

        qreal x2 = x + leftOfCenter * 20 - rightOfCenter * 10 + cornerCase * !vertical * (onLeft * 20 - onRight * 10);;
        qreal y2 = y + aboveCenter * 20 - belowCenter * 10 + cornerCase * vertical * (above * 20 - below * 10);;
        point2.setX(x2);
        point2.setY(y2);

        path.moveTo(point1);
        path.lineTo(anchor);
        path.lineTo(point2);
        path = path.simplified();
    }

    painter->setBrush(QColor(255, 255, 0));
    painter->drawPath(path);
    painter->drawText(textRect, text);

}

void showPointPosition::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->setAccepted(true);
}

void showPointPosition::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (event->buttons() & Qt::LeftButton){
        setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
}

void showPointPosition::setText(const QString &text){
    this->text = text;
    QFontMetrics metrics(font);
    textRect = metrics.boundingRect(QRect(0, 0, 150, 150), Qt::AlignLeft, text);
    textRect.translate(5, 5);
    prepareGeometryChange();    //改变一个图像的boundingrect之前一定要使用这个函数
    rect = textRect.adjusted(-5,-5,5,5); //文字框往外拉5，变成绘图框
}

void showPointPosition::setAnchor(QPointF point){
    anchor = point;
}

void showPointPosition::updateGraphics(){
    prepareGeometryChange();
    setPos(chart->mapToPosition(anchor) + QPoint(10, -50));
}
