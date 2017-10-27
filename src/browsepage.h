#ifndef MEDIAWIKI_BROWSEPAGE_H
#define MEDIAWIKI_BROWSEPAGE_H

// Qt Lib

#include <QDateTime>
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QNetworkCookieJar>

#include "work.h"
#include "query.h"
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

    explicit BrowsePage(MediaWiki& media, QObject* pa = 0);

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
     * @brief Undo all reivisions from undo to this one. If not set,just undo one revision
     * @param undoafter if true set the undo after property
     */
    void setUndoAfter(int undoafter);

    /**
     * @brief Undo this revision. Overrides text, prependtext and appendtext
     * @param undo if true set the undo
     */
    void setUndo(int undo);

    /**
     * @brief Set the text added to the beginning of the page. Overrides Text.
     * @param prependText the text added to the beginning of the page
     */
    void setPrependText(const QString& prependText);

    /**
     * @brief Set the text added to the end of the page. Overrides text.
     * @param appendText the text added to the end of the page
     */

    void setAppendText(const QString& appendText);
    /**
     * @brief Set the page title
     * @param pageName the page title
     */
    void setPageName(const QString& pageName);

    /**
     * @brief Set the edit token. Retrieve from QueryInfo.
     * @param token the edit token
     */
    void setToken(const QString& token);

    /**
     * @brief Set the timestamp of the base revision. Leave unset to ignore conflit.
     * @param baseTimestamp the timestamp of the base revision
     */
    void setBaseTimestamp(const QDateTime& baseTimestamp);
    /**
     * @brief Set the timestamp when you obtained the edit token
     * @param startTimestamp the timestamp when you obtained the edit token
     */
    void setStartTimestamp(const QDateTime& startTimestamp);

    /**
     * @brief Set the page content
     * @param text the page content.
     */
    void setText(const QString& text);

Q_SIGNALS:
    /**
     * @brief Emit the captcha question.
     * @param captcha the captcha question
     */

    void resultCaptcha(const QVariant& captcha);

private Q_SLOTS:

    // bring data from page
    void sendRequest(WikiPage wiki_page);
    void finished();

    /**
     * @brief Put the captcha answer.
     * @param captcha the captcha answer
     */

    void finishedCaptcha(const QString& captcha);
};


}  // namespace mediawiki
#endif // BROWSEPAGE_H
