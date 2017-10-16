#ifndef MEDIAWIKIWORK_P_H
#define MEDIAWIKIWORK_P_H

#include "MediaWiki.h"

namespace mediawiki {

class WorkPrivate
{
public:

    explicit WorkPrivate(MediaWiki& mediawiki)
        : m_mediawiki(mediawiki),
          mManager(mediawiki.manager()),
          reply(0)

    {

    }


    MediaWiki&                    m_mediawiki;
    QNetworkAccessManager* const  mManager;
    QNetworkReply*                reply;
};

} // namespace mediawiki

#endif // MEDIAWIKIWORK_P_H
