#include "frmvcplot.h"
#include "ui_frmvcplot.h"
#include "quiwidget.h"
#include "iconfont.h"
#include "appinit.h"

frmVCPlot::frmVCPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmVCPlot)
{
    ui->setupUi(this);
    BatteryVoltagePlot = new plotManager(ui->plotwidget, -5, 5);
    BatteryCurrentPlot = new plotManager(ui->plotwidget_2, -5, 5);
    isVoltageTestMode = 0;
    isCurrentTestMode = 0;

    ui->btnChangeColor->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe6c5, 20, 20, 20));
    ui->btnUnzoom->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xea58, 20, 20, 20));
    ui->btnSaveWave->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xea4a, 20, 20, 20));
    ui->btnChangeColor_2->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe6c5, 20, 20, 20));
    ui->btnUnzoom_2->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xea58, 20, 20, 20));
    ui->btnSaveWave_2->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xea4a, 20, 20, 20));

    connect(ui->cbIsGridVisible,&QCheckBox::stateChanged,BatteryVoltagePlot,&plotManager::showGrid);
    connect(ui->cbIsMinorGridVisible,&QCheckBox::stateChanged,BatteryVoltagePlot,&plotManager::showMinorGrid);
    connect(ui->cbIsDarkBackground,&QCheckBox::stateChanged,BatteryVoltagePlot,&plotManager::darkBackground);
    connect(ui->cbIsWaveVisible,&QCheckBox::stateChanged,BatteryVoltagePlot,&plotManager::on_ch1_visible_changed);
    connect(ui->cbTestMode,&QCheckBox::stateChanged,this,&frmVCPlot::VoltageTestMode);
    connect(ui->btnUnzoom,&QPushButton::pressed,BatteryVoltagePlot,&plotManager::unzoom);
    connect(ui->cbIsGridVisible_2,&QCheckBox::stateChanged,BatteryCurrentPlot,&plotManager::showGrid);
    connect(ui->cbIsMinorGridVisible_2,&QCheckBox::stateChanged,BatteryCurrentPlot,&plotManager::showMinorGrid);
    connect(ui->cbIsDarkBackground_2,&QCheckBox::stateChanged,BatteryCurrentPlot,&plotManager::darkBackground);
    connect(ui->cbIsWaveVisible_2,&QCheckBox::stateChanged,BatteryCurrentPlot,&plotManager::on_ch1_visible_changed);
    connect(ui->cbTestMode_2,&QCheckBox::stateChanged,this,&frmVCPlot::CurrentTestMode);
    connect(ui->btnUnzoom_2,&QPushButton::pressed,BatteryCurrentPlot,&plotManager::unzoom);
}

frmVCPlot::~frmVCPlot()
{
    delete BatteryCurrentPlot;
    delete BatteryVoltagePlot;
    delete ui;
}

void frmVCPlot::UpdateVoltagePlotData(qreal data){
    BatteryVoltagePlot->updateData_Common(data);
}

void frmVCPlot::UpdateCurrentPlotData(qreal data){
    BatteryCurrentPlot->updateData_Common(data);
}

void frmVCPlot::UpdateVoltagePlotData_TestMode(){
    BatteryVoltagePlot->updateData_TestMode();
}

void frmVCPlot::UpdateCurrentPlotData_TestMode(){
    BatteryCurrentPlot->updateData_TestMode();
}

void frmVCPlot::VoltageTestMode(int state){
    if(state == 2){
        isVoltageTestMode = 1;
    }
    else {
        isVoltageTestMode = 0;
    }
    emit modeChanged_Voltage(isVoltageTestMode);
}

void frmVCPlot::CurrentTestMode(int state){
    if(state == 2){
        isCurrentTestMode = 1;
    }
    else {
        isCurrentTestMode = 0;
    }
    emit modeChanged_Current(isCurrentTestMode);
}

void frmVCPlot::on_btnChangeColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if(color.isValid()){
        BatteryVoltagePlot->changeColor(color);
    }
}

void frmVCPlot::on_btnChangeColor_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if(color.isValid()){
        BatteryCurrentPlot->changeColor(color);
    }
}
