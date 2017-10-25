#include "query.h"

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

#include "MediaWiki.h"
#include "work_p.h"


namespace  mediawiki {

class QueryPrivate : public WorkPrivate
{
public:

    QueryPrivate(MediaWiki& mediawiki)
        : WorkPrivate(mediawiki)
    {}

    QVector<Shield>         shield;
    QMap<QString, QString>  requestParam;
    WikiPage                wiki_page;

};


Query::Query(MediaWiki& mediawiki, QObject* const parent)
     : Work(*new Query(mediawiki), parent)
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

void Query::setRevisionId(unsigned int id)
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
//you can see : https://www.mediawiki.org/wiki/API:Data_formats
void Query::SendRequest()
{
    Q_D(Query);

    QUrl url = d->m_mediawiki.url();
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


}













}
