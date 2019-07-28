#include "frmsystemhelp.h"
#include "ui_frmsystemhelp.h"

frmSystemHelp::frmSystemHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmSystemHelp)
{
    ui->setupUi(this);
}

frmSystemHelp::~frmSystemHelp()
{
    delete ui;
}
