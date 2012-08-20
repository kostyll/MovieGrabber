#include "JSON.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QStringList>
#include <QDebug>
#include <QEventLoop>
#include <QFile>
#include <QMap>

struct JSONData
{
    JSONData() : isParsingFinished(false) {}

    QNetworkAccessManager *netMan;
    QMap<int,QString> valueMap;
    QMap<int,QString> configsValueMap;
    bool isParsingFinished;

    QString fileData;
    QString url;
};

JSON& JSON::instance()
{
    static JSON theInstance;
    return theInstance;
}

JSON::JSON() :
    QObject()
{
    d = new JSONData;
}

JSON::~JSON()
{
    delete d;
}

void JSON::parse(const QString& url)
{
    d->isParsingFinished = false;
    d->netMan = new QNetworkAccessManager;
    d->netMan->get(QNetworkRequest(QUrl(url)));
    d->url = url;

    connect(d->netMan, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkReplyFinished(QNetworkReply*)));
}

void JSON::storeConfigs()
{
    if(!d->isParsingFinished)
    {
        QEventLoop pause;
        connect(d->netMan, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
        pause.exec();
    }

    d->configsValueMap = d->valueMap;
}

QString JSON::value(const int &id, const QString &key, JSON::ValueMode mode) const
{
    if(!d->isParsingFinished)
    {
        QEventLoop pause;
        connect(d->netMan, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
        pause.exec();
    }
    QString string;
    if(mode == JSON::Normal)
        string = d->valueMap.value(id);
    else if(mode == JSON::Configs)
        string = d->configsValueMap.value(id);

    QStringList stringList = string.split(",");
    Q_FOREACH(QString str, stringList)
    {
        str.remove("{");
        if(str.startsWith("\""))
                    str = str.mid(1);

        if(str.startsWith(key+"\""))
        {
            QString returnStr;
            if(str.startsWith(key+"\""+":"))
                returnStr = str.remove(key+"\""+":");
            else
                returnStr = str.remove(key+"\""+":");

            if(returnStr.startsWith("\""))
                returnStr = returnStr.mid(1);

            if(returnStr.endsWith("\""))
                returnStr.chop(1);

            return returnStr.trimmed();
        }
    }

    return QString();
}

int JSON::valueCount(JSON::ValueMode mode) const
{
    if(!d->isParsingFinished)
    {
        QEventLoop pause;
        connect(d->netMan, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
        pause.exec();
    }

    if(mode == JSON::Normal)
        return d->valueMap.count();
    else if(mode == JSON::Configs)
        return d->configsValueMap.count();

    return -1;
}


// Only for configs.json
int JSON::localIndexOfKey(const QString &key)
{
    if(!d->isParsingFinished)
    {
        QEventLoop pause;
        connect(d->netMan, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
        pause.exec();
    }

    int valueCount = this->valueCount(JSON::Configs);
    for(int i=1; i<=valueCount; i++)
    {
        QString value = this->value(i,"key", JSON::Configs);
        if(value == key)
        {
            return i;
            break;
        }
    }
    return -1;
}

QString JSON::getUrl(const QString &key) const
{
    JSON *that = const_cast<JSON*>(this);
//    that->parse("http://www.sachinworld.com/static/s3rsports/configs.json");
    int index = that->localIndexOfKey(key);
    QString returnStr = value(index,"value", JSON::Configs);
    if(!returnStr.isEmpty())
        return returnStr;
    return QString();
}

void JSON::parseString(const QString& mString)
{
    QString string = mString;
    if(!string.startsWith('[') && string.mid(6).contains("tot"))
        string.remove(0, string.indexOf('['));
    if(!string.endsWith(']') && string.startsWith('['))
    {
        int inde = string.lastIndexOf(']');
        string.remove(inde, string.length()-inde);
    }

    QStringList stringList;
    string.replace("\{\"id", "\\n{\"id");
    stringList = string.split("\\n");

    int i = 1;
    Q_FOREACH(QString str, stringList)
    {
        str = str.simplified();
        if(str == "[")
            continue;
        if(str.isEmpty())
            continue;

        str = str.simplified();
        d->valueMap.insert(i,str);
        i++;
    }

    d->isParsingFinished = true;
    emit parseDone(d->url);
}

QString JSON::mapValue(int index) const
{
    if(!d->isParsingFinished)
    {
        QEventLoop pause;
        connect(d->netMan, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
        pause.exec();
    }

    return d->valueMap.value(index);
}

void JSON::onNetworkReplyFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        d->valueMap.clear();

        QString replyString =  reply->readAll();
        replyString = replyString.simplified();
        d->fileData = replyString;
        this->parseString(replyString);
    }
    else
    {
        d->isParsingFinished = true;
        emit parseDone(d->url);
    }
}
