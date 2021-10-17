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
#include <QSpacerItem>
#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QJsonObject>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkAccessManager>
#include <QMap>
#include <QMapIterator>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QJsonDocument>
#include <QPointer>
#include <QColorDialog>
#include <QThread>

#include "http.h"

#endif // GLOBAL_H

#define FILE_PATH_APITOKEN  ":/Config/API.ini"
#define FILE_PATH_COLOR     ":/Config/color.ini"
#define FILE_PATH_FONT      ":/Config/font.ini"
#define FILE_PATH_CONFIG    ":/Config/config.txt"

enum SHOWSOUCETYPE {
    LOCAL = 1,
    YIYAN,
    POETRY
};

enum FONTTYPE {
    HYShangWeiShouShuW = 0,
    SimSun,
    SimHei,
    Microsoft_YaHei,
    Microsoft_JhengHei,
    NSimSun,
    PMingLiU,
    MingLiU,
    DFKai_SB,
    FangSong,
    KaiTi,
    FangSong_GB2312,
    KaiTi_GB2312,
    LiSu,
    YouYuan,
    STXihei,
    STKaiti,
    STSong,
    STZhongsong,
    STFangsong,
    FZShuTi,
    FZYaoti,
    STCaiyun,
    STHupo,
    STLiti,
    STXingkai,
    STXinwei
};

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
