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
    Q_D(QueryInfo);
    d->requestParam[QStringLiteral("pageids")] = QString::number(id);
}

void QueryInfo::setRevisionId(unsigned int id)
{
    Q_D(QueryInfo);
    d->requestParam[QStringLiteral("revids")] = QString::number(id);
}


















}
