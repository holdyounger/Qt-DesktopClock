#include "longstory.h"

const QString g_poetryUrl           = "https://v2.jinrishici.com/sentence";
const QString g_yiyanUrl            = "https://v1.hitokoto.cn";
const QString g_poetryGetTokenURL   = "https://v2.jinrishici.com/token";
const QString g_yiyanGetTokenURL    = "https://v2.jinrishici.com/token";
QString g_token;

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

bool LongStory::GetToken(QString strTokenUrl, QString strToken)
{
    bool bRet = false;
    QNetworkRequest request;

    //获取access_token
    QByteArray replyData; // 保存回复信息
    QMap<QString, QString> header;
    header.clear();

    bool result = Http::get_sync(strTokenUrl,replyData,header);
    if(result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();  //应该在fromJson之后判断一下是不是json对象
        if(obj.value("status").toString() == "success")
        {
            g_token = obj.value("data").toString();
            // qDebug() << g_token << endl;
            bRet = true;
        }
        else
        {
            goto _end_;
        }
    }

_end_:
    return bRet;
}

QString LongStory::GetFromLocalFile()
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
        delete read;
    }

    int nRad = getRandomNum(retList.size());

    return retList[nRad];
}

QString LongStory::GetFromYiYanAPI()
{
    QString strRet = NULL;
    QSettings setIni(FILE_PATH_APITOKEN,QSettings::IniFormat);
    QMap<QString,QString> header;
    QByteArray replyData;      // 保存回复信息

    // 1 直接调用API即可
    // 1.2 组装HTTP头部
    header.clear();

    bool result = Http::get_sync(g_yiyanUrl, replyData, header);
    if(result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();  //应该在fromJson之后判断一下是不是json对象
        strRet = obj.value("hitokoto").toString();
        if(strRet.isEmpty())
        {
            strRet = "";
        }
    }

    return strRet;
}

QString LongStory::GetFromPoetryAPI()
{
    QString strRet = NULL;
    QString strSetValue;
    QSettings setIni(FILE_PATH_APITOKEN,QSettings::IniFormat);
    QMap<QString,QString> header;
    QByteArray replyData;      // 保存回复信息

    // 1 获取Token
    // - 1.1 配置文件
    setIni.beginGroup("POETRY");
    g_token = setIni.value("token",QVariant("NULL")).toString();
    setIni.endGroup();

    //qDebug() << "read Value" << ':' << g_token;
    // -1.2 http
    if(g_token.isEmpty())
    {
        GetToken(g_poetryGetTokenURL,g_token);
        setIni.beginGroup("POETRY");
        setIni.setValue("token", g_token);
        setIni.endGroup();
        // qDebug() << "set token success" << g_token ;
    }

    // 2 组装HTTP头部
    header.insert(QString("X-User-Token").toUtf8(), g_token.toUtf8());
    bool result = Http::get_sync(g_poetryUrl, replyData, header);
    if(result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();  //应该在fromJson之后判断一下是不是json对象
        if(obj.value("status").toString() == "success")
        {
            QJsonObject dataObj = obj.value("data").toObject();
            strRet = dataObj.value("content").toString();
            // qDebug() << g_token << endl;
        }
    }

    return strRet;
}

QString LongStory::GetOne(SHOWSOUCETYPE enuType)
{
    QString strOne;

    switch (enuType) {
    case LOCAL:
        strOne = GetFromLocalFile();
        break;
    case YIYAN:
        strOne = GetFromYiYanAPI();
        break;
    case POETRY:
        strOne = GetFromPoetryAPI();
        break;
    default:
        strOne = GetFromLocalFile();
    }

    if(strOne.isEmpty())
    {
        strOne = QString::fromLocal8Bit("哎呀~,出错了……\n请尝试切换源");
    }
    return strOne;
}

LongStory::LongStory()
{

}
