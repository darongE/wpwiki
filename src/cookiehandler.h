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
#include <QString>

#include <iostream>
class CookieHandler : public QObject
{
    Q_OBJECT

public:

    CookieHandler()
    {
        mManager = new QNetworkAccessManager(this);
        mManager->setCookieJar(new QNetworkCookieJar(this));

    }


    void sendSignal(const QUrl url)
    {
        mUrl= url;

        replyFinished();
    }


    void sendPostRequest( const QByteArray &data, int icase )
    {

        QNetworkRequest r(mUrl);
        r.setRawHeader("User-Agent",data);


        if(icase == 1)
        {
           r.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
           r.setRawHeader("Cookie", data );
            request = r;
        }

        request = r;
    }


    void setManagerPost()
    {
        mManager->post(request, mUrl.toString().toUtf8());
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


public Q_SLOTS:

    //network --> reply
    void replyFinished( /*QNetworkReply *reply*/)
    {

//        if(reply->error() != QNetworkReply::NoError ){
//           qWarning() << "ERROR: " << reply->errorString();
//            return;
//          }
        QByteArray bytecookie = "";

        QList<QNetworkCookie>  wikiCookies = mManager->cookieJar()->cookiesForUrl(mUrl);

        qDebug() << "COOKIES for" << mUrl.host() << wikiCookies;
        for(int i = 0 ; i < wikiCookies.size(); ++i)
          {
              bytecookie += wikiCookies.at(i).toRawForm(QNetworkCookie::NameAndValueOnly);
              bytecookie += ';';
          }

       // request->setRawHeader("Cookie", bytecookie );

    }


private:

    QNetworkAccessManager *mManager;
    QNetworkRequest       request;
    QUrl mUrl;
};

#endif // COOKIEHANDLER_H
