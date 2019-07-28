/*
    类：ChartView
    基类：QChartView
    描述：chart的视图区
    使用：直接初始化即可
*/

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChart>
#include <QChartView>
#include <QRubberBand>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QChart* chart, QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent *event);

private:
    bool isClicking;
    int x_old;
    int y_old;
};

#endif // CHARTVIEW_H
