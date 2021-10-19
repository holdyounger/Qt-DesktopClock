#include "global.h"
#include <QDebug>

Global::Global()
{

}

QString Global::GetFont()
{
    QSettings settings(":/Config/font.ini",
                       QSettings::IniFormat);
    int nCount = settings.value("Font/Number").toInt();
    QString key = QString("Font/Font%1").arg(getRandomNum(nCount));
    QString Font = settings.value(key).toString();
    //qDebug() << Font;
    return Font;
}

QString Global::GetColor()
{
    QSettings settings(":/Config/color.ini",
                       QSettings::IniFormat);
    int nCount = settings.value("Color/Number").toInt();
    QString key = QString("Color/Color%1").arg(getRandomNum(nCount));
    QString Color = settings.value(key,"NULL").toString();
    if(Color == "NULL")
        Color = "Black";
    //qDebug() << Color;
    return Color;
}

int getRandomNum(int n)
{
    // 随机数
    int num;
    // 初始化随机种子数
    qsrand(QTime::currentTime().second() / 10);
    // 调用全局的qrand()函数生成随机数，对10000取余，保证位于10000的范围内
    num=qrand()%n;
    return num;
}

int changeFontSize(int size)
{
    int nRet = 30 - size / ( size > 30  ? 6 : 5);
    if(size > 25 && size <= 30)
        nRet = nRet - 1;
    else if(size > 40)
    {
        nRet++;
    }
    return nRet;
}
