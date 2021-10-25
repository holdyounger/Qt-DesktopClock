QT       += core gui sql widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GLOBAL/global.cpp \
    GLOBAL/http.cpp \
    UI/widget.cpp \
    global.cpp \
    global.cpp \
    http.cpp \
    http.cpp \
    longstory.cpp \
    main.cpp \
    widget.cpp \
    widget.cpp

HEADERS += \
    GLOBAL/global.h \
    GLOBAL/http.h \
    UI/widget.h \
    global.h \
    global.h \
    http.h \
    http.h \
    longstory.h \
    widget.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    Assert/data/one.csv \
    Assert/data/one1.csv \
    Assert/font/HYShangWeiShouShuW.ttf \
    Assert/img/Action/LCD.ico \
    Assert/img/Action/about.ico \
    Assert/img/Action/add.ico \
    Assert/img/Action/autocolor.ico \
    Assert/img/Action/customcolor.ico \
    Assert/img/Action/down.ico \
    Assert/img/Action/downhover.ico \
    Assert/img/Action/font.ico \
    Assert/img/Action/spindown.ico \
    Assert/img/Action/start.ico \
    Assert/img/Action/stop.ico \
    Assert/img/Action/switch.ico \
    Assert/img/Action/time.ico \
    Assert/img/Action/up.ico \
    Assert/img/Action/uphover.ico \
    Assert/img/Logo.ico \
    Assert/img/Logo.jpg \
    Assert/qss/main.qss \
    Assert/qss/style1.qss \
    Config/API.ini \
    Config/color.ini \
    Config/config.txt \
    Config/font.ini \
    LICENSE \
    ReadMe.md \
    setting.rc

RESOURCES += \
    qrc.qrc \
    qrc.qrc

RC_FILE = \
    setting.rc

# UAC
