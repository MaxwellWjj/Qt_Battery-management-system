#include "appinit.h"
#include "quiwidget.h"

QScopedPointer<AppInit> AppInit::self;
AppInit *AppInit::Instance()
{
    if (self.isNull()) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new AppInit);
        }
    }

    return self.data();
}

AppInit::AppInit(QObject *parent) : QObject(parent)
{
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w = (QWidget *)obj;
    if (!w->property("canMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }

    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}

void AppInit::start()
{
    qApp->installEventFilter(this);

    //设置全局字体
    QUIConfig::IconMain = 0xf108;
    QUIConfig::FontSize = 12;
    QFont font;
    font.setFamily(QUIConfig::FontName);
    font.setPixelSize(QUIConfig::FontSize);
    qApp->setFont(font);

    //设置编码
    QUIHelper::setCode();
    //设置翻译文件
    QUIHelper::setTranslator();
    //初始化随机数种子
    QUIHelper::initRand();
}

void AppInit::initStyle(const QString &styleName)
{
    QFile file(styleName);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        file.close();

        QUIHelper::getQssColor(qss, QUIConfig::TextColor, QUIConfig::PanelColor, QUIConfig::BorderColor, QUIConfig::NormalColorStart,
                               QUIConfig::NormalColorEnd, QUIConfig::DarkColorStart, QUIConfig::DarkColorEnd, QUIConfig::HighColor);

        //追加样式
        QStringList list;

        //主背景
        list.append(QString("QWidget#widgetMain{background:%1;}").arg(QUIConfig::BorderColor));

        //中英文标题字体大小
        list.append(QString("#labLogoCn{font-size:%1px;}#labLogoEn{font-size:%2px;}")
                    .arg(QUIConfig::FontSize + 13).arg(QUIConfig::FontSize + 4));

        //右上角菜单
        list.append(QString("QWidget#widgetMenu>QPushButton{border-radius:0px;padding:0px;margin:1px 1px 2px 1px;}"));

        //视频画面
        bool black = (styleName.contains("black") || styleName.contains("darkblue") || styleName.contains("purple"));
        list.append(QString("QWidget#widgetVideo>QLabel{font-size:%1px;border:2px solid %2;background:%3;}")
                    .arg(QUIConfig::FontSize + 10).arg(QUIConfig::BorderColor).arg(QUIConfig::NormalColorStart));
        list.append(QString("QWidget#widgetVideo>QLabel:focus{border:2px solid %1;background:%2;}")
                    .arg(QUIConfig::HighColor).arg(black ? QUIConfig::NormalColorEnd : QUIConfig::DarkColorStart));

        //画面分割栏
        list.append(QString("QWidget#widgetSplite>QPushButton{background:transparent;border:none;}"));

        //顶部导航按钮,可以自行修改圆角角度
        int topBtnRadius = 20;
        list.append(QString("QWidget#widgetBtn>QPushButton{font-size:%1px;background:transparent;border:none;border-radius:%2px;}")
                    .arg(QUIConfig::FontSize + 3).arg(topBtnRadius));
        list.append(QString("QWidget#widgetBtn>QPushButton:checked,QWidget#widgetBtn>QPushButton:hover{background:%1;border:2px solid %2;}")
                    .arg(QUIConfig::DarkColorEnd).arg(QUIConfig::BorderColor));

        //左侧导航按钮,可以自行修改圆角角度
        int leftBtnRadius = 5;
        list.append(QString("QWidget[flag=\"btn\"]>QPushButton{min-height:%1px;max-height:%1px;}").arg(30));
        list.append(QString("QWidget[flag=\"btn\"]>QPushButton{font-size:%1px;background:transparent;border:none;border-radius:%2px;}")
                    .arg(QUIConfig::FontSize + 3).arg(leftBtnRadius));
        list.append(QString("QWidget[flag=\"btn\"]>QPushButton:checked,QWidget[flag=\"btn\"]>QPushButton:hover{background:%1;border:2px solid %2;}")
                    .arg(QUIConfig::DarkColorEnd).arg(QUIConfig::BorderColor));

        //面板框
        list.append(QString("QFrame[flag=\"btn\"]{background:%1;}").arg(QUIConfig::BorderColor));
        list.append(QString("QFrame[flag=\"btn\"]>QPushButton{font-size:%1px;font-weight:bold;}").arg(QUIConfig::FontSize + 3));

        //翻页导航标签
        list.append(QString("QFrame[flag=\"navlab\"] QLabel{min-height:%1px;max-height:%1px;font:%2px;}").arg(30).arg(QUIConfig::FontSize + 3));

        //字体放大
        list.append(QString("#widgetControl>QLabel{font-size:%1px;}").arg(QUIConfig::FontSize + 12));
        list.append(QString("#widgetControl>QCheckBox::indicator{width:%1px;height:%1px;}").arg(30));

        //左侧导航栏及按钮图标大小
        list.append(QString("QLineEdit#txtCard,QLabel#labTip,QLabel#labCard,QLabel#labTime{font-weight:bold;font-size:%1px;min-height:%2px;qproperty-alignment:AlignCenter;}").arg(QUIConfig::FontSize + 2).arg(28));
        list.append(QString("QWidget[flag=\"navbtn\"] QPushButton,QFrame[flag=\"navbtn\"] QPushButton{qproperty-iconSize:%1px;min-width:%2px;}").arg(18).arg(80));
        list.append(QString("QLCDNumber{background-color:rgb(0,0,0);color:%1;}").arg("yellow"));

        //选项卡
        list.append(QString("QTabWidget::pane{border:0px;}QTabBar::tab{min-width:%1px;min-height:%2px;}").arg(64).arg(20));

        //控件无边框
        list.append(QString("QListView,QTreeView,#widgetLeft>QTableView{border-width:0px;}"));
        list.append(QString("QTreeView{padding:5px 0px 0px 0px;}"));

        //元素间隔
        //list.append(QString("QTableWidget[flag=\"table\"]::item{margin:2px;color:%1;background:%2;}").arg(QUIConfig::TextColor).arg(QUIConfig::DarkColorStart));

        //文本框控件
        //list.append(QString("QTextEdit,QTextEdit:hover,QTextEdit:focus{border-width:0px;border-radius:0px;}"));

        //自定义面板标题控件
        list.append(QString("NavTitle{qproperty-bgColor:%1;qproperty-textColor:%2;qproperty-borderColor:%3;}")
                    .arg(QUIConfig::NormalColorStart).arg(QUIConfig::TextColor).arg(QUIConfig::BorderColor));

        //开关按钮
        list.append(QString("SwitchButton{min-width:62px;max-height:25px;}"));

        //将新增的样式加到统一样式表中
        qss += list.join("");

        qApp->setPalette(QPalette(QUIConfig::PanelColor));
        qApp->setStyleSheet(qss);
    }
}
