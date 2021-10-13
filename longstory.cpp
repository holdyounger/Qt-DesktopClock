#include "longstory.h"

SouType LongStory::GetSouType(QString str)
{
    if(str == "知乎")
    {
        return ZHIHU;
    }
    else if(str == "句读")
    {
        return JUDOU;
    }
    else if(str == "小红书")
    {
        return XIOAHONGSHU;
    }
    else if(str == "书")
    {
        return BOOK;
    }
    else
    {
        return CUSTOM;
    }
}

TextType LongStory::GetTextType(QString str)
{
    if(str == "彩虹屁")
    {
        return RAINBOWFART;
    }
    else if(str == "情感")
    {
        return EMOTION;
    }
    else if(str == "鸡汤")
    {
        return CHICKENSOUP;
    }
    else if(str == "情话")
    {
        return WHISPERSLOVE;
    }
    else if(str == "三行情书")
    {
        return ThreeQuotationsBook;
    }
    else // 文案
    {
        return COPYWRITE;
    }
}

QStringList LongStory::openFileToReadData()
{
    QFile file(":/Assert/data/one.csv");
    QStringList Data;
    QStringList retList;
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<QStringLiteral("请正确选择csv文件");
    }
    else
    {

        QTextStream * read = new QTextStream(&file);
        Data = read->readAll().split("\n");            //每行以\n区分
        for(int i = 1 ; i < Data.count() - 1 ; i++)               //去掉最后一行空白行
        {
            QStringList strLine = Data.at(i).split(",");         //一行中的单元格以，区分
            if(!strLine.at(1).isEmpty())
            {
                STU_WORD stuTemp;
                retList.append(strLine.at(1));
                stuTemp.enuTextType = GetTextType(strLine.at(0));
                stuTemp.enuSouType  = GetSouType(strLine.at(2));
                stuTemp.StrCont = strLine.at(1);
                m_StuWord.append(stuTemp);
                stuTemp.clear();
            }
        }
    }

    return retList;
}

LongStory::LongStory()
{

}
