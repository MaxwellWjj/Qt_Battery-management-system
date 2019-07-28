#ifndef FRMVCPLOT_H
#define FRMVCPLOT_H

#include <QWidget>
#include <QColor>
#include <QPalette>

#include "plotmanager.h"

namespace Ui {
class frmVCPlot;
}

class frmVCPlot : public QWidget
{
    Q_OBJECT

public:
    explicit frmVCPlot(QWidget *parent = nullptr);
    ~frmVCPlot();
    void UpdateVoltagePlotData(qreal data);
    void UpdateVoltagePlotData_TestMode();
    void UpdateCurrentPlotData(qreal data);
    void UpdateCurrentPlotData_TestMode();

private slots:
    void VoltageTestMode(int state);
    void CurrentTestMode(int state);

    void on_btnChangeColor_clicked();

    void on_btnChangeColor_2_clicked();

signals:
    void modeChanged_Voltage(int state);
    void modeChanged_Current(int state);

private:
    Ui::frmVCPlot *ui;
    plotManager* BatteryVoltagePlot;
    plotManager* BatteryCurrentPlot;

    int isVoltageTestMode;
    int isCurrentTestMode;
};

#endif // FRMVCPLOT_H
