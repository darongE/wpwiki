#ifndef WPMediaWiki_H
#define WPMediaWiki_H


//Qt lib
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>

//
#include "mediawiki_export.h"


namespace mediawiki
{

/**
 * @brief Access WPMediaWiki API
 */

class MEDIAWIKI_EXPORT WPMediaWiki
{

public:

    /**
     * @brief Make WPMediaWiki url api
     * @param url : wiki url
     * @param customUserAgent : you can specify the user-agent to use
     *        whcih will be cancatenated with the postfix user-agent
     *        else the postfix user-agent is used only
     */

    explicit WPMediaWiki(const QUrl& url, const QString& customUseragent = QString());


    /**
     * @brief Destructs the WPMediaWiki
     */

    ~WPMediaWiki();

    /**
     * @brief Returns the url api of the wiki
     * @return the url api of the wiki
     */

    QUrl url() const;

    /**
     * @brief Returns the user agent of the wiki
     * @return user agent of the wiki
     */

    QString userAgent() const;

    /**
     * @brief Returns the network manager instance of the wiki
     * @return the network manager instance of the wiki
     *
     */

    QNetworkAccessManager* manager() const;

 private:

    class WPMediaWikiPrivate;
    WPMediaWikiPrivate* const d_wiki_ptr;

    friend class WorkPrivate;

};

}









#endif // WPMediaWiki_H
