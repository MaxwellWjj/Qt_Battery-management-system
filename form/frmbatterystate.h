#ifndef FRMBATTERYSTATE_H
#define FRMBATTERYSTATE_H

#include <QWidget>

namespace Ui {
class frmBatteryState;
}

class frmBatteryState : public QWidget
{
    Q_OBJECT

public:
    explicit frmBatteryState(QWidget *parent = nullptr);
    ~frmBatteryState();
    void Update_Soc(int battery1,int battery2,int battery3,int battery4,int battery5,int battery6,int battery7);

    void change_Health(int battery, int state); //state = 1: healthy; state = 2: sub_healthy; state = 3:unhealthy

private:
    Ui::frmBatteryState *ui;
};

#endif // FRMBATTERYSTATE_H
