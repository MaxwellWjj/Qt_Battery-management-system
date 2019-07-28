#include "frmbatterystate.h"
#include "ui_frmbatterystate.h"

frmBatteryState::frmBatteryState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmBatteryState)
{
    ui->setupUi(this);
    ui->health_1->setGreen();
    ui->health_2->setGreen();
    ui->health_3->setGreen();
    ui->health_4->setGreen();
    ui->health_5->setGreen();
    ui->health_6->setGreen();
    ui->health_7->setGreen();
    ui->health_8->setGreen();

}

frmBatteryState::~frmBatteryState()
{
    delete ui;
}

void frmBatteryState::Update_Soc(int battery1, int battery2, int battery3, int battery4, int battery5, int battery6, int battery7){
    ui->soc_1->setValue(battery1);
    ui->soc_2->setValue(battery2);
    ui->soc_3->setValue(battery3);
    ui->soc_4->setValue(battery4);
    ui->soc_5->setValue(battery5);
    ui->soc_6->setValue(battery6);
    ui->soc_7->setValue(battery7);

    ui->battery_1->setValue(battery1);
    ui->battery_2->setValue(battery2);
    ui->battery_3->setValue(battery3);
    ui->battery_4->setValue(battery4);
    ui->battery_5->setValue(battery5);
    ui->battery_6->setValue(battery6);
    ui->battery_7->setValue(battery7);

    ui->waveChart_1->addData(battery1);
    ui->waveChart_2->addData(battery2);
    ui->waveChart_3->addData(battery3);
    ui->waveChart_4->addData(battery4);
    ui->waveChart_5->addData(battery5);
    ui->waveChart_6->addData(battery6);
    ui->waveChart_7->addData(battery7);

}

void frmBatteryState::change_Health(int battery, int state){
    if(battery == 1){
        if(state == 1) {
            ui->health_1->setGreen();
            ui->soc_1->setUsedColor(QColor(100,184,255,255));
        }
        if(state == 2) ui->health_1->setBlue();
        if(state == 3) {
            ui->health_1->setRed();
            ui->soc_1->setUsedColor(Qt::red);
        }
    }
    if(battery == 2){
        if(state == 1) {
            ui->health_2->setGreen();
            ui->soc_2->setUsedColor(QColor(100,184,255,255));
        }
        if(state == 2) ui->health_2->setBlue();
        if(state == 3) {
            ui->health_2->setRed();
            ui->soc_2->setUsedColor(Qt::red);
        }
    }
    if(battery == 3){
        if(state == 1) {
            ui->health_3->setGreen();
            ui->soc_3->setUsedColor(QColor(100,184,255,255));
        }
        if(state == 2) ui->health_3->setBlue();
        if(state == 3) {
            ui->health_3->setRed();
            ui->soc_3->setUsedColor(Qt::red);
        }
    }
    if(battery == 4){
        if(state == 1) {
            ui->health_4->setGreen();
            ui->soc_4->setUsedColor(QColor(100,184,255,255));
        }
        if(state == 2) ui->health_4->setBlue();
        if(state == 3) {
            ui->health_4->setRed();
            ui->soc_4->setUsedColor(Qt::red);
        }
    }
    if(battery == 5){
        if(state == 1) {
            ui->health_5->setGreen();
            ui->soc_5->setUsedColor(QColor(100,184,255,255));
        }
        if(state == 2) ui->health_5->setBlue();
        if(state == 3) {
            ui->health_5->setRed();
            ui->soc_5->setUsedColor(Qt::red);
        }
    }
    if(battery == 6){
        if(state == 1) {
            ui->health_6->setGreen();
            ui->soc_6->setUsedColor(QColor(100,184,255,255));
        }
        if(state == 2) ui->health_6->setBlue();
        if(state == 3) {
            ui->health_6->setRed();
            ui->soc_6->setUsedColor(Qt::red);
        }
    }
    if(battery == 7){
        if(state == 1) {
            ui->health_7->setGreen();
            ui->soc_7->setUsedColor(QColor(100,184,255,255));
        }
        if(state == 2) ui->health_7->setBlue();
        if(state == 3) {
            ui->health_7->setRed();
            ui->soc_7->setUsedColor(Qt::red);
        }
    }

}
