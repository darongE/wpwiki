#ifndef MEDIAWIKI_BROWSEPAGE_H
#define MEDIAWIKI_BROWSEPAGE_H

// Qt Lib

#include <QDateTime>
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QNetworkCookieJar>

#include "work.h"
#include "mediawiki_export.h"


namespace mediawiki
{

class MediaWiki;
class BrowsePagePrivate;




class MEDIAWIKI_EXPORT BrowsePage : public Work
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BrowsePage)
public:

    /**
     * @brief Indicates all possible error conditions
     * found during theh processing
     */

    enum
    {
       TextMissing = Work::UserDefinedError+1,
       InvalidSection,
       TitleProtected,
       CreatePagePermissionMissing,
       AnonymousCreatePagePermissionMissing,
       ArticleDuplication,
       AnonymousCreateImagePermissionMissing,
       CreateImagePermissionMissing,
       SpamDetected,
       Filtered,
       ArticleSizeExceed,
       AnonymousEditPagePermissionMissing,
       EditPagePermissionMissiing,
       PageDeleted,
       EmptyPage,
       EmptySection,
       EditConflict,
       RevWrongPage,
       UndoFailed


    };

    /**
     * @brief Constructs on BrowsePage
     * @param media
     * @param parent
     */

    explicit BrowsePage(MediaWiki& media, QObject* parent = 0);

    /**
     * @brief Destorys the Browsepage work
     */
    virtual ~BrowsePage();

    /**
     * @brief starts the work asychronously
     */
    void start() Q_DECL_OVERRIDE;

    enum Watchlist
    {
        watch,
        unwatch,
        preferences,
        nochange

    };

    /**
     * @brief Specify watchlist element
     * @param checklist
     */
    void setWatchList(BrowsePage::Watchlist watchlist);

    /**
     * @brief If set, suppress errors about the page having
     *        been deleted in the meantime and recreate it.
     * @param recreate if set, suppress errors about the page
     *        having been deleted in the meantime and recreat it
     */
    void setRecreate(bool recreate);

    /**
     * @brief If set, throw an error if page already exits.
     * @param if set, throw an error if the page already exits
     */

    void setCreateonly(bool createonly);

    /**
     * @brief If set, throw a missing_title error if the page doesn't exist.
     * @param norecreate if set, throw a missing_title error if the page
     *        exist
     */
    void setNocreate(bool norecreate);

    /**
     * @brief If set to true, mark the edit as minor
     * @param minor if set to true, mark the edit as minor
     */
    void setMinor(bool minor);

    /**
     * @brief set the Section
     * @param section ( new section or integer)
     */
    void setSection(const QString& section);

    /**
     * @brief set the summary
     * @param summary
     */
    void setSummary(const QString& summary);

    /**
     * @brief Undo all reivisions from undo to this one.
     *        If not set,just undo one revision
     * @param undoafter if true set the undo after property
     */
    void setUndoAfter(int undoafter);

    /**
     * @brief Undo this revision. Overrides text, prependtext
     *        appendtext
     * @param undo if true set the undo
     */
    void setUndo(int undo);

    void setPrependText(const QString& prependText);




};


}
#endif // BROWSEPAGE_H
