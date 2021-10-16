#include "widget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // a.setWindowIcon(QIcon(":/Assert/img/Logo.ico"));
    // 设置字体
    //    QFont f("STCaiyun", 30);
    //    a.setFont(f);
    Widget w;
    w.show();
    return a.exec();
}
