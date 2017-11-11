#ifndef MediaWikiWORK_P_H
#define MediaWikiWORK_P_H

#include "WPMediaWiki.h"

namespace mediawiki {

class WorkPrivate
{
public:

    explicit WorkPrivate(WPMediaWiki& MediaWiki)
        : m_MediaWiki(MediaWiki),
          mManager(MediaWiki.manager()),
          reply(0)

    {

    }


    WPMediaWiki&                    m_MediaWiki;
    QNetworkAccessManager* const  mManager;
    QNetworkReply*                reply;
};

} // namespace MediaWiki

#endif // MediaWikiWORK_P_H
