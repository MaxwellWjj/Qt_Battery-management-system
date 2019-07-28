#include "frmmain.h"
#include "ui_frmmain.h"
#include "quiwidget.h"
#include "iconfont.h"
#include "appinit.h"

#define THRESHOLD 0.03  //判断坏电池的阈值
#define ULTRASOUNDMAX 1.0   //判断SOC的最大值
#define VOLTAGEMAX 3.5 //判断电压最大值

static qreal regressArray[7] = {0.06252,0.40625,0.40625,1.14062,1.14062,1.35937,0.92187};

frmMain::frmMain(QWidget *parent) : QWidget(parent), ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->initForm();
    this->initText();
    this->initNav();
    this->initIcon();
    for (int var = 0; var < 7; var ++) {
        UltraSound.append(0);
        BatteryVoltage.append(0);
        IsBatteryHealthy.append(0);
        BatterySoc.append(0);
    }
    count = 10; //测试soc/soh功能
    state = 0;  //测试balance功能
    QUIHelper::setFormInCenter(this);
    on_btnMenu_Max_clicked();
    //updateTimer = new QTimer(this);
    //updateTimer->start(500);
    //connect(updateTimer,&QTimer::timeout,this,&frmMain::updateUltraSoundWave);
    connect(SystemConfigWidget,&frmData::PortStart,this,&frmMain::PortStart);
    connect(SystemConfigWidget,&frmData::PortClose,this,&frmMain::PortClose);
    connect(SystemConfigWidget,&frmData::CreateServer,this,&frmMain::CreateServer);
    Sleep(1000);
}

frmMain::~frmMain()
{
    delete SystemConfigWidget;
    delete StateViewWidget;
    delete ViewVcWidget;
    delete DataViewWidget;
    //delete updateTimer;
    delete tcpServer;
    delete ui;
}

bool frmMain::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        //双击标题栏最大化
        if (watched == ui->widgetTop) {
            on_btnMenu_Max_clicked();
        }
    }

    return QWidget::eventFilter(watched, event);
}

void frmMain::initForm()
{
    ui->widgetMain->setProperty("form", true);
    ui->widgetTop->setProperty("form", "title");
    ui->widgetTop->setFixedHeight(80);
    ui->bottomWidget->setFixedHeight(25);

    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    ui->widgetTop->installEventFilter(this);
    ui->labLogoBg->installEventFilter(this);

    //设置右上角菜单,图形字体
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QUIConfig::IconMin);
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QUIConfig::IconNormal);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QUIConfig::IconClose);

    //设置底部状态栏
    ui->bottomWidget->setVersion("V201905");
    ui->bottomWidget->setCurrentUserName("吴加隽");
    ui->bottomWidget->setCurrentUserType("管理员");
    ui->bottomWidget->setFontName(QUIConfig::FontName);
    int fontSize = (QUIConfig::FontSize > 12 ? QUIConfig::FontSize - 1 : QUIConfig::FontSize);
    ui->bottomWidget->setFontSize(fontSize);
    ui->bottomWidget->setLineFixedWidth(true);
    ui->bottomWidget->start();

    //添加换肤菜单
    QStringList styleNames;
    styleNames << "银色" << "蓝色" << "浅蓝色" << "深蓝色" << "灰色" << "浅灰色" << "深灰色" << "黑色"
               << "浅黑色" << "深黑色" << "PS黑色" << "黑色扁平" << "白色扁平" << "蓝色扁平" << "紫色" << "黑蓝色" << "视频黑";
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    foreach (QString styleName, styleNames) {
        QAction *action = new QAction(styleName, this);
        connect(action, SIGNAL(triggered(bool)), this, SLOT(initStyle()));
        this->addAction(action);
    }
}

void frmMain::initText()
{
    //从配置文件读取logo名称
    ui->labLogoCn->setText("锂电池超声监测系统");
    ui->labLogoEn->setText("Battery Security System");
    this->setWindowTitle(ui->labLogoCn->text());

    //设置标题+版本+版权
    ui->bottomWidget->setTitle("锂电池超声监测系统");
    ui->bottomWidget->setAuthor("华中科技大学WISCO实验室");
}

void frmMain::initNav()
{
    SystemConfigWidget = new frmData;
    ui->stackedWidget->addWidget(SystemConfigWidget);

    StateViewWidget = new frmBatteryState;
    ui->stackedWidget->addWidget(StateViewWidget);

    ViewVcWidget = new frmVC;
    ui->stackedWidget->addWidget(ViewVcWidget);

    DataViewWidget = new frmConfig;
    ui->stackedWidget->addWidget(DataViewWidget);

    connect(this, SIGNAL(changeStyle()), this, SLOT(initIcon()));
    connect(this, SIGNAL(changeStyle()), ViewVcWidget, SLOT(initIcon()));
    connect(this, SIGNAL(changeStyle()), DataViewWidget, SLOT(initIcon()));

    QList<QString> texts;
    btns << ui->btnSystemConfig << ui->btnViewState << ui->btnViewVC << ui->btnViewData;
    texts << "系统设置" << "状态监控" << "压流监控" << "峰值显示";

    for (int i = 0; i < btns.count(); i++) {
        QPushButton *btn = (QPushButton *)btns.at(i);
        btn->setIconSize(QSize(25, 20));
        btn->setFixedWidth(115);
        btn->setCheckable(true);
        btn->setText(texts.at(i));
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    }

    ui->btnViewData->click();
}

void frmMain::initIcon()
{
    //如果logo图片不存在则隐藏标签,否则显示logo图片
    ui->labLogoBg->setAlignment(Qt::AlignCenter);
    QPixmap pixLogo(QUIHelper::appPath() + "/" + "bg.png");
    if (pixLogo.isNull()) {
        //ui->labLogoBg->setVisible(false);
        //设置图形字体作为logo
        int size = 60;
        ui->labLogoBg->setFixedWidth(size + 20);
        IconFont::Instance()->setIcon(ui->labLogoBg, 0xe6f2, size);
    } else {
        int size = 150;
        ui->labLogoBg->setFixedWidth(size + 20);
        pixLogo = pixLogo.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->labLogoBg->setPixmap(pixLogo);
    }

    //从图形字体库中设置图标
    ui->btnSystemConfig->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe6ca, 20, 20, 20));
    ui->btnViewState->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe602, 20, 20, 20));
    ui->btnViewVC->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe608, 20, 20, 20));
    ui->btnViewData->setIcon(IconFont::Instance()->getPixmap(QUIConfig::TextColor, 0xe61e, 20, 20, 20));
}

void frmMain::updateUltraSound(qreal BatteryI,qreal BatteryII,qreal BatteryIII,qreal BatteryIV,qreal BatteryV,qreal BatteryVI,qreal BatteryVII){
    DataViewWidget->updateData(BatteryI,BatteryII,BatteryIII,BatteryIV,BatteryV,BatteryVI,BatteryVII);
}

void frmMain::updateVoltage(qreal BatteryI,qreal BatteryII,qreal BatteryIII,qreal BatteryIV,qreal BatteryV,qreal BatteryVI,qreal BatteryVII){
    ViewVcWidget->updateVoltageData(BatteryI,BatteryII,BatteryIII,BatteryIV,BatteryV,BatteryVI,BatteryVII);
}

void frmMain::updateCurrent(qreal BatteryI,qreal BatteryII,qreal BatteryIII,qreal BatteryIV,qreal BatteryV,qreal BatteryVI,qreal BatteryVII){
    ViewVcWidget->updateCurrentData(BatteryI,BatteryII,BatteryIII,BatteryIV,BatteryV,BatteryVI,BatteryVII);
}

void frmMain::updateBattertSoc(int SocI, int SocII, int SocIII, int SocIV, int SocV, int SocVI, int SocVII){
    StateViewWidget->Update_Soc(SocI,SocII,SocIII,SocIV,SocV,SocVI,SocVII);
}

void frmMain::buttonClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    if (btn == ui->btnSystemConfig) {
        emit setIndex(0);
        ui->stackedWidget->setCurrentIndex(0);
    } else if (btn == ui->btnViewState) {
        emit setIndex(1);
        ui->stackedWidget->setCurrentIndex(1);
    } else if (btn == ui->btnViewVC) {
        ui->stackedWidget->setCurrentIndex(2);
    } else if (btn == ui->btnViewData) {
        ui->stackedWidget->setCurrentIndex(3);
    }

    //取消其他按钮选中
    foreach (QPushButton *b, btns) {
        b->setChecked(b == btn);
    }
}

void frmMain::initStyle()
{
    QAction *act = (QAction *)sender();
    QString name = act->text();
    QString qssFile = ":/qss/lightblue.css";

    if (name == "银色") {
        qssFile = ":/qss/silvery.css";
    } else if (name == "蓝色") {
        qssFile = ":/qss/blue.css";
    } else if (name == "浅蓝色") {
        qssFile = ":/qss/lightblue.css";
    } else if (name == "深蓝色") {
        qssFile = ":/qss/darkblue.css";
    } else if (name == "灰色") {
        qssFile = ":/qss/gray.css";
    } else if (name == "浅灰色") {
        qssFile = ":/qss/lightgray.css";
    } else if (name == "深灰色") {
        qssFile = ":/qss/darkgray.css";
    } else if (name == "黑色") {
        qssFile = ":/qss/black.css";
    } else if (name == "浅黑色") {
        qssFile = ":/qss/lightblack.css";
    } else if (name == "深黑色") {
        qssFile = ":/qss/darkblack.css";
    } else if (name == "PS黑色") {
        qssFile = ":/qss/psblack.css";
    } else if (name == "黑色扁平") {
        qssFile = ":/qss/flatblack.css";
    } else if (name == "白色扁平") {
        qssFile = ":/qss/flatwhite.css";
    } else if (name == "蓝色扁平") {
        qssFile = ":/qss/flatblue.css";
    } else if (name == "紫色") {
        qssFile = ":/qss/purple.css";
    } else if (name == "黑蓝色") {
        qssFile = ":/qss/blackblue.css";
    } else if (name == "视频黑") {
        qssFile = ":/qss/blackvideo.css";
    }

    AppInit::Instance()->initStyle(qssFile);
    emit changeStyle();
}

void frmMain::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void frmMain::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }

    IconHelper::Instance()->setIcon(ui->btnMenu_Max, max ? QUIConfig::IconNormal : QUIConfig::IconMax);
    this->setProperty("canMove", max);
    max = !max;
}

void frmMain::on_btnMenu_Close_clicked()
{
    this->close();
}

void frmMain::CreateServer(){
    QString addr;
    tcpServer = new TcpServer(this);
    connect(tcpServer,&TcpServer::clientConnected,this,&frmMain::clientConnected);
    connect(tcpServer,&TcpServer::clientDisconnected,this,&frmMain::clientDisconnected);
    connect(tcpServer,&TcpServer::receiveData,this,&frmMain::tcpReadData);
    addr = tcpServer->get_localmachine_ip();
    SystemConfigWidget->showIPAddress(addr);
}

void frmMain::PortStart(QString portname){
    bool isOK;
    quint16 var = quint16(portname.toInt());
    isOK = tcpServer->start(var);
    if(isOK){
        SystemConfigWidget->changeState(0);
    }
}

void frmMain::PortClose(){
    tcpServer->stop();
    SystemConfigWidget->changeState(1);
}

void frmMain::updateUltraSoundWave(){
    updateUltraSound(0,0,0,0,0,0,0);
    updateVoltage(0,0,0,0,0,0,0);
    updateCurrent(0,0,0,0,0,0,0);
    StateViewWidget->Update_Soc(count,count,count,count,count,count,count);
    count ++;
    if(count == 98) count = 10;
}

void frmMain::myReadData(){
    QByteArray buffer, voltage;
    quint8 flagbyte;
    int32_t channelflag;
    //buffer = serial->readAll();
    if(!buffer.isEmpty()){
        if(buffer.size() == 6){
            flagbyte = quint8(buffer.at(1));
            voltage = buffer.mid(2,2);
            channelflag = int32_t(flagbyte);
            if((quint8(buffer.at(0)) == 0xDA) && (quint8(buffer.at(5)) == 0xEF) && (channelflag >= 0) && (channelflag <= 6)){
                qDebug()<<"frame is good"<<endl;
                if(channelflag == 0 || channelflag == 1 || channelflag == 4 || channelflag == 5){
                    UltraSound[channelflag] = qreal(quint8(buffer.at(4))*4.0/256);
                }
                else{
                    UltraSound[channelflag] = qreal(quint8(buffer.at(4))*2.0/256);
                }

                BatteryVoltage[channelflag] = qreal(voltage.toUShort());
                updateUltraSound(UltraSound[0],UltraSound[1],UltraSound[2],UltraSound[3],UltraSound[4],UltraSound[5],UltraSound[6]);
                updateVoltage(BatteryVoltage[0],BatteryVoltage[1],BatteryVoltage[2],BatteryVoltage[3],BatteryVoltage[4],BatteryVoltage[5],BatteryVoltage[6]);
            }
            else {
                qDebug()<<"frame is error"<<endl;
            }
        }

        else {
            qDebug()<<"frame length error"<<endl;
        }
    }
    buffer.clear();
}

void frmMain::clientConnected(const QString &ip, int port){
    SystemConfigWidget->connectState(ip,port);
}

void frmMain::clientDisconnected(){
    SystemConfigWidget->stateDisconnect();
}

void frmMain::tcpReadData(QByteArray data){
    QByteArray buffer = data;
    int i = 0;
    qDebug()<<buffer.toHex()<<endl;
    if(!buffer.isEmpty()){
        if(buffer.size() == 23 && quint8(buffer.at(0)) == 0xDA && quint8(buffer.at(22)) == 0xEF){
            qDebug()<<"frame is good"<<endl;
            for(i = 0; i < 7; i ++){
                BatteryVoltage[i] = qreal(((buffer.at((i+1)*2)*100)+(buffer.at(2*i+1)))/1000.0);
                UltraSound[i] = qreal(quint8(buffer.at(15 + i))*4.0/256);
                BatterySoc[i] = qint32(70+(UltraSound[i]*10/regressArray[i]));
                if(UltraSound[i] < THRESHOLD && IsBatteryHealthy[i] == 1){
                    IsBatteryHealthy[i] = 1;
                    BatterySoc[i] = 0;
                    StateViewWidget->change_Health(i+1,3);
                }
                if(UltraSound[i] < THRESHOLD && IsBatteryHealthy[i] == 0){
                    IsBatteryHealthy[i] = 1;
                    BatterySoc[i] = 0;
                    StateViewWidget->change_Health(i+1,3);
                }
                if(UltraSound[i] >= THRESHOLD && IsBatteryHealthy[i] == 1){
                    IsBatteryHealthy[i] = 0;
                    StateViewWidget->change_Health(i+1,1);
                }
            }
            qDebug()<<UltraSound<<endl;
            qDebug()<<BatterySoc<<endl;
            updateUltraSound(UltraSound[0],UltraSound[1],UltraSound[2],UltraSound[3],UltraSound[4],UltraSound[5],UltraSound[6]);
            updateBattertSoc(BatterySoc[0],BatterySoc[1],BatterySoc[2],BatterySoc[3],BatterySoc[4],BatterySoc[5],BatterySoc[6]);
            updateVoltage(BatteryVoltage[0],BatteryVoltage[1],BatteryVoltage[2],BatteryVoltage[3],BatteryVoltage[4],BatteryVoltage[5],BatteryVoltage[6]);
        }
        else{
            qDebug()<<"frame is error"<<endl;
        }
    }
}

void frmMain::on_pbtest_clicked()
{
    tcpServer->writeData("ER\r\n");
}

void frmMain::on_pbbalance_clicked()
{
    if(state == 0){
        ui->pbbalance->setText("off");
        tcpServer->writeData("on\r\n");
        state = 1;
    }
    if(state == 1){
        ui->pbbalance->setText("on");
        tcpServer->writeData("of\r\n");
        state = 0;
    }
}
