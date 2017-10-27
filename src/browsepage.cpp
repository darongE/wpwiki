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

#include "MediaWiki.h"
#include "query.h"
#include "work_p.h"

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
    BrowsePagePrivate(MediaWiki& mediawiki)
          : WorkPrivate(mediawiki)

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



};

BrowsePage::BrowsePage(MediaWiki& media, QObject* parent)
          : Work(*new BrowsePagePrivate(media),parent)
{

}

void BrowsePage::setUndoAfter(int undoafter)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("undoafter")] = QString::number(undoafter;)
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
    d->requestParam[QStringList("title")] = pageName;

}

void BrowsePage::setToken(const QString &token)
{
    Q_D(BrowsePage);
    d->requestParam[QStringList("token")] = token;

}

void BrowsePage::setBaseTimestamp(const QDateTime &baseTimestamp)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("basetimestamp")] = baseTimestamp;

}

void BrowsePage::setStartTimestamp(const QDateTime &startTimestamp)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("starttimestamp")] = startTimestamp;
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
       d->requestParameter[QStringLiteral("md5")] = QString();
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
        d->requestParameter[QStringLiteral("nocreate")] = QStringLiteral("on");
        d->requestParameter[QStringLiteral("md5")] = QString();
    }
}

void BrowsePage::setMinor(bool minor)
{
    Q_D(BrowsePage);
    if(minor)
        d->requestParameter[QStringLiteral("minor")] = QStringLiteral("on");
    else
        d->requestParameter[QStringLiteral("notminor")] = QStringLiteral("on");
}

void BrowsePage::setSection(const QString &section)
{
    Q_D(BrowsePage);
    d->requestParameter[QStringLiteral("section")] = section;
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
    Query* p_query = new Query(d->m_mediawiki, this);
    p_query->setPageName(d->requestParam[QStringLiteral("title")]);
    p_query->setToken(QStringLiteral("edit"));
    connect(info, SIGNAL(getPage(WikiPage)),
            this, SLOT(sendRequest(WikiPage)));

    p_query->start();

}
//e.g
//www.mediawiki.org/w/index.php
//?title=Project:Sandbox
//&action=edit
void BrowsePage::sendRequest(WikiPage wiki_page)
{
    Q_D(BrowsePage);
    d->requestParam[QStringLiteral("token")] = wiki_page.pageEditToken();

    QUrl    url = d->m_mediawiki.url();
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
        d->requestParam[QStringLiteral("md5")] = QString::fromLatin1(hash.toText());
    }
}



}
