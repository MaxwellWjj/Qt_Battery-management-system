#include "frmvc.h"
#include "ui_frmvc.h"
#include "quiwidget.h"
#include "iconfont.h"

frmVC::frmVC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmVC)
{
    ui->setupUi(this);
    Battery_WidgetI = new frmVCPlot;
    Battery_WidgetII = new frmVCPlot;
    Battery_WidgetIII = new frmVCPlot;
    Battery_WidgetIV = new frmVCPlot;
    Battery_WidgetV = new frmVCPlot;
    Battery_WidgetVI = new frmVCPlot;
    Battery_WidgetVII = new frmVCPlot;

    for (int i = 0; i < 7; i ++) {
        IsVoltageTestmode.append(0);
    }
    for (int i = 0; i < 7; i ++) {
        IsCurrentTestmode.append(0);
    }

    this->initForm();
    this->initNav();
    this->initIcon();

    connect(Battery_WidgetI,&frmVCPlot::modeChanged_Voltage,this,&frmVC::changeVoltageTestModeState);
    connect(Battery_WidgetII,&frmVCPlot::modeChanged_Voltage,this,&frmVC::changeVoltageTestModeState);
    connect(Battery_WidgetIII,&frmVCPlot::modeChanged_Voltage,this,&frmVC::changeVoltageTestModeState);
    connect(Battery_WidgetIV,&frmVCPlot::modeChanged_Voltage,this,&frmVC::changeVoltageTestModeState);
    connect(Battery_WidgetV,&frmVCPlot::modeChanged_Voltage,this,&frmVC::changeVoltageTestModeState);
    connect(Battery_WidgetVI,&frmVCPlot::modeChanged_Voltage,this,&frmVC::changeVoltageTestModeState);
    connect(Battery_WidgetVII,&frmVCPlot::modeChanged_Voltage,this,&frmVC::changeVoltageTestModeState);
    connect(Battery_WidgetI,&frmVCPlot::modeChanged_Current,this,&frmVC::changeCurrentTestModeState);
    connect(Battery_WidgetII,&frmVCPlot::modeChanged_Current,this,&frmVC::changeCurrentTestModeState);
    connect(Battery_WidgetIII,&frmVCPlot::modeChanged_Current,this,&frmVC::changeCurrentTestModeState);
    connect(Battery_WidgetIV,&frmVCPlot::modeChanged_Current,this,&frmVC::changeCurrentTestModeState);
    connect(Battery_WidgetV,&frmVCPlot::modeChanged_Current,this,&frmVC::changeCurrentTestModeState);
    connect(Battery_WidgetVI,&frmVCPlot::modeChanged_Current,this,&frmVC::changeCurrentTestModeState);
    connect(Battery_WidgetVII,&frmVCPlot::modeChanged_Current,this,&frmVC::changeCurrentTestModeState);

}

frmVC::~frmVC()
{
    delete Battery_WidgetI;
    delete Battery_WidgetII;
    delete Battery_WidgetIII;
    delete Battery_WidgetIV;
    delete Battery_WidgetV;
    delete Battery_WidgetVI;
    delete Battery_WidgetVII;
    delete ui;
}

void frmVC::initForm()
{
    ui->widgetLeft->setProperty("flag", "btn");
    ui->widgetLeft->setFixedWidth(150);
}

void frmVC::initNav(){
    QList<QString> texts;
    btns << ui->btnBatteryI << ui->btnBatteryII << ui->btnBatteryIII << ui->btnBatteryIV << ui->btnBatteryV << ui->btnBatteryVI << ui->btnBatteryVII;
    texts << "电 池 1" << "电 池 2" << "电 池 3" << "电 池 4" << "电 池 5" << "电 池 6" << "电 池 7";

    ui->stackedWidget->addWidget(Battery_WidgetI);
    ui->stackedWidget->addWidget(Battery_WidgetII);
    ui->stackedWidget->addWidget(Battery_WidgetIII);
    ui->stackedWidget->addWidget(Battery_WidgetIV);
    ui->stackedWidget->addWidget(Battery_WidgetV);
    ui->stackedWidget->addWidget(Battery_WidgetVI);
    ui->stackedWidget->addWidget(Battery_WidgetVII);

    for (int i = 0; i < btns.count(); i++) {
        QPushButton *btn = (QPushButton *)btns.at(i);
        btn->setIconSize(QSize(30, 20));
        btn->setCheckable(true);
        btn->setText(texts.at(i) + "  ");
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    }

    ui->btnBatteryI->click();
}

void frmVC::initIcon()
{
    //从图形字体库中设置图标
    ui->btnBatteryI->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe708, 20, 30, 20));
    ui->btnBatteryII->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe708, 20, 30, 20));
    ui->btnBatteryIII->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe708, 20, 30, 20));
    ui->btnBatteryIV->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe708, 20, 30, 20));
    ui->btnBatteryV->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe708, 20, 30, 20));
    ui->btnBatteryVI->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe708, 20, 30, 20));
    ui->btnBatteryVII->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe708, 20, 30, 20));
}

void frmVC::buttonClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    int index = btns.indexOf(btn);
    ui->stackedWidget->setCurrentIndex(index);

    //取消其他按钮选中
    foreach (QPushButton *b, btns) {
        b->setChecked(b == btn);
    }
}

void frmVC::updateVoltageData(qreal battery1,qreal battery2,qreal battery3,qreal battery4,qreal battery5,qreal battery6,qreal battery7){
    if(IsVoltageTestmode.at(0) == 0){
        Battery_WidgetI->UpdateVoltagePlotData(battery1);
    }
    else {
        Battery_WidgetI->UpdateVoltagePlotData_TestMode();
    }
    if(IsVoltageTestmode.at(1) == 0){
        Battery_WidgetII->UpdateVoltagePlotData(battery2);
    }
    else {
        Battery_WidgetII->UpdateVoltagePlotData_TestMode();
    }
    if(IsVoltageTestmode.at(2) == 0){
        Battery_WidgetIII->UpdateVoltagePlotData(battery3);
    }
    else {
        Battery_WidgetIII->UpdateVoltagePlotData_TestMode();
    }
    if(IsVoltageTestmode.at(3) == 0){
        Battery_WidgetIV->UpdateVoltagePlotData(battery4);
    }
    else {
        Battery_WidgetIV->UpdateVoltagePlotData_TestMode();
    }
    if(IsVoltageTestmode.at(4) == 0){
        Battery_WidgetV->UpdateVoltagePlotData(battery5);
    }
    else {
        Battery_WidgetV->UpdateVoltagePlotData_TestMode();
    }
    if(IsVoltageTestmode.at(5) == 0){
        Battery_WidgetVI->UpdateVoltagePlotData(battery6);
    }
    else {
        Battery_WidgetVI->UpdateVoltagePlotData_TestMode();
    }
    if(IsVoltageTestmode.at(6) == 0){
        Battery_WidgetVII->UpdateVoltagePlotData(battery7);
    }
    else {
        Battery_WidgetVII->UpdateVoltagePlotData_TestMode();
    }
}

void frmVC::updateCurrentData(qreal battery1,qreal battery2,qreal battery3,qreal battery4,qreal battery5,qreal battery6,qreal battery7){
    if(IsCurrentTestmode.at(0) == 0){
        Battery_WidgetI->UpdateCurrentPlotData(battery1);
    }
    else {
        Battery_WidgetI->UpdateCurrentPlotData_TestMode();
    }
    if(IsCurrentTestmode.at(1) == 0){
        Battery_WidgetII->UpdateCurrentPlotData(battery2);
    }
    else {
        Battery_WidgetII->UpdateCurrentPlotData_TestMode();
    }
    if(IsCurrentTestmode.at(2) == 0){
        Battery_WidgetIII->UpdateCurrentPlotData(battery3);
    }
    else {
        Battery_WidgetIII->UpdateCurrentPlotData_TestMode();
    }
    if(IsCurrentTestmode.at(3) == 0){
        Battery_WidgetIV->UpdateCurrentPlotData(battery4);
    }
    else {
        Battery_WidgetIV->UpdateCurrentPlotData_TestMode();
    }
    if(IsCurrentTestmode.at(4) == 0){
        Battery_WidgetV->UpdateCurrentPlotData(battery5);
    }
    else {
        Battery_WidgetV->UpdateCurrentPlotData_TestMode();
    }
    if(IsCurrentTestmode.at(5) == 0){
        Battery_WidgetVI->UpdateCurrentPlotData(battery6);
    }
    else {
        Battery_WidgetVI->UpdateCurrentPlotData_TestMode();
    }
    if(IsCurrentTestmode.at(6) == 0){
        Battery_WidgetVII->UpdateCurrentPlotData(battery7);
    }
    else {
        Battery_WidgetVII->UpdateCurrentPlotData_TestMode();
    }
}

void frmVC::changeVoltageTestModeState(int state){
    frmVCPlot* plot = (frmVCPlot*)sender();
    if(plot == Battery_WidgetI){
        IsVoltageTestmode[0] = state;
    }
    if(plot == Battery_WidgetII){
        IsVoltageTestmode[1] = state;
    }
    if(plot == Battery_WidgetIII){
        IsVoltageTestmode[2] = state;
    }
    if(plot == Battery_WidgetIV){
        IsVoltageTestmode[3] = state;
    }
    if(plot == Battery_WidgetV){
        IsVoltageTestmode[4] = state;
    }
    if(plot == Battery_WidgetVI){
        IsVoltageTestmode[5] = state;
    }
    if(plot == Battery_WidgetVII){
        IsVoltageTestmode[6] = state;
    }
}

void frmVC::changeCurrentTestModeState(int state){
    frmVCPlot* plot = (frmVCPlot*)sender();
    if(plot == Battery_WidgetI){
        IsCurrentTestmode[0] = state;
    }
    if(plot == Battery_WidgetII){
        IsCurrentTestmode[1] = state;
    }
    if(plot == Battery_WidgetIII){
        IsCurrentTestmode[2] = state;
    }
    if(plot == Battery_WidgetIV){
        IsCurrentTestmode[3] = state;
    }
    if(plot == Battery_WidgetV){
        IsCurrentTestmode[4] = state;
    }
    if(plot == Battery_WidgetVI){
        IsCurrentTestmode[5] = state;
    }
    if(plot == Battery_WidgetVII){
        IsCurrentTestmode[6] = state;
    }
}
