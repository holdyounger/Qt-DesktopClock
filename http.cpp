#include "http.h"

Http::Http()
{

}

/*

*/
bool Http::post_sync(QString url, QMap<QString, QString> header, QByteArray &requestData, QByteArray &replyData)
{
    bool bRet;
    QNetworkAccessManager manager;
    QNetworkRequest request;
    QMapIterator<QString,QString> it(header);

    request.setUrl(url);

    while(it.hasNext())
    {
        it.next();
        request.setRawHeader(it.key().toLatin1(),it.value().toLatin1());
    }


    QNetworkReply * reply = manager.post(request,requestData);
    QEventLoop l;
    connect(reply,&QNetworkReply::finished,&l, &QEventLoop::quit);
    l.exec();               // 死循环

    if(reply != nullptr && reply->error() == QNetworkReply::NoError)
    {
        replyData = reply->readAll();
        bRet = true;
    }
    else
    {
        goto _END_;
    }

_END_:
    reply->deleteLater();
    return bRet;
}

bool Http::get_token(QString url, QByteArray &replyData)
{
    bool bRet = false;
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    request.setUrl(url);
    QNetworkReply * reply = manager->get(request);
    QEventLoop l;
    connect(manager,&QNetworkAccessManager::finished,&l, &QEventLoop::quit);
    l.exec();               // 死循环

    if(reply != nullptr && reply->error() == QNetworkReply::NoError)
    {
        replyData = reply->readAll();
        bRet = true;
    }
    else
    {
        goto _END_;
    }

_END_:
    reply->deleteLater();
    delete manager;
    return bRet;
}
