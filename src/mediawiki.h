#ifndef MEDIAWIKI_H
#define MEDIAWIKI_H


//Qt lib
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>

//
#include "mediawiki_export.h"
#include "MediaWiki_p.h"

namespace  mediawiki
{

/**
 * @brief Access Mediawiki API
 */

class MEDIAWIKI_EXPORT MediaWiki
{
public:

    /**
     * @brief Make MediaWiki url api
     * @param url : wiki url
     * @param customUserAgent : you can specify the user-agent to use
     *        whcih will be cancatenated with the postfix user-agent
     *        else the postfix user-agent is used only
     */

    explicit MediaWiki(const QUrl& url, const QString& customUseragent = QString());


    /**
     * @brief Destructs the MediaWiki
     */

    ~MediaWiki();

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

    class MediaWikiPrivate;
    MediaWikiPrivate* const d_wiki_ptr;

    //friend class WorkPrivate:

};

}









#endif // MEDIAWIKI_H
