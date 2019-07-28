#ifndef FRMSYSTEMHELP_H
#define FRMSYSTEMHELP_H

#include <QWidget>

namespace Ui {
class frmSystemHelp;
}

class frmSystemHelp : public QWidget
{
    Q_OBJECT

public:
    explicit frmSystemHelp(QWidget *parent = nullptr);
    ~frmSystemHelp();

private:
    Ui::frmSystemHelp *ui;
};

#endif // FRMSYSTEMHELP_H
