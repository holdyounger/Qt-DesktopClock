#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QLCDNumber>
#include <QLineEdit>
#include <QColor>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QString>
#include <QKeyEvent>
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QGroupBox>
#include <QTextEdit>
#include <QPoint>
#include <QFile>
#include <QDir>
#include <QFont>
#include <QBitmap>
#include <QPainter>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QPropertyAnimation>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private:
    void InitUI();
    void BorderRadius();
    void InitStyle(int i);

    void InitTrayIcon();
    void createHorizontalGroupBox();
    void createVerticalGroupBox();
    void InitConnection();
    void RefreshTime();
    void EnterAnimation(QObject *obj);

private:
    // 重写键盘事件
    void keyPressEvent(QKeyEvent *e);
    // 绘图
    void paintEvent(QPaintEvent *e);
    // 鼠标进入事件
    void enterEvent(QEvent *e);
    // 鼠标离开事件
    void leaveEvent(QEvent *e);

private:
    // 拖动事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool isPressedWidget; // 界面移动问题

    // 控件
    QLabel *m_lab_Text;
    QLCDNumber *m_LCD_Hour;
    QLCDNumber *m_LCD_Min;
    QLCDNumber *m_LCD_Sec;

    // 布局相关
    QGroupBox *m_hbl_Time;
    QGroupBox *m_vbl_Main;

    // 窗口拖动
    QPoint m_lastPos;

    // 系统托盘
    QSystemTrayIcon *m_SysTrayIcon;
    QMenu *m_menu;
    QAction *m_action1;
    QAction *m_action2;

    int m_nw;
    int m_nh;
public slots:
    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void showWindow();
    void changeWord();
private:
    // Ui::Widget *ui;

};
#endif // WIDGET_H
