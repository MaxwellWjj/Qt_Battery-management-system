#include "frmdataplot.h"
#include "ui_frmdataplot.h"
#include <QDebug>
#include "quiwidget.h"
#include "iconfont.h"
#include "appinit.h"

frmDataPlot::frmDataPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmDataPlot)
{
    ui->setupUi(this);
    BatteryPlot = new plotManager(ui->plotwidget, 0, 2);
    isTestMode = 0;

    ui->btnChangeColor->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe6c5, 20, 20, 20));
    ui->btnUnzoom->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xea58, 20, 20, 20));
    ui->btnSaveWave->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xea4a, 20, 20, 20));

    connect(ui->cbIsGridVisible,&QCheckBox::stateChanged,BatteryPlot,&plotManager::showGrid);
    connect(ui->cbIsMinorGridVisible,&QCheckBox::stateChanged,BatteryPlot,&plotManager::showMinorGrid);
    connect(ui->cbIsDarkBackground,&QCheckBox::stateChanged,BatteryPlot,&plotManager::darkBackground);
    connect(ui->cbIsWaveVisible,&QCheckBox::stateChanged,BatteryPlot,&plotManager::on_ch1_visible_changed);
    connect(ui->cbTestMode,&QCheckBox::stateChanged,this,&frmDataPlot::TestMode);
    connect(ui->btnUnzoom,&QPushButton::pressed,BatteryPlot,&plotManager::unzoom);
}

frmDataPlot::~frmDataPlot()
{
    delete BatteryPlot;
    delete ui;
}

void frmDataPlot::UpdatePlotData(qreal data){
    BatteryPlot->updateData_Common(data);
}

void frmDataPlot::UpdatePlotData_TestMode(){
    BatteryPlot->updateData_TestMode();
}

void frmDataPlot::TestMode(int state){
    if(state == 2){
        isTestMode = 1;
    }
    else {
        isTestMode = 0;
    }
    emit modeChanged(isTestMode);
}

void frmDataPlot::on_btnChangeColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if(color.isValid()){
        BatteryPlot->changeColor(color);
    }
}
