#include "frmserialconfig.h"
#include "ui_frmserialconfig.h"

frmSerialConfig::frmSerialConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmSerialConfig)
{
    ui->setupUi(this);
    ui->pbClosedPort->setEnabled(false);
    ui->pbOpenPort->setEnabled(false);
}

frmSerialConfig::~frmSerialConfig()
{
    delete ui;
}

void frmSerialConfig::on_pbOpenPort_clicked()
{
    ui->pbOpenPort->setEnabled(false);
    ui->pbClosedPort->setEnabled(true);
    portName = ui->Portname->text();
    emit portStart(portName);
}

void frmSerialConfig::on_pbClosedPort_clicked()
{
    ui->pbClosedPort->setEnabled(false);
    ui->pbOpenPort->setEnabled(true);
    emit portClosed();
}

void frmSerialConfig::on_pbCreateServer_clicked()
{
    ui->pbOpenPort->setEnabled(true);
    ui->pbCreateServer->setEnabled(false);
    emit createServer();
}

void frmSerialConfig::showIPAddr(QString addr){
    ui->IP_address->setText(addr);
}

void frmSerialConfig::stateChange(int state){
    if(state == 0){
        ui->ServerState->setText(QString("Listen"));
    }
    if(state == 1){
        ui->ServerState->setText(QString("Closed"));
    }
}

void frmSerialConfig::stateConnect(QString ip, int port){
    ui->connectstate->setText(QString("%1,%2").arg(ip).arg(port));
}

void frmSerialConfig::stateDisconnect(){
    ui->connectstate->setText(QString("no connection"));
}
