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
    void InitStyle();
    void createHorizontalGroupBox();
    void createVerticalGroupBox();
    void InitConnection();
    void RefreshTime();

private:
    // 重写键盘事件
    void keyPressEvent(QKeyEvent *e);
    // 绘图
    void paintEvent(QPaintEvent *e);
    // 鼠标进入事件
    void enterEvent(QMouseEvent *e);

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



private:
    // Ui::Widget *ui;

};
#endif // WIDGET_H
