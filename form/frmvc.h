#ifndef FRMVC_H
#define FRMVC_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include "frmvcplot.h"

namespace Ui {
class frmVC;
}

class frmVC : public QWidget
{
    Q_OBJECT

public:
    explicit frmVC(QWidget *parent = nullptr);
    ~frmVC();

    void updateVoltageData(qreal battery1,qreal battery2,qreal battery3,qreal battery4,qreal battery5,qreal battery6,qreal battery7);
    void updateCurrentData(qreal battery1,qreal battery2,qreal battery3,qreal battery4,qreal battery5,qreal battery6,qreal battery7);

private:
    Ui::frmVC *ui;
    QList<QPushButton *> btns;
    QVector<int> IsVoltageTestmode;
    QVector<int> IsCurrentTestmode;
    frmVCPlot* Battery_WidgetI;
    frmVCPlot* Battery_WidgetII;
    frmVCPlot* Battery_WidgetIII;
    frmVCPlot* Battery_WidgetIV;
    frmVCPlot* Battery_WidgetV;
    frmVCPlot* Battery_WidgetVI;
    frmVCPlot* Battery_WidgetVII;

private slots:
    void initForm();
    void initNav();
    void initIcon();
    void buttonClicked();
    void changeVoltageTestModeState(int state);
    void changeCurrentTestModeState(int state);

};

#endif // FRMVC_H
