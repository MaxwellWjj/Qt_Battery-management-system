#include "frmdata.h"
#include "ui_frmdata.h"
#include "quiwidget.h"
#include "iconfont.h"

frmData::frmData(QWidget *parent) : QWidget(parent), ui(new Ui::frmData)
{
    ui->setupUi(this);
    serialConfig = new frmSerialConfig;
    serverConfig = new frmSystemHelp;
    backPlatformConfig = new frmSystemHelp;
    systemhelp = new frmSystemHelp;
    aboutus = new frmSystemHelp;
    this->initForm();
    this->initNav();
    this->initIcon();
    connect(serialConfig,&frmSerialConfig::createServer,this,&frmData::CreateServer);
    connect(serialConfig,&frmSerialConfig::portStart,this,&frmData::PortStart);
    connect(serialConfig,&frmSerialConfig::portClosed,this,&frmData::PortClose);
}

frmData::~frmData()
{
    delete serialConfig;
    delete serverConfig;
    delete ui;
}

void frmData::initForm()
{
    ui->widgetLeft->setProperty("flag", "btn");
    ui->widgetLeft->setFixedWidth(150);
}

void frmData::initNav()
{
    QList<QString> texts;
    btns << ui->btnNetConfig << ui->btnServerConfig<< ui->btnBackPlatform<< ui->btnSystemHelp << ui->btnAboutUs;
    texts << "网 口 配 置" << "服务器配置" << "后 台 配 置"<< "系 统 帮 助" << "关 于 我 们";
    ui->stackedWidget->addWidget(serialConfig);
    ui->stackedWidget->addWidget(serverConfig);
    ui->stackedWidget->addWidget(backPlatformConfig);
    ui->stackedWidget->addWidget(systemhelp);
    ui->stackedWidget->addWidget(aboutus);

    for (int i = 0; i < btns.count(); i++) {
        QPushButton *btn = (QPushButton *)btns.at(i);
        btn->setIconSize(QSize(30, 20));
        btn->setCheckable(true);
        btn->setText(texts.at(i) + "  ");
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    }

    ui->btnNetConfig->click();
}

void frmData::initIcon()
{
    //从图形字体库中设置图标
    ui->btnNetConfig->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe563, 20, 30, 20));
    ui->btnServerConfig->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe563, 20, 30, 20));
    ui->btnBackPlatform->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe675, 20, 30, 20));
    ui->btnSystemHelp->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe62a, 20, 30, 20));
    ui->btnAboutUs->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xeac4, 20, 30, 20));
}

void frmData::buttonClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    int index = btns.indexOf(btn);
    ui->stackedWidget->setCurrentIndex(index);

    //取消其他按钮选中
    foreach (QPushButton *b, btns) {
        b->setChecked(b == btn);
    }
}

void frmData::showIPAddress(QString addr){
    serialConfig->showIPAddr(addr);
}

void frmData::changeState(int state){
    serialConfig->stateChange(state);
}

void frmData::connectState(QString ip, int port){
    serialConfig->stateConnect(ip,port);
}

void frmData::stateDisconnect(){
    serialConfig->stateDisconnect();
}
