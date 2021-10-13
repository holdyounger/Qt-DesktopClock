#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once
#include <QSettings>
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
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QFontDatabase>
#include <QLinearGradient>
#include <QMouseEvent>
#endif // GLOBAL_H

class Global{
private:
    Global();
public:

    static QString GetFont();
    static QString GetColor();

private:
    QSettings m_SetIng;
};

int getRandomNum(int n);
int changeFontSize(int size);
