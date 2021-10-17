#include "widget.h"
#include "ui_widget.h"
#pragma execution_character_set("utf-8")
#define OBJNAME(x) (QString(#x))

int g_nSwitchDuration;
Widget::Widget()
{
    InitUI();
    InitStyle(0);
    InitConnection();
    InitLoadFont();

    // 初始化变量
    m_bswitch = false;
    m_bActionSwitchColor = true;
    m_enuSourceType = LOCAL;
    m_LCD_color = QColor(0,0,0);
    m_nSetFontSize = 30;
    m_FontColor = "black";
    m_bFontAutoColorSwitch = false;
    g_nSwitchDuration = 10;

    QString labCont = "One For You";
    m_lab_Text->setText(labCont);

    m_fontFamily = "HYShangWeiShouShuW";
    QTimer::singleShot(1000 * g_nSwitchDuration,this,[=]()mutable{
        m_fontFamily = "KaiTi";
    });

    // 设置窗口透明
    setAttribute( Qt::WA_TranslucentBackground);

    // 去边框
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    show();
}

Widget::~Widget()
{

}

void Widget::InitUI()
{
    QFont f("KaiTi", 30);
    setFont(f);

    createHorizontalGroupBox();
    createVerticalGroupBox();

    // 获取桌面大小
    QRect screenRect = QApplication::desktop()->screenGeometry();
    m_nw = screenRect.width();
    m_nh = screenRect.height();

    // 圆角
    BorderRadius();

    // 设置ico
    setWindowIcon(QIcon(":/Assert/img/Logo.ico"));

    // 系统托盘
    InitTrayIcon();

    // 设置位置
    setGeometry(m_nw-m_nw / 3 * 2, m_nh-m_nh / 3 * 2, m_nw / 3, m_nh / 4);
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    setFixedSize(m_nw / 3, m_nh / 4);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    // mainLayout->setObjectName("mainLayout");
    mainLayout->addWidget(m_vbl_Main);

    setLayout(mainLayout);

    // 设置窗口置顶
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowTitle(tr("OneForYou"));
}

/* 设置关于窗体为圆角 */
void Widget::BorderRadius()
{
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),15,15);
    setMask(bmp);
}

void Widget::InitStyle(int i)
{
    m_LCD_Hour->setStyleSheet(" font: 18px black;");
    if(i != 0)
    {
        QFile file(QString(":/Assert/qss/style%1.qss").arg(i));
        file.open(QFile::ReadOnly);
        this->setStyleSheet(file.readAll());
        file.close();
        return;
    }

    // m_LCD_Min->setStyleSheet("color: black; ");
    // m_LCD_Sec->setStyleSheet("color: black; ");

    QFile file(QString(":/Assert/qss/main.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();

}

void Widget::InitTrayIcon()
{
    m_SysTrayIcon = new QSystemTrayIcon(this);
    m_SysTrayIcon->setIcon(QIcon(":/Assert/img/Logo.ico"));
    m_SysTrayIcon->setToolTip("OneForYou");
    m_SysTrayIcon->show();

    m_menu            = new QMenu(this);
    m_action_time     = new QAction(m_menu);
    m_action_source   = new QAction(m_menu);
    m_action_about    = new QAction(m_menu);
    m_action_color    = new QAction(m_menu);
    m_action_exit     = new QAction(m_menu);
    m_action_LCDColor = new QAction(m_menu);
    m_action_font     = new QAction(m_menu);
    m_action_fontColor= new QAction(m_menu);

    m_action_time->setText(QString("更换切换时间"));
    m_action_source->setText(QString("更换源"));
    m_action_about->setText(QString("关于"));
    m_action_color->setText(QString("边框彩带开关"));
    m_action_fontColor->setText(QString("文案字体颜色"));

    m_action_exit->setText(QString("退出"));
    m_action_LCDColor->setText(QString("更改时间颜色"));
    m_action_font->setText(QString("更改文案字体"));

    QMenu *childMenu = new QMenu;
    QAction *auto_fontColor= new QAction(m_action_fontColor);
    QAction *custom_fontColor= new QAction(m_action_fontColor);
    childMenu->addAction(auto_fontColor);
    childMenu->addAction(custom_fontColor);
    auto_fontColor->setIcon(QIcon(":/Assert/img/Action/autocolor.ico"));
    custom_fontColor->setIcon(QIcon(":/Assert/img/Action/customcolor.ico"));

    auto_fontColor->setText(QString("自动更换文案字体"));
    custom_fontColor->setText(QString("自定义文案字体"));
    m_action_fontColor->setMenu(childMenu);


    m_action_time->setIcon(QIcon(":/Assert/img/Action/time.ico"));
    m_action_source->setIcon(QIcon(":/Assert/img/Action/switch.ico"));
    m_action_color->setIcon(QIcon(":/Assert/img/Action/stop.ico"));
    m_action_about->setIcon(QIcon(":/Assert/img/Logo.ico"));
    m_action_LCDColor->setIcon(QIcon(":/Assert/img/Action/LCD.ico"));
    m_action_font->setIcon(QIcon(":/Assert/img/Action/font.ico"));
    m_action_fontColor->setIcon(QIcon(":/Assert/img/Action/LCD.ico"));

    m_menu->addAction(m_action_time);
    m_menu->addAction(m_action_source);
    m_menu->addAction(m_action_font);
    m_menu->addSeparator();
    m_menu->addAction(m_action_color);
    m_menu->addAction(m_action_LCDColor);
    m_menu->addAction(m_action_fontColor);
    m_menu->addSeparator();
    m_menu->addAction(m_action_about);
    m_menu->addAction(m_action_exit);

    connect(auto_fontColor, &QAction::triggered, this, &Widget::slot_autoChangeFontColor);
    connect(custom_fontColor, &QAction::triggered, this, &Widget::slot_customChangeFontColor);
    connect(m_action_font, &QAction::triggered, this, &Widget::slot_changeFont);
    connect(m_action_LCDColor, &QAction::triggered, this, &Widget::slot_switchChangeLCDColor);
    connect(m_action_color, &QAction::triggered, this, &Widget::slot_switchChangeColor);
    connect(m_action_time, &QAction::triggered, this, &Widget::slot_changeTime);
    connect(m_action_source, &QAction::triggered, this, &Widget::slot_changeSource);
    connect(m_action_about, &QAction::triggered, this, &Widget::slot_showAbout);
    connect(m_action_exit, &QAction::triggered, this, &Widget::slot_exit);

    m_SysTrayIcon->setContextMenu(m_menu);
}

void Widget::InitLoadFont()
{
    QFontDatabase::addApplicationFont(":/Assert/font/HYShangWeiShouShuW.ttf");
}

void Widget::createHorizontalGroupBox()
{
    QHBoxLayout *layout = new QHBoxLayout;
    QSpacerItem* vSpacer2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_LCD_Hour = new QLCDNumber;
    m_hbl_Time = new QGroupBox;

    int nw = this->width();
    int nh = this->height();

    m_LCD_Hour->setObjectName("LCD_Hour");
    m_LCD_Hour->setDigitCount(8);
    m_LCD_Hour->setSegmentStyle(QLCDNumber::Flat);
    m_LCD_Hour->setFrameShape(QFrame::HLine);
    m_LCD_Hour->setBackgroundRole(QPalette::Text);

    m_LCD_Hour->setGeometry(0,0,nw,nh);
    m_LCD_Hour->setFixedHeight(this->width()/5);
    //m_LCD_Hour->setFixedWidth(this->width());

    // 设置布局
    layout->addSpacerItem(vSpacer2);
    layout->addWidget(m_LCD_Hour);
    layout->addSpacerItem(vSpacer2);
    layout->setStretch(0,1);
    layout->setStretch(1,10);
    layout->setStretch(2,1);
    layout->setContentsMargins(0, 0, 0, 0);

    m_hbl_Time->setLayout(layout);
}

void Widget::createVerticalGroupBox()
{
    m_vbl_Main = new QGroupBox;
    m_vbl_Main->setObjectName("mainLayout");
    QVBoxLayout *layout = new QVBoxLayout;

    m_lab_Text = new QLabel;
    m_lab_Text->setObjectName("lab_Text");
    m_lab_Text->setWordWrap(true);
    m_lab_Text->adjustSize();
    m_lab_Text->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    m_lab_Text->setAlignment(Qt::AlignVCenter | Qt:: AlignHCenter);

    layout->addWidget(m_hbl_Time);
    layout->addWidget(m_lab_Text);
    layout->setStretch(0,2);
    layout->setStretch(1,1);

    //layout->SetFixedSize();

    m_vbl_Main->setLayout(layout);
}

void Widget::InitConnection()
{
    // 绑定时间
    QTimer *Timer = new QTimer(this);
    Timer->start(1000);
    connect(Timer, &QTimer::timeout, [=]()
    {
        RefreshTime();
    });

    // 绑定颜色时间
    QTimer *colorTimer = new QTimer(this);
    colorTimer->start(1);
    connect(colorTimer, &QTimer::timeout, [=]()
    {
        if(m_bswitch)
        {
            // changeColor();
        }
    });

    // 绑定文案
    QTimer *TimerText = new QTimer(this);
    TimerText->start(1000);
    TimerText->setInterval(1000);
    connect(TimerText, &QTimer::timeout, [=]()
    {
        m_nSwitchStatus--;
        if(m_nSwitchStatus < 0)
        {
            m_nSwitchStatus = 10;
        }
        if(m_nSwitchStatus == 0)
        {
            slot_changeWord();
        }
    });

    connect(m_SysTrayIcon,&QSystemTrayIcon::activated,this, &Widget::slot_activeTray);
    // connect(m_lab_Text, &QLabel:)
}

void Widget::RefreshTime()
{
    QTime NowTime = QTime::currentTime();
    // qDebug() << NowTime.hour() << ':' << NowTime.minute() << ':' << NowTime.second() << endl;
    QString text=NowTime.toString("hh:mm:ss");
    m_LCD_Hour->display(text);
}

void Widget::EnterAnimation(QObject *obj, QRect rect)
{
    // LeaveAnimation(obj,rect);
    // 切换特效
    int nDuration = 500 * 2;

    m_bswitch = false;
    QTimer::singleShot(nDuration,this,[=](){
        m_bswitch = true;
    });

    m_animation= new QPropertyAnimation(obj,"geometry");
    m_animation->setEasingCurve(QEasingCurve::InOutExpo);  // 缓和曲线风格
    m_animation->setDuration(nDuration);
    m_animation->setStartValue(QRect(rect.x()+300, rect.y(), rect.width(), rect.height()));
    //QRect rec = this->geometry();
    //qDebug() << rect.x() << ':' << rect.y() << ':' << rect.width() << ':' << rect.height() << endl;
    m_animation->setEndValue(QRect(rect.x(), rect.y(), rect.width(), rect.height()));
    m_animation->start(QAbstractAnimation::KeepWhenStopped);
    m_animation->deleteLater();
}

void Widget::LeaveAnimation(QObject *obj, QRect rect)
{
    // 切换特效
    int nDuration = 500 * 1;
    m_animation= new QPropertyAnimation(obj,"geometry");
    m_animation->setEasingCurve(QEasingCurve::InOutExpo);  // 缓和曲线风格
    m_animation->setDuration(nDuration);
    m_animation->setStartValue(QRect(rect.x(), rect.y(), rect.width(), rect.height()));
    //QRect rec = this->geometry();
    //qDebug() << rect.x() << ':' << rect.y() << ':' << rect.width() << ':' << rect.height() << endl;
    m_animation->setEndValue(QRect(rect.x() - 300, rect.y(), rect.width(), rect.height()));
    m_animation->start(QAbstractAnimation::KeepWhenStopped);
    m_animation->deleteLater();
}

void Widget::changeColor()
{
    if(m_bActionSwitchColor && this->isVisible())
    {
        QString mainStyle = QString("QGroupBox#mainLayout {border-bottom:2px solid %1;border-top:2px solid %1;padding: 0px;margin: 0px;}QLCDNumber{color:rgb(%2,%3,%4);}")
                .arg(Global::GetColor()).arg(m_LCD_color.red()).arg(m_LCD_color.green()).arg(m_LCD_color.blue());
        m_vbl_Main->setStyleSheet(QString("%1").arg(mainStyle));
    }
}

SHOWSOUCETYPE Widget::getChoicedItem()
{

    QStringList Items;
    Items << tr("本地") << tr("每日一言") << tr("每日诗词");

    bool ok;
    QInputDialog Dialog;
    Dialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    QString item = Dialog.getItem(this, tr("更换一言来源"),
                                  tr("来源:"), Items, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        if(item == "本地")
        {
            return LOCAL;
        }
        else if(item == "每日诗词")
        {
            return POETRY;
        }
        else if(item == "每日一言")
        {
            return YIYAN;
        }
        else
        {
            return LOCAL;
        }
    }
    return LOCAL;
}

QString Widget::getChoicedFont()
{
    QMap<QString,QString> FontMap;
    QSettings setFontIni(":/Config/font.ini",QSettings::IniFormat);
    QStringList Items;

    int nCount = setFontIni.value("Font/Number").toInt();
    for(int i = 1; i <= nCount; i++)
    {
        QString key = setFontIni.value(QString("Font/FontCh%1").arg(i)).toString();
        QString value   = setFontIni.value(QString("Font/FontEng%1").arg(i)).toString();
        Items.append(key);
        FontMap.insert(key,value);
    }

    bool ok;
    QInputDialog Dialog;
    Dialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    QString item = Dialog.getItem(this, tr("更换字体"),
                                  tr(""), Items, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        return FontMap[item];
    }
    else
    {
        return m_fontFamily;
    }
}

void Widget::slot_showWindow()
{
    if(this->isVisible())
    {
        //this->setVisible(true);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
        hide();
    }
    else
    {
        //this->setVisible(false);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        show();
    }
}


void Widget::slot_changeWord()
{
    // qDebug() << this->isVisible();
    if(this->isVisible() == false)
    {
        return;
    }

    LongStory ObjLs;

    // <1>获取文本
    QString StrLCont = ObjLs.GetOne(m_enuSourceType);

    // <2> 获取用户设置
    int nSize = StrLCont.size();
    m_nSetFontSize = changeFontSize(nSize - 2);
    m_lab_Text->setText((StrLCont).replace("\\n","\n"));
    EnterAnimation(m_lab_Text, m_lab_Text->geometry());

    if(g_nSwitchDuration != 0)
    {
        m_nSwitchStatus = g_nSwitchDuration;
    }

    // 判断是否获取错误
    if(StrLCont.contains("请尝试切换"))
    {
        QTimer *timer = new QTimer;
        timer->start(1000);
        int n = 3;
        connect(timer, &QTimer::timeout,[=]()mutable{
            if(n > 0)
            {
                m_lab_Text->setText( QString("%1秒后切换为本地源").arg(n--));
            }
            else
            {
                m_enuSourceType = LOCAL;
                // qDebug() << "切换" ;
                slot_changeWord();
            }
        });
        timer->deleteLater();
    }
}

void Widget::slot_changeTime()
{
    bool ok;
    QInputDialog Dialog;
    Dialog.setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    Dialog.setOption(QInputDialog::UseListViewForComboBoxItems);
    //msgBox.setIcon(QMessageBox::NoIcon);
    //Dialog.setIconPixmap(QPixmap(":/Assert/img/Action/information.png"));
    int nTime = Dialog.getInt(this, tr("更改文案切换时间"),
                              tr("时间(秒):"), 10, 3, 60 * 5, 1, &ok);
    if (ok && nTime != 0)
    {
        g_nSwitchDuration = nTime;
    }


}

void Widget::slot_showAbout()
{
    QString URL = "https://www.yuque.com/docs/share/78da571b-0bd6-428e-93db-b5673b487d30?#%20%E3%80%8AOneForYou%E3%80%8B";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}


void Widget::slot_changeFont()
{
    m_fontFamily = getChoicedFont();
    //slot_changeWord();
}

void Widget::slot_autoChangeFontColor()
{
    m_bFontAutoColorSwitch = true;
    m_FontColor = Global::GetColor();
}

void Widget::slot_customChangeFontColor()
{
    m_bFontAutoColorSwitch = false;
    QColor color = QColorDialog::getColor(Qt::red, this, tr("颜色对话框"), QColorDialog::ShowAlphaChannel);
    m_FontColor = QString("rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue());
}

void Widget::slot_switchChangeColor()
{
    m_bActionSwitchColor = m_bActionSwitchColor ? false : true;
    QString str = m_bActionSwitchColor ? QString(":/Assert/img/Action/stop.ico") : QString(":/Assert/img/Action/start.ico");
    m_action_color->setIcon(QIcon(str));
}

void Widget::slot_switchChangeLCDColor()
{
    m_LCD_color = QColorDialog::getColor(Qt::red, this, tr("颜色对话框"), QColorDialog::ShowAlphaChannel);
}

void Widget::slot_changeSource()
{
    m_enuSourceType = getChoicedItem();
    slot_changeWord();
}

void Widget::slot_exit()
{
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    //msgBox.setIcon(QMessageBox::NoIcon);
    msgBox.setIconPixmap(QPixmap(":/Assert/img/Action/information.png"));
    if (!(msgBox.information(this,tr("One For You"),tr("\t退出程序\t"),tr("√"),tr("×"))))
    {
        exit(0);
    }
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        this->setVisible(false);
    }
}

void Widget::paintEvent(QPaintEvent *e)
{
    QString strStyle = QString::fromUtf8("QLabel#lab_Text{font-size: %1px;font-family:%2;color: %3;}").arg(QString::number(m_nSetFontSize)).arg(m_fontFamily).arg(m_FontColor);
    //qDebug() << strStyle;
    m_lab_Text->setStyleSheet(strStyle);

    if(m_bswitch)
    {
        changeColor();
    }

    if(m_bFontAutoColorSwitch)
    {
        slot_autoChangeFontColor();
    }
}

void Widget::enterEvent(QEvent *e)
{
    //setWindowOpacity(10);
    InitStyle(1);
}

void Widget::leaveEvent(QEvent *e)
{
    InitStyle(0);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *e)
{
    slot_changeWord();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->globalPos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(this->x() + (event->globalX() - m_lastPos.x()),
               this->y() + (event->globalY() - m_lastPos.y()));
    m_lastPos = event->globalPos();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    // 其实这里的mouseReleaseEvent函数可以不用重写
    m_lastPos = event->globalPos();
}

void Widget::slot_activeTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Context:
        //showMenu();
        break;
    case QSystemTrayIcon::DoubleClick:
    {
        break;
    }
    case QSystemTrayIcon::Trigger:
    {
        slot_showWindow();
        break;
    }
    }
}
