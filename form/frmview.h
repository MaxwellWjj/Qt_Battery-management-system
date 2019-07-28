#ifndef FRMVIEW_H
#define FRMVIEW_H

#include <QWidget>

namespace Ui {
class frmView;
}

class frmView : public QWidget
{
    Q_OBJECT

public:
    explicit frmView(QWidget *parent = 0);
    ~frmView();

private:
    Ui::frmView *ui;

private slots:
    void initForm();
    void initNav();
    void setIndex(int index);
};

#endif // FRMVIEW_H
