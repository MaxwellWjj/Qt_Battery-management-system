#include "plotmanager.h"
#define DATANUM_INSERT_PERTIME 1

plotManager::plotManager(QWidget* plotArea, int _ymin, int _ymax, QObject *parent) :
    QObject(parent),
    chart(new QChart),
    tip(nullptr)
{
    ymin = _ymin;
    ymax = _ymax;
    constructPlot(plotArea);
    isch1_visible = false;
    isShowGrid = false;
    isShowMinorGrid = false;
    connect(series_ch1, SIGNAL(hovered(QPointF, bool)), this, SLOT(tipSlot(QPointF,bool)));
}

void plotManager::constructPlot(QWidget *plotArea){
    _plotArea = plotArea;
    plotLayout = new QVBoxLayout(_plotArea);
    plotLayout->setContentsMargins(1,1,1,1);
    plotLayout->setSpacing(1);

    //initialize
    initChart();
}

void plotManager::initChart(){
    series_ch1 = new QLineSeries;
    series_ch1->setColor(Qt::blue);

    chart->addSeries(series_ch1);
    chart->createDefaultAxes();
    chart->axisY()->setRange(ymin, ymax);
    chart->axisX()->setRange(0, 100);

    chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 8, QFont::Normal, true));
    chart->axisY()->setTitleFont(QFont("Microsoft YaHei", 8, QFont::Normal, true));
    chart->axisX()->setTitleText("Time/us");
    chart->axisY()->setTitleText("Ultrasonic Amplitude/mV");
    chart->axisX()->setGridLineVisible(false);
    chart->axisY()->setGridLineVisible(false);
    chart->legend()->hide();

    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);   //抗混叠特效
    plotLayout->addWidget(chartView);

}

void plotManager::updateData_TestMode(){
    int i;
    QVector<QPointF> oldData = series_ch1->pointsVector();
    QVector<QPointF> data;

    if(isch1_visible){
        if (oldData.size() < 101) {
            data = series_ch1->pointsVector();
        } else {
            /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
             * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
             * 现在改成使用宏定义了
             */
            for (i = DATANUM_INSERT_PERTIME; i < oldData.size(); ++i) {
                data.append(QPointF(i - DATANUM_INSERT_PERTIME , oldData.at(i).y()));
            }
        }

        qint64 size = data.size();
        /* 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
         * 但为了后面方便插入多个数据，先这样写
         * 目前使用宏定义
         */
        for(i = 0; i < DATANUM_INSERT_PERTIME; ++i){
            data.append(QPointF(i + size, ymax * sin(M_PI * count * 4 / 180)));
        }

        series_ch1->replace(data);

        count++;
    }
}

void plotManager::changeColor(QColor color){
    series_ch1->setColor(color);
}

void plotManager::updateData_Common(qreal channel_1){
    int i;

    //通道一
    QVector<QPointF> oldData_1 = series_ch1->pointsVector();
    QVector<QPointF> data_1;

    if(isch1_visible){
        if (oldData_1.size() < 101) {
            data_1 = series_ch1->pointsVector();
        } else {
            /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
             * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
             * 现在改成使用宏定义了
             */
            for (i = DATANUM_INSERT_PERTIME; i < oldData_1.size(); ++i) {
                data_1.append(QPointF(i - DATANUM_INSERT_PERTIME , oldData_1.at(i).y()));
            }
        }

        qint64 size = data_1.size();

        data_1.append(QPointF(size, qreal(channel_1)));

        series_ch1->replace(data_1);
    }

}

void plotManager::clearPlot(){
    series_ch1->clear();
}

void plotManager::showGrid(int show){
    if(show == 2){
        chart->axisX()->setGridLineVisible(true);
        chart->axisY()->setGridLineVisible(true);
    }
    else {
        chart->axisX()->setGridLineVisible(false);
        chart->axisY()->setGridLineVisible(false);
    }
}

void plotManager::showMinorGrid(int show){
    if(show == 2){
        chart->axisX()->setMinorGridLineVisible(true);
        chart->axisY()->setMinorGridLineVisible(true);

    }
    else {
        chart->axisX()->setMinorGridLineVisible(false);
        chart->axisY()->setMinorGridLineVisible(false);
    }
}

void plotManager::on_ch1_visible_changed(int show){
    if(show == 2){
        isch1_visible = true;
    }
    else {
        isch1_visible = false;
        series_ch1->clear();
    }
}

void plotManager::unzoom(){
    chart->zoomReset();
}

void plotManager::darkBackground(int show){
    if(show == 2) chart->setTheme(QChart::ChartThemeDark);
    else chart->setTheme(QChart::ChartThemeLight);
}

void plotManager::tipSlot(QPointF position, bool isHovering){
    if(tip == nullptr) tip = new showPointPosition(chart);
    if(isHovering){
        tip->setText(QString("X: %1 \nY: %2 ").arg(position.x()).arg(position.y()));
        tip->setAnchor(position);
        tip->setZValue(11);
        tip->updateGraphics();
        tip->show();
    }else{
        tip->hide();
    }
}
