#include "chartview.h"
#include <QChart>

ChartView::ChartView(QChart* chart, QWidget* parent):
    QChartView(chart, parent),
    isClicking(false),
    x_old(0),y_old(0)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

void ChartView::mousePressEvent(QMouseEvent* event){
    if(event->button()&Qt::LeftButton){
        isClicking = true;
    }else if(event->button()&Qt::RightButton){
        chart()->zoomReset();
    }

    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent* event){
    int x,y;

    if(isClicking){
        if(x_old == 0 && y_old == 0){

        }else{
            x = event->x() - x_old;
            y = event->y() - y_old;
            chart()->scroll(-x,y);
        }
        x_old = event->x();
        y_old = event->y();
        return;
    }
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent* event){
    if(isClicking){
        x_old = 0;
        y_old = 0;
        isClicking = false;
    }
    if (!(event->button() & Qt::RightButton)) {
        QChartView::mouseReleaseEvent(event);
    }
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        keyPressEvent(event);
        break;
    }
}

void ChartView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        chart()->zoom(1.1);
    } else {
        chart()->zoom(10.0/11);
    }

    QChartView::wheelEvent(event);
}
