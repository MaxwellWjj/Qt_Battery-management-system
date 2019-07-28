#include "frmconfig.h"
#include "ui_frmconfig.h"
#include "quiwidget.h"
#include "iconfont.h"

frmConfig::frmConfig(QWidget *parent) : QWidget(parent), ui(new Ui::frmConfig)
{
    ui->setupUi(this);
    Battery_WidgetI = new frmDataPlot;
    Battery_WidgetII = new frmDataPlot;
    Battery_WidgetIII = new frmDataPlot;
    Battery_WidgetIV = new frmDataPlot;
    Battery_WidgetV = new frmDataPlot;
    Battery_WidgetVI = new frmDataPlot;
    Battery_WidgetVII = new frmDataPlot;

    for (int i = 0; i < 7; i ++) {
        IsUltrasoundTestmode.append(0);
    }
    this->initForm();
    this->initNav();
    this->initIcon();
    connect(Battery_WidgetI,&frmDataPlot::modeChanged,this,&frmConfig::changeTestModeState);
    connect(Battery_WidgetII,&frmDataPlot::modeChanged,this,&frmConfig::changeTestModeState);
    connect(Battery_WidgetIII,&frmDataPlot::modeChanged,this,&frmConfig::changeTestModeState);
    connect(Battery_WidgetIV,&frmDataPlot::modeChanged,this,&frmConfig::changeTestModeState);
    connect(Battery_WidgetV,&frmDataPlot::modeChanged,this,&frmConfig::changeTestModeState);
    connect(Battery_WidgetVI,&frmDataPlot::modeChanged,this,&frmConfig::changeTestModeState);
    connect(Battery_WidgetVII,&frmDataPlot::modeChanged,this,&frmConfig::changeTestModeState);

}

frmConfig::~frmConfig()
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

void frmConfig::initForm()
{
    ui->widgetLeft->setProperty("flag", "btn");
    ui->widgetLeft->setFixedWidth(150);
}

void frmConfig::initNav()
{
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

void frmConfig::initIcon()
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

void frmConfig::buttonClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    int index = btns.indexOf(btn);
    ui->stackedWidget->setCurrentIndex(index);

    //取消其他按钮选中
    foreach (QPushButton *b, btns) {
        b->setChecked(b == btn);
    }
}

void frmConfig::updateData(qreal battery1,qreal battery2,qreal battery3,qreal battery4,qreal battery5,qreal battery6,qreal battery7){
    if(IsUltrasoundTestmode.at(0)==0){
        Battery_WidgetI->UpdatePlotData(battery1);
    }
    else {
        Battery_WidgetI->UpdatePlotData_TestMode();
    }
    if(IsUltrasoundTestmode.at(1)==0){
        Battery_WidgetII->UpdatePlotData(battery2);
    }
    else {
        Battery_WidgetII->UpdatePlotData_TestMode();
    }
    if(IsUltrasoundTestmode.at(2)==0){
        Battery_WidgetIII->UpdatePlotData(battery3);
    }
    else {
        Battery_WidgetIII->UpdatePlotData_TestMode();
    }
    if(IsUltrasoundTestmode.at(3)==0){
        Battery_WidgetIV->UpdatePlotData(battery4);
    }
    else {
        Battery_WidgetIV->UpdatePlotData_TestMode();
    }
    if(IsUltrasoundTestmode.at(4)==0){
        Battery_WidgetV->UpdatePlotData(battery5);
    }
    else {
        Battery_WidgetV->UpdatePlotData_TestMode();
    }
    if(IsUltrasoundTestmode.at(5)==0){
        Battery_WidgetVI->UpdatePlotData(battery6);
    }
    else {
        Battery_WidgetVI->UpdatePlotData_TestMode();
    }
    if(IsUltrasoundTestmode.at(6)==0){
        Battery_WidgetVII->UpdatePlotData(battery7);
    }
    else {
        Battery_WidgetVII->UpdatePlotData_TestMode();
    }
}

void frmConfig::changeTestModeState(int state){
    frmDataPlot* plot = (frmDataPlot*) sender();
    if(plot == Battery_WidgetI){
        IsUltrasoundTestmode[0] = state;
    }
    if(plot == Battery_WidgetII){
        IsUltrasoundTestmode[1] = state;
    }
    if(plot == Battery_WidgetIII){
        IsUltrasoundTestmode[2] = state;
    }
    if(plot == Battery_WidgetIV){
        IsUltrasoundTestmode[3] = state;
    }
    if(plot == Battery_WidgetV){
        IsUltrasoundTestmode[4] = state;
    }
    if(plot == Battery_WidgetVI){
        IsUltrasoundTestmode[5] = state;
    }
    if(plot == Battery_WidgetVII){
        IsUltrasoundTestmode[6] = state;
    }
}
