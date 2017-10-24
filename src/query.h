#ifndef QUERY_H
#define QUERY_H

#include <QList>
#include <QString>
#include <QUrl>
#include <QDateTime>

// local class
#include "wikipage.h"
#include "shield.h"
#include "mediawiki_export.h"
#include "work.h"


namespace  mediawiki
{

class MediaWiki;
class QueryPrivate;

class MEDIAWIKI_EXPORT Query : public Work
{

    Q_OBJECT
    Q_DECLARE_PRIVATE(Query)


public:

    /**
     * @brief Query
     * @param mediawiki work
     * @param parent : QObject parent
     */

    explicit Query(MediaWiki& mediawiki,QObject* const parent() = 0 );


    virtual ~Query();

    /**
     * @brief start the job asynchronously
     */
    void start() Q_DECL_OVERRIDE;

    /**
     * @brief set the page name
     * @param title : page name
     */
    void setPageName(const QString& title);
    /**
     * @brief set the token to perform a data-modifying action on page
     * @param token
     */
    void setToken(const QString& token);

    /**
     * @brief set the page ID
     * @param id : page ID
     */
    void setPageId(quint32 id);

    /**
     * @brief setRevisionID
     * @param id : page revision
     */
    void setRevisionID(quint32 id);


Q_SIGNALS:

    /**
     * @brief getPage
     * @param page : wikipage
     */
    void getPage(const WikiPage& page);
    void shield_work(const QVector<Shield>& shield);

private Q_SLOTS:

    /**
     * @brief SendRequest
     */
    void SendRequest();
    void ProcessReply();

};  //namespace mediawiki

}
#endif // QUERY_H
