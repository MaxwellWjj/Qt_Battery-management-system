/*
    类：showPointPosition
    基类：QGraphicsItem
    描述：显示曲线上点的坐标位置
    使用：构造对象，配置好public里面的两个set方法后使用updateGraphics()方法更新
*/

#ifndef POINTPOSITION_H
#define POINTPOSITION_H

#include <QGraphicsItem>
#include <QChartGlobal>
#include <QFont>
#include <QChart>
#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QtGlobal>

///声明命名空间
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QtChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class showPointPosition : public QGraphicsItem
{
public:
    showPointPosition(QChart* parent);

    void setText(const QString& text);  //设置文字以及绘图框
    void setAnchor(QPointF point);  //设置鼠标位置
    void updateGraphics();  //更新绘图区

    ///改写基类QGraphicsItem的两个虚函数
    /// QRectF boundingRect()
    /// void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* parent)
    /// 图形-视图框架，自定义图形时一定要完成这个工作
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QString text;   //显示框中的文字
    QRectF textRect;    //显示框文字区域
    QRectF rect;    //图像显示框区域
    QPointF anchor; //鼠标位置
    QFont font; //字体
    QChart *chart;  //接收形参中的Qchart对象
};

#endif // POINTPOSITION_H
