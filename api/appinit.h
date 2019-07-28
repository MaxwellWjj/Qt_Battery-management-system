#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>

class DbCleanThread;

class AppInit : public QObject
{
    Q_OBJECT
public:
    static AppInit *Instance();
    explicit AppInit(QObject *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    static QScopedPointer<AppInit> self;

public slots:
    void start();
    void initStyle(const QString &styleName);

};

#endif // APPINIT_H
