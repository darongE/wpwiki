#include "browsepage.h"
// Qt includes

#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QXmlStreamReader>
#include <QCryptographicHash>
#include <QStringList>

#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "WPMediaWiki.h"
#include "query.h"
#include "work_p.h"
#include "cookiehandler.h"

namespace mediawiki
{

class Result
{
public:
    quint32     m_capchaId;
    QVariant    m_captchaQuestion;
    QString     m_captchaAnswer;
};

class BrowsePagePrivate : public WorkPrivate
{
public:
    BrowsePagePrivate(WPMediaWiki& MediaWiki)
          : WorkPrivate(MediaWiki)

    {

    }

    static int error(const QString& error)
    {
        QString tmp = error;
        int ret     = 0;
        QStringList list;
        list    << QStringLiteral("notext")
                << QStringLiteral("invalidsection")
                << QStringLiteral("protectedtitle")
                << QStringLiteral("cantcreate")
                << QStringLiteral("cantcreateanon")
                << QStringLiteral("articleexists")
                << QStringLiteral("noimageredirectanon")
                << QStringLiteral("noimageredirect")
                << QStringLiteral("spamdetected")
                << QStringLiteral("filtered")
                << QStringLiteral("contenttoobig")
                << QStringLiteral("noeditanon")
                << QStringLiteral("noedit")
                << QStringLiteral("pagedeleted")
                << QStringLiteral("emptypage")
                << QStringLiteral("emptynewsection")
                << QStringLiteral("editconflict")
                << QStringLiteral("revwrongpage")
                << QStringLiteral("undofailure");

        ret = list.indexOf(tmp.remove(QChar::fromLatin1('-')));

        if(ret == -1)
           ret = 0;

        return ret + (int)BrowsePage::TextMissing;

    }

    QUrl                    baseUrl;
    QMap<QString, QString>  requestParam;
    Result                  result;

    CookieHandler           *h_cookie;



};

BrowsePage::BrowsePage(WPMediaWiki& media, QObject* parent)
          : Work(*new BrowsePagePrivate(media),parent)
{

}


BrowsePage::~BrowsePage()
{

}
void BrowsePage::setUndoAfter(int undoafter)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("undoafter")] = QString::number(undoafter);
}

void BrowsePage::setUndo(int undo)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("undo")] = QString::number(undo);

}

void BrowsePage::setPrependText(const QString &prependText)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("prependtext")] = prependText;
    d->requestParam[QStringLiteral("md5")] = QString();

}

void BrowsePage::setAppendText(const QString &appendText)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("appendtext")] = appendText;
    d->requestParam[QStringLiteral("md5")] = QString();

}

void BrowsePage::setPageName(const QString &pageName)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("title")] = pageName;

}

void BrowsePage::setToken(const QString &token)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("token")] = token;

}

void BrowsePage::setBaseTimestamp(const QDateTime &baseTimestamp)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("basetimestamp")] =  baseTimestamp.toString(QStringLiteral("yyyy-MM-ddThh:mm:ssZ"));

}

void BrowsePage::setStartTimestamp(const QDateTime &startTimestamp)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("starttimestamp")] = startTimestamp.toString(QStringLiteral("yyyy-MM-ddThh:mm:ssZ"));
}

void BrowsePage::setText(const QString &text)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("text")] = text;
    d->requestParam[QStringLiteral("md5")] = QString();
}

void BrowsePage::setRecreate(bool recreate)
{
    Q_D(BrowsePage);
    if(recreate)
    {
       d->requestParam[QStringLiteral("recreate")] = QStringLiteral("on");
       d->requestParam[QStringLiteral("md5")] = QString();
    }


}

void BrowsePage::setCreateonly(bool createonly)
{
    Q_D(BrowsePage);
    if(createonly)
    {
        d->requestParam[QStringLiteral("createonly")] = QStringLiteral("on");
        d->requestParam[QStringLiteral("md5")] = QString();
    }
}

void BrowsePage::setNocreate(bool norecreate)
{
    Q_D(BrowsePage);
    if(norecreate)
    {
        d->requestParam[QStringLiteral("nocreate")] = QStringLiteral("on");
        d->requestParam[QStringLiteral("md5")] = QString();
    }
}

void BrowsePage::setMinor(bool minor)
{
    Q_D(BrowsePage);
    if(minor)
        d->requestParam[QStringLiteral("minor")] = QStringLiteral("on");
    else
        d->requestParam[QStringLiteral("notminor")] = QStringLiteral("on");
}

void BrowsePage::setSection(const QString &section)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("section")] = section;
}

void BrowsePage::setSummary(const QString &summary)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("summary")] = summary;
}

void BrowsePage::setWatchList(BrowsePage::Watchlist watchlist)
{
    Q_D(BrowsePage);

    switch(watchlist){

    case BrowsePage::watch:
        d->requestParam[QStringLiteral("watchlist")]= QString(QStringLiteral("watch"));
        break;
    case BrowsePage::unwatch:
        d->requestParam[QStringLiteral("watchlist")] = QString(QStringLiteral("unwatch"));
        break;
    case BrowsePage::nochange:
        d->requestParam[QStringLiteral("watchlist")] = QString(QStringLiteral("nochange"));
        break;
    case BrowsePage::preferences:
        d->requestParam[QStringLiteral("watchlist")] = QString(QStringLiteral("preferences"));
        break;
    }
}

void BrowsePage::start()
{
    Q_D(BrowsePage);
    Query* p_query = new Query(d->m_MediaWiki, this);

            //= new Query(d->m_MediaWiki, this);
    p_query->setPageName(d->requestParam[QStringLiteral("title")]);
    p_query->setToken(QStringLiteral("edit"));
    connect(p_query, SIGNAL(getPage(WikiPage)),
            this, SLOT(sendRequest(WikiPage)));

    p_query->start();

}
//e.g
//www.MediaWiki.org/w/index.php
//?title=Project:Sandbox
//&action=edit
void BrowsePage::sendRequest(WikiPage wiki_page)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("token")] = wiki_page.pageEditToken();

    QUrl    url = d->m_MediaWiki.url();
    QUrlQuery url_query;
    url_query.addQueryItem(QStringLiteral("format"),QStringLiteral("xml"));
    url_query.addQueryItem(QStringLiteral("action"), QStringLiteral("edit"));

    // Add parameter

    if(d->requestParam.contains(QStringLiteral("md5")))
    {
        QString text;
        if(d->requestParam.contains(QStringLiteral("prependtext")))
            text += d->requestParam[QStringLiteral("prependtext")];
        if(d->requestParam.contains(QStringLiteral("appendtext")))
            text += d->requestParam[QStringLiteral("appendtext")];
        if(d->requestParam.contains(QStringLiteral("text")))
            text += d->requestParam[QStringLiteral("text")];


        // prependtext & appendtext : text param
        QByteArray hash = QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Md5);
        d->requestParam[QStringLiteral("md5")] = QString::fromLatin1(hash.toHex());
    }


    QMapIterator<QString, QString> i(d->requestParam);

    while(i.hasNext())
    {
        i.next();
        if(i.key() != QStringLiteral("token"))
            url_query.addQueryItem(i.key(),i.value());


    }


    QByteArray cookie;
    QList<QNetworkCookie> mediawikiCookies = d->mManager->cookieJar()->cookiesForUrl(d->m_MediaWiki.url());
    for(int i = 0 ; i < mediawikiCookies.size(); ++i)
    {
        cookie += mediawikiCookies.at(i).toRawForm(QNetworkCookie::NameAndValueOnly);
        cookie += ';';
    }
    // Add the token
    url_query.addQueryItem(QStringLiteral("token"), d->requestParam[QStringLiteral("token")]);
    url.setQuery(url_query);
    d->baseUrl = url;

    // Set the request
    QNetworkRequest request( url );
    request.setRawHeader("User-Agent", d->m_MediaWiki.userAgent().toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
    request.setRawHeader( "Cookie", cookie );

    setPercent(25); // Request ready.

    // Send the request
    d->reply = d->mManager->post( request, url.toString().toUtf8() );
    connectReply();
    connect( d->reply, SIGNAL(finished()),
             this, SLOT(finishedEdit()) );

    setPercent(50); // Request sent.

}

void BrowsePage::finishedEdit()
{
    Q_D(BrowsePage);
    disconnect(d->reply, SIGNAL(finished()),
               this, SLOT(finishedEdit()));

    setPercent(75);

    if( d->reply->error() != QNetworkReply::NoError)
    {
        this->setError(this->NetworkError);
        d->reply->close();
        d->reply->deleteLater();
        emitResult();

        return;

    }

    QXmlStreamReader reader( d->reply );
    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartElement )
        {
            QXmlStreamAttributes attrs = reader.attributes();

            if(reader.name() == QStringLiteral("edit"))
            {
                if(attrs.value(QStringLiteral("result") ).toString() == QLatin1String("Success"))
                {
                    setPercent(100);
                    this->setError(KJob::NoError);
                    d->reply->close();
                    d->reply->deleteLater();
                    emitResult();
                    return;
                }
                else if( attrs.value(QStringLiteral("result")).toString() == QLatin1String("Failure"))
                {
                    this->setError(KJob::NoError);
                    reader.readNext();
                    attrs = reader.attributes();

                    d->result.m_capchaId = attrs.value(QStringLiteral("id")).toString().toUInt();

                    if(!attrs.value( QStringLiteral("question")).isEmpty())
                        d->result.m_captchaQuestion = QVariant(attrs.value( QStringLiteral("question")).toString());
                    else if(!attrs.value( QStringLiteral("url")).isEmpty())
                        d->result.m_captchaQuestion = QVariant(attrs.value( QStringLiteral("url")).toString());
                }
            }
            else if( reader.name() == QStringLiteral("error"))
            {
                this->setError(BrowsePagePrivate::error(attrs.value(QStringLiteral("code") ).toString()));
                d->reply->close();
                d->reply->deleteLater();
                emitResult();
                return;
            }

          }
          else if(token == QXmlStreamReader::Invalid &&
                  reader.error() != QXmlStreamReader::PrematureEndOfDocumentError)
          {

              this->setError(this->XmlError);
              d->reply->close();
              d->reply->deleteLater();
              emitResult();
              return;
          }
       }

        d->reply->close();
        d->reply->deleteLater();
        emit resultCaptcha(d->result.m_captchaQuestion);


}


void BrowsePage::finishedCaptcha(const QString& captcha)
{
    Q_D(BrowsePage);
    d->result.m_captchaAnswer = captcha;

    QUrl url         = d->baseUrl;
    QUrlQuery   query;

    query.addQueryItem(QStringLiteral("CaptchaId"), QString::number(d->result.m_capchaId));
    query.addQueryItem(QStringLiteral("CaptchaAnswer"), d->result.m_captchaAnswer);

    url.setQuery(query);
    QString data = url.toString();
    QByteArray byte_cookie;
    QList<QNetworkCookie> MediaWiki_cookies = d->mManager->cookieJar()->cookiesForUrl(d->m_MediaWiki.url());

    for(int i = 0; i < MediaWiki_cookies.size(); ++i)
    {
        byte_cookie += MediaWiki_cookies.at(i).toRawForm(QNetworkCookie::NameAndValueOnly);
        byte_cookie += ';';


    }

    //set the request
    QNetworkRequest request( url);
    request.setRawHeader("User-Agent", d->m_MediaWiki.userAgent().toUtf8());
    request.setRawHeader("Cookie", byte_cookie);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
    //send the request

    d->reply = d->mManager->post(request, data.toUtf8());
    connect( d->reply, SIGNAL(finished()),
             this, SLOT(finishedEdit()) );

}
//md5: MD5 hash (hex) of the text parameter or the prependtext and appendtext parameters concatenated.
//If this parameter is set and the hashes don't match,
//the edit is rejected. This can be used to guard against data corruption.









}
