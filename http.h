#ifndef HTTP_H
#define HTTP_H
#include "global.h"

class Http : public QObject
{
    Q_OBJECT
public:
   Http();

   static bool post_sync(QString url,QMap<QString,QString> header,QByteArray &requestData,QByteArray& replyData);
   static bool get_sync(QString url, QByteArray& replyData, QMap<QString, QString> header);
};

#endif // HTTP_H
