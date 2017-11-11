#include <QString>

#include "WPMediaWiki.h"
#include "WPMediaWiki_p.h"

namespace mediawiki {


WPMediaWiki::WPMediaWiki(const QUrl& url, const QString& customUserAgent)
    : d_wiki_ptr(new WPMediaWikiPrivate(url,
                                      customUserAgent.isEmpty() ? QString()
                                                                : QString(customUserAgent
                                                              + QStringLiteral("-"))
                                                              + WPMediaWikiPrivate::POSTFIX_USER_AGENT,
                                        new QNetworkAccessManager()))

{

}

WPMediaWiki::~WPMediaWiki()
{
 //   delete d_wiki_ptr;
}

QUrl WPMediaWiki::url() const
{
    return d_wiki_ptr->m_url;
}

QString WPMediaWiki::userAgent() const
{
    return d_wiki_ptr->m_userAgent;
}

QNetworkAccessManager* WPMediaWiki::manager() const
{
    return d_wiki_ptr->mManager;
}

} //namespace WPMediaWiki
