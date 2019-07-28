#ifndef FRMSERIALCONFIG_H
#define FRMSERIALCONFIG_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class frmSerialConfig;
}

class frmSerialConfig : public QWidget
{
    Q_OBJECT

public:
    explicit frmSerialConfig(QWidget *parent = nullptr);
    ~frmSerialConfig();
    void showIPAddr(QString addr);
    void stateChange(int state);
    void stateConnect(QString ip,int port);
    void stateDisconnect();

private slots:
    void on_pbOpenPort_clicked();

    void on_pbClosedPort_clicked();

    void on_pbCreateServer_clicked();

signals:
    void createServer();
    void portStart(QString portname);
    void portClosed();

private:
    Ui::frmSerialConfig *ui;
    QString portName;
};

#endif // FRMSERIALCONFIG_H
