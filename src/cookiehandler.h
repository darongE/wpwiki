#ifndef COOKIEHANDLER_H
#define COOKIEHANDLER_H

#include <QObject>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

#include <iostream>
class CookieHandler : public QObject
{
    Q_OBJECT

public:
    CookieHandler(QObject *parent = nullptr) : QObject(parent)
    {
        mManager = new QNetworkAccessManager(this);

        mManager->setCookieJar(new QNetworkCookieJar(this));
        connect(mManager, SIGNAL(finished(QNetworkRequest*, QNetworkReply*)),
                SLOT(replyFinished(QNetworkRequest*, QNetworkReply*)));
    }


    void sendPostRequest(const QUrl &url, const QByteArray &data)
    {
        mUrl = url;

        QNetworkRequest r(mUrl);
        r.setRawHeader("User-Agent",data);
        mManager->post(r, data);

    }


    virtual ~CookieHandler()
    {
        if (mManager) {
            delete mManager;
            mManager = NULL;
        }
    }

    QNetworkReply* getReply() const
    {
        return mManager->get(QNetworkRequest(mUrl));
    }



private slots:

    //network --> reply
    void replyFinished(QNetworkRequest* request,QNetworkReply *reply)
    {

        if(reply->error() != QNetworkReply::NoError ){
           qWarning() << "ERROR: " << reply->errorString();
            return;
          }
        QByteArray bytecookie = "";

        QList<QNetworkCookie>  wikiCookies = mManager->cookieJar()->cookiesForUrl(mUrl);

        qDebug() << "COOKIES for" << mUrl.host() << wikiCookies;
        for(int i = 0 ; i < wikiCookies.size(); ++i)
          {
              bytecookie += wikiCookies.at(i).toRawForm(QNetworkCookie::NameAndValueOnly);
              bytecookie += ';';
          }

        request->setRawHeader("Cookie", bytecookie );

    }


private:
    QNetworkAccessManager *mManager;
    QUrl mUrl;
};

#endif // COOKIEHANDLER_H
