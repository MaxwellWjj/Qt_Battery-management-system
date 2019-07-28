#ifndef FRMDATA_H
#define FRMDATA_H

#include <QWidget>
#include "frmserialconfig.h"
#include "frmsystemhelp.h"

class QPushButton;

namespace Ui {
class frmData;
}

class frmData : public QWidget
{
    Q_OBJECT

public:
    explicit frmData(QWidget *parent = 0);
    ~frmData();
    void showIPAddress(QString addr);
    void changeState(int state);
    void connectState(QString ip,int port);
    void stateDisconnect();

private:
    Ui::frmData *ui;
    QList<QPushButton *> btns;
    frmSerialConfig* serialConfig;
    frmSystemHelp* serverConfig;
    frmSystemHelp* backPlatformConfig;
    frmSystemHelp* systemhelp;
    frmSystemHelp* aboutus;

signals:
    void CreateServer();
    void PortStart(QString name);
    void PortClose();

private slots:
    void initForm();
    void initNav();
    void initIcon();
    void buttonClicked();
};

#endif // FRMDATA_H
