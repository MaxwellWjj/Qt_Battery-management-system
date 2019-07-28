#ifndef RINGSPROGRESSBAR_H
#define RINGSPROGRESSBAR_H

#include <QWidget>
#include <QPainter>

class RingsProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit RingsProgressBar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    void setRange(int range);
    void setProgress(int progress);

private:

    int m_range;
    int m_progress;
    int m_rotateAngle;
};

#endif // RINGSPROGRESSBAR_H
