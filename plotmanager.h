#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QObject>
#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVBoxLayout>
#include <QVector>
#include <QtMath>
#include <QColor>

#include "chartview.h"
#include "pointposition.h"

class plotManager : public QObject
{
    Q_OBJECT
public:
    explicit plotManager(QWidget* plotArea, int _ymin, int _ymax, QObject *parent = nullptr);

    ///更新数据
    void updateData_Common(qreal channel_1);
    ///测试模式
    void updateData_TestMode();
    ///清空波形
    void clearPlot();
    ///更改波形颜色
    void changeColor(QColor color);

private:
    QWidget* _plotArea;
    ChartView *chartView;
    QChart *chart;
    showPointPosition *tip;
    QLineSeries* series_ch1;
    QVBoxLayout* plotLayout;

    bool isch1_visible;
    bool isShowGrid;
    bool isShowMinorGrid;
    bool isHovering; //获取鼠标有没有放在数据的上方，有的话返回坐标值并显示
    quint16 count; ///注意这个变量是用在test mode中的

    int ymin;
    int ymax;

    ///波形区域构造
    void constructPlot(QWidget* plotArea);
    ///初始化chart对象
    void initChart();

signals:

public slots:
    void showGrid(int show);
    void showMinorGrid(int show);
    void unzoom();
    void darkBackground(int show);
    void tipSlot(QPointF position, bool isHovering);
    void on_ch1_visible_changed(int show);
};

#endif // PLOTMANAGER_H
