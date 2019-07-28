#ifndef FRMCONFIG_H
#define FRMCONFIG_H

#include <QWidget>
#include <QTimer>

#include "frmdataplot.h"

class QPushButton;

namespace Ui {
class frmConfig;
}

class frmConfig : public QWidget
{
    Q_OBJECT

public:
    explicit frmConfig(QWidget *parent = nullptr);
    ~frmConfig();

    void updateData(qreal battery1,qreal battery2,qreal battery3,qreal battery4,qreal battery5,qreal battery6,qreal battery7);

private:
    Ui::frmConfig *ui;
    QList<QPushButton *> btns;
    QVector<int> IsUltrasoundTestmode;
    frmDataPlot* Battery_WidgetI;
    frmDataPlot* Battery_WidgetII;
    frmDataPlot* Battery_WidgetIII;
    frmDataPlot* Battery_WidgetIV;
    frmDataPlot* Battery_WidgetV;
    frmDataPlot* Battery_WidgetVI;
    frmDataPlot* Battery_WidgetVII;

private slots:
    void initForm();
    void initNav();
    void initIcon();
    void buttonClicked();
    void changeTestModeState(int state);
};

#endif // FRMCONFIG_H
