#include "frmmain.h"
#include "appinit.h"
#include "head.h"
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppInit::Instance()->start();
    AppInit::Instance()->initStyle(":/qss/psblack.css");
    QPixmap pixmap("timg.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    frmMain w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
