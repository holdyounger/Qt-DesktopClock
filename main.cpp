#include "widget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 设置字体
//    QFont f("STCaiyun", 30);
//    a.setFont(f);
    Widget w;
    return a.exec();
}
