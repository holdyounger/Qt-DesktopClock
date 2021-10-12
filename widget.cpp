#include "widget.h"
#include "ui_widget.h"
#pragma execution_character_set("utf-8")

Widget::Widget()
{
    InitUI();
    InitStyle();
    InitConnection();
    //m_LCD_Hour->display(1);
    //m_LCD_Min->display(1);

    QString labCont = "“你会爱我如初吗?”\n“不，是与日剧增”";
    m_lab_Text->setText(labCont);
    m_lab_Text->setAlignment(Qt::AlignVCenter | Qt:: AlignHCenter);

    // 设置ico
    setWindowIcon(QIcon(":/Assert/img/Logo.ico"));

    // 设置窗口透明
    // setWindowOpacity(1);
    setAttribute( Qt::WA_TranslucentBackground);

    // 去边框
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

}

Widget::~Widget()
{
}

void Widget::InitUI()
{
    createHorizontalGroupBox();
    createVerticalGroupBox();

    // 获取桌面大小
    QRect screenRect = QApplication::desktop()->screenGeometry();
    int nw = screenRect.width();
    int nh = screenRect.height();

    // 设置位置
    setGeometry(nw-nw / 3 * 2, nh-nh / 3 * 2, nw / 3, nh / 4);
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_vbl_Main);

    setLayout(mainLayout);

    // 设置窗口置顶
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowTitle(tr("OneForYou"));
}

void Widget::BorderRadius()
{
    QBitmap bmp(this->size());

    bmp.fill();

    QPainter p(&bmp);

    p.setPen(Qt::NoPen);

    p.setBrush(Qt::black);

    p.drawRoundedRect(bmp.rect(),20,20);

    setMask(bmp);
}

void Widget::InitStyle(int i)
{
    m_LCD_Hour->setStyleSheet("color: black; font: 18px black;");
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

void Widget::createHorizontalGroupBox()
{
    m_hbl_Time = new QGroupBox;
    QHBoxLayout *layout = new QHBoxLayout;

    m_LCD_Hour = new QLCDNumber;
    //  m_LCD_Min = new QLCDNumber;
    // m_LCD_Sec = new QLCDNumber;

    m_LCD_Hour->setObjectName("LCD_Hour");
    m_LCD_Hour->setDigitCount(8);
    //  m_LCD_Min->setObjectName("LCD_Min");
    //  m_LCD_Sec->setObjectName("LCD_Min");

    // 设置布局
    layout->addWidget(m_LCD_Hour);
    //  layout->addWidget(m_LCD_Min);
    //  layout->addWidget(m_LCD_Sec);

    m_LCD_Hour->setSegmentStyle(QLCDNumber::Filled);
    // m_LCD_Min->setSegmentStyle(QLCDNumber::Filled);
    //  m_LCD_Sec->setSegmentStyle(QLCDNumber::Filled);

    int nw = this->width();
    int nh = this->height();
    m_LCD_Hour->setGeometry(0,0,nw/3,nh/3);
    //    m_LCD_Min->setGeometry(0,0,nw/3,nh/3);
    //    m_LCD_Sec->setGeometry(0,0,nw/3,nh/3);
    m_hbl_Time->setLayout(layout);
}

void Widget::createVerticalGroupBox()
{
    m_vbl_Main = new QGroupBox;
    QVBoxLayout *layout = new QVBoxLayout;

    m_lab_Text = new QLabel;
    m_lab_Text->setObjectName("lab_Text");

    layout->addWidget(m_hbl_Time);
    layout->addWidget(m_lab_Text);
    layout->setSpacing(-1000);
    layout->setStretch(0,5);
    layout->setStretch(1,2);
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

}

void Widget::RefreshTime()
{
    QTime NowTime = QTime::currentTime();
    // qDebug() << NowTime.hour() << ':' << NowTime.minute() << ':' << NowTime.second() << endl;
    QString text=NowTime.toString("hh:mm:ss");
    m_LCD_Hour->display(text);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void Widget::paintEvent(QPaintEvent *e)
{

}

void Widget::enterEvent(QEvent *e)
{
    if(this->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        QBitmap bmp(this->size());

        bmp.fill();

        QPainter p(&bmp);

        p.setPen(Qt::NoPen);

        p.setBrush(Qt::black);

        p.drawRoundedRect(bmp.rect(),20,20);

        setMask(bmp);



    }
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
