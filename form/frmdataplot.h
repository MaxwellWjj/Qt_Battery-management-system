#ifndef FRMDATAPLOT_H
#define FRMDATAPLOT_H

#include <QWidget>
#include <QTimer>
#include <QPalette>

#include "plotmanager.h"

namespace Ui {
class frmDataPlot;
}

class frmDataPlot : public QWidget
{
    Q_OBJECT

public:
    explicit frmDataPlot(QWidget *parent = nullptr);
    ~frmDataPlot();
    void UpdatePlotData(qreal data);
    void UpdatePlotData_TestMode();

private slots:
    void TestMode(int state);

    void on_btnChangeColor_clicked();

signals:
    void modeChanged(int state);

private:
    Ui::frmDataPlot *ui;
    plotManager* BatteryPlot;

    int isTestMode;
};

#endif // FRMDATAPLOT_H
