#ifndef WPMEDIAWIKI_P_H
#define WPMEDIAWIKI_P_H

#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>

namespace  mediawiki
{

 class Q_DECL_HIDDEN WPMediaWiki::WPMediaWikiPrivate
 {

public:

    WPMediaWikiPrivate(const QUrl& url, const QString& userAgent, QNetworkAccessManager* const manager)
        : m_url(url),
          m_userAgent(userAgent),
          mManager(manager)
    {


    }

    ~WPMediaWikiPrivate()
    {
        delete mManager;
    }

public:

    static const QString         POSTFIX_USER_AGENT;
    const QUrl                     m_url;
    const QString                  m_userAgent;
    QNetworkAccessManager* const   mManager;

};

const QString WPMediaWiki::WPMediaWikiPrivate::POSTFIX_USER_AGENT = QString::fromUtf8("MediaWiki-silk");

} //namespace meida wiki

#endif // WPMEDIAWIKI_P_H
