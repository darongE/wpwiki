#ifndef MEDIAWIKI_P_H
#define MEDIAWIKI_P_H

#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>

namespace  mediawiki {

class Q_DECL_HIDDEN MediaWiki::MediaWikiPrivate
{

public:

    MediaWikiPrivate(const QUrl& url, const QString& userAgent, QNetworkAccessManager* const manager)
        : url(url),
          userAgent(m_userAgent),
          manager(mManager)
    {

    }

    ~MediaWikiPrivate()
    {
        delete mManager;
    }

public:

    static const QString           agent;
    const QUrl                     m_url;
    const QString                  m_userAgent;
    QNetworkAccessManager* const   mManager;

};

const QString MediaWiki::MediaWikiPrivate::POSTFIX_USER_AGENT = QString::fromUtf8("mediawiki-silk");

} //namespace meida wiki

#endif // MEDIAWIKI_P_H
