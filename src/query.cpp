#include "query.h"
#include "cookiehandler.h"

#include <QDateTime>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QXmlStreamReader>
#include <QRegExp>

#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "WPMediaWiki.h"
#include "work_p.h"


namespace  mediawiki {

class QueryPrivate : public WorkPrivate
{
public:

    QueryPrivate(WPMediaWiki& MediaWiki)
        : WorkPrivate(MediaWiki)
    {


    }

    QVector<Shield>         m_vec_shield;
    QMap<QString, QString>  requestParam;
    WikiPage                wiki_page;
    CookieHandler           *cookie_handler;

};


Query::Query(WPMediaWiki& MediaWiki, QObject* const parent)
     : Work(*new QueryPrivate(MediaWiki), parent)
{

}

Query::~Query()
{

}

void Query::setPageName(const QString &title)
{
    Q_D(Query);
    d->requestParam[QStringLiteral("titles")] = title;
}

void Query::setToken(const QString &token)
{
    Q_D(Query);
    d->requestParam[QStringLiteral("intoken")] = token;
}

void Query::setPageId(quint32 id)
{
    Q_D(Query);
    d->requestParam[QStringLiteral("pageids")] = QString::number(id);
}

void Query::setRevisionID(unsigned int id)
{
    Q_D(Query);
    d->requestParam[QStringLiteral("revids")] = QString::number(id);
}

void Query::start()
{
    QTimer::singleShot(0, this, SLOT(SendRequest()));
}

//media wiki api form
//api.php?action=query&titles=Albert%20Einstein&prop=info&format=xmlfm
//you can see : https://www.MediaWiki.org/wiki/API:Data_formats
void Query::SendRequest()
{
    Q_D(Query);

    QUrl url = d->m_MediaWiki.url();
    QUrlQuery query;


    query.addQueryItem(QStringLiteral("format"), QStringLiteral("xml"));
    query.addQueryItem(QStringLiteral("action"), QStringLiteral("query"));
    query.addQueryItem(QStringLiteral("prop"),   QStringLiteral("info"));
    query.addQueryItem(QStringLiteral("inprop"), QStringLiteral("protection|talkid|watched|subjectid|url|readable|preload"));


    QMapIterator<QString, QString> i(d->requestParam);
    while (i.hasNext())
    {
        i.next();
        query.addQueryItem(i.key(), i.value());
    }

    url.setQuery(query);

    // this part will handle in Cookiehandler.h
    d->cookie_handler->sendSignal(url);
    d->cookie_handler->sendPostRequest(d->m_MediaWiki.userAgent().toUtf8(),0);

    d->reply = d->cookie_handler->getReply();

    connectReply();

     connect(d->reply, SIGNAL(finished()), this, SLOT(ProcessReply()));
  }


void Query::ProcessReply()
{
    Q_D(Query);

    disconnect(d->reply, SIGNAL(finished()),
               this, SLOT(ProcessReply()));

    if(d->reply->error() == QNetworkReply::NoError)
    {
        QString content = QString::fromUtf8(d->reply->readAll());
        QRegExp regex(QStringLiteral("&(?!\\w+;)"));


        // "&(?!\\w+;)"  --> &amp
        content.replace(regex, QStringLiteral("&amp"));
        QXmlStreamReader reader(content);
        QVector<Shield> v_shield;

        while(!reader.atEnd() && !reader.hasError() )
        {
            QXmlStreamReader::TokenType token = reader.readNext();
            QXmlStreamAttributes attrs = reader.attributes();

            if (token == QXmlStreamReader::StartElement)
            {
                if (reader.name() == QLatin1String("page"))
                {
                    d->wiki_page.setPageId(attrs.value(QStringLiteral("pageid")).toString().toUInt());
                    d->wiki_page.setTitle(attrs.value(QStringLiteral("title")).toString());
                    d->wiki_page.setNs(attrs.value(QStringLiteral("ns")).toString().toUInt());
                    d->wiki_page.setTouched(QDateTime::fromString(attrs.value(QStringLiteral("touched")).toString(),
                                                                  QStringLiteral("yyyy'-'MM'-'dd'T'hh':'mm':'ss'Z'")));

                    d->wiki_page.setLastRevId(attrs.value(QStringLiteral("lastrevid")).toString().toUInt());
                    d->wiki_page.setCounter(attrs.value(QStringLiteral("counter")).toString().toUInt());
                    d->wiki_page.setLength(attrs.value(QStringLiteral("length")).toString().toUInt());
                    d->wiki_page.setStarttimestamp(QDateTime::fromString(attrs.value(QStringLiteral("starttimestamp")).toString(),
                                                                         QStringLiteral("yyyy'-'MM'-'dd'T'hh':'mm':'ss'Z'")));

                    d->wiki_page.setEditToken(attrs.value(QStringLiteral("edittoken")).toString());
                    d->wiki_page.setTalkid(attrs.value(QStringLiteral("talkid")).toString().toUInt());
                    d->wiki_page.setFullurl(QUrl(attrs.value(QStringLiteral("fullurl")).toString()));
                    d->wiki_page.setEditurl(QUrl(attrs.value(QStringLiteral("editurl")).toString()));
                    d->wiki_page.setReadable(attrs.value(QStringLiteral("readable")).toString());
                    d->wiki_page.setPreload(attrs.value(QStringLiteral("preload")).toString());
                }
                else  if(reader.name() == QLatin1String("protection"))
                {

                    //protection have many item. so should clear
                    v_shield.clear();
                }
                else if(reader.name() == QLatin1String("pr"))
                {


                    QString expiry(attrs.value(QStringLiteral("expiry")).toString());
                    QString level(attrs.value(QStringLiteral("level")).toString());
                    QString type(attrs.value(QStringLiteral("type")).toString());
                    QString source;

                    if(!attrs.value(QStringLiteral("source")).toString().isEmpty())
                    {
                        source = attrs.value(QStringLiteral("source")).toString();
                    }
                    else if(!attrs.value(QStringLiteral("cascade")).toString().isEmpty())
                    {
                        source = attrs.value(QStringLiteral("cascade")).toString();
                    }

                    Shield m_shield;
                    m_shield.setExpiry(expiry);
                    m_shield.setLevel(level);
                    m_shield.setType(type);
                    m_shield.setSource(source);
                    v_shield.push_back(m_shield);
                }

            }
            else if( token == QXmlStreamReader::EndElement)
            {
                if (reader.name() == QLatin1String("page"))
                    d->m_vec_shield = v_shield;
            }
        }

        if(!reader.hasError())
        {
            setError(KJob::NoError);
            emit shield_work(v_shield);  //send protection..
            emit WikiPage(d->wiki_page);
        }
        else
        {
            setError(Work::XmlError);
        }
    }
    else
    {
        setError(Work::NetworkError);
    }

    emitResult();
}

}  //namespace MediaWiki












