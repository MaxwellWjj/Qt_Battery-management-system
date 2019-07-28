#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

#include "frmview.h"
#include "frmdata.h"
#include "frmconfig.h"
#include "frmvc.h"
#include "frmbatterystate.h"
#include "tcpserver.h"

class QPushButton;

namespace Ui
{
class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = nullptr);
    ~frmMain();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::frmMain *ui;
    QList<QPushButton *> btns;
    frmData *SystemConfigWidget;
    frmBatteryState *StateViewWidget;
    frmVC *ViewVcWidget;
    frmConfig *DataViewWidget;

    //QTimer* updateTimer;
    //QSerialPort* serial;
    TcpServer* tcpServer;
    int count; //测试SOC/SOH功能
    int state; //测试开关均衡功能

    void updateUltraSound(qreal BatteryI,qreal BatteryII,qreal BatteryIII,qreal BatteryIV,qreal BatteryV,qreal BatteryVI,qreal BatteryVII);
    void updateVoltage(qreal BatteryI,qreal BatteryII,qreal BatteryIII,qreal BatteryIV,qreal BatteryV,qreal BatteryVI,qreal BatteryVII);
    void updateCurrent(qreal BatteryI,qreal BatteryII,qreal BatteryIII,qreal BatteryIV,qreal BatteryV,qreal BatteryVI,qreal BatteryVII);
    void updateBattertSoc(int SocI,int SocII,int SocIII,int SocIV,int SocV,int SocVI,int SocVII);

    QVector<qreal> UltraSound;
    QVector<qreal> BatteryVoltage;
    QVector<int> BatterySoc;
    QVector<int> IsBatteryHealthy;  //0-健康; 1-不健康

private slots:
    void initForm();
    void initText();
    void initNav();
    void initIcon();
    void buttonClicked();
    void initStyle();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

    void updateUltraSoundWave();
    void CreateServer();
    void PortStart(QString portname);
    void PortClose();
    void myReadData();
    void tcpReadData(QByteArray data);
    void clientConnected(const QString &ip, int port);
    void clientDisconnected();

    void on_pbtest_clicked();

    void on_pbbalance_clicked();

signals:
    void setIndex(int index);
    void changeStyle();
};

#endif // FRMMAIN_H
