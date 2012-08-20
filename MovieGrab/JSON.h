#ifndef JSON_H
#define JSON_H

#include <QObject>

class QUrl;
class QNetworkReply;

struct JSONData;
class JSON : public QObject
{
    Q_OBJECT

public:
    static JSON& instance();
    JSON();
    ~JSON();

    enum ValueMode {
        Normal,
        Configs
    };

    Q_INVOKABLE void parse(const QString& url);
    Q_INVOKABLE void storeConfigs();
    Q_INVOKABLE QString value(const int& id, const QString& key, JSON::ValueMode mode = Normal) const;
    Q_INVOKABLE int valueCount(JSON::ValueMode mode = Normal) const;
    Q_INVOKABLE int localIndexOfKey(const QString& key);
    Q_INVOKABLE QString getUrl(const QString& key) const;
    void parseString(const QString& string);
    QString mapValue(int index) const;

private slots:
    void onNetworkReplyFinished(QNetworkReply *reply);

signals:
    void parseDone(QString url);

private:
    JSONData *d;
};

#endif // JSON_H
