#include <QString>

#include "MediaWiki.h"
#include "MediaWiki_p.h"

namespace mediawiki {


MediaWiki::MediaWiki(const QUrl& url, const QString& customUserAgent)
    : d_wiki_ptr(new MediaWikiPrivate(url,
                                      customUserAgent.isEmpty() ? QString()
                                                                : QString(customUserAgent
                                                              + QStringLiteral("-"))
                                                              + MediaWikiPrivate::POSTFIX_USER_AGENT,
                                        new QNetworkAccessManager()))

{

}

MediaWiki::~MediaWiki()
{
    delete d_wiki_ptr;
}

QUrl MediaWiki::url() const
{
    return d_wiki_ptr->m_url;
}

QString MediaWiki::userAgent() const
{
    return d_wiki_ptr->m_userAgent;
}

QNetworkAccessManager* MediaWiki::manager() const
{
    return d_wiki_ptr->mManager;
}

} //namespace mediawiki
