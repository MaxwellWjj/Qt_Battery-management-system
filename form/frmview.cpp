#include "frmview.h"
#include "ui_frmview.h"
#include "quiwidget.h"

frmView::frmView(QWidget *parent) : QWidget(parent), ui(new Ui::frmView)
{
    ui->setupUi(this);
    this->initForm();
    this->initNav();
}

frmView::~frmView()
{
    delete ui;
}

void frmView::initForm()
{

}

void frmView::initNav()
{
    QList<QString> texts;
    texts << "数据监控" << "电压监控" << "电流监控";

    //这里临时用qlabel加粗显示,可以改成自己的widget窗体
    QString qss = "font:80pt;";
    for (int i = 0; i < texts.count(); i++) {
        QLabel *lab = new QLabel;
        lab->setAlignment(Qt::AlignCenter);
        lab->setText(texts.at(i));
        lab->setStyleSheet(qss);
        lab->setAutoFillBackground(true);
        ui->stackedWidget->addWidget(lab);
    }
}

void frmView::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
