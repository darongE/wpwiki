#ifndef WIKIPAGE_H
#define WIKIPAGE_H

#include <QDateTime>
#include <QUrl>

#include "mediawiki_export.h"


namespace  mediawiki
{


class MEDIAWIKI_EXPORT WikiPage
{
public:


    WikiPage();

    /**
     * @brief Constructs a page from an other page
     * @param other an other page
     */
    WikiPage(const WikiPage& other);

    ~WikiPage();

    /**
     * @brief Returns true if this instanace and other are equal,else false
     * @param other instance to compare
     * @return true if there are equal, else false
     */
    WikiPage& operator=(WikiPage other);

    /**
     * @brief Set the pageId of the page.
     * @param id : page id of the page
     */

    void setPageId(quint32 id);

    /**
     * @brief Return the page id of the page
     * @return the page id of the page
     */
    quint32 pageId() const;

    /**
     * @brief Set the tile of the page
     * @param title : title of the page
     */
    void setTitle(const QString& title);

    /**
     * @brief  pageTitle
     * @return title of the page
     */
    QString pageTitle() const;

    /**
     * @brief Set the namespace of the page
     * @param ns : namespace of the page
     */
    void setNS(quint32 ns) const;

    /**
     * @brief Return the namespace of the page
     * @return the namespace of the page
     */
    quint32 pageNS() const;

    /**
     * @brief Set the last revision id the page
     * @param lastRevId the last revision id of the page
     */
    void setLastRevId(quint32 lastRevId) const;

    /**
     * @brief Return the last revision id of the page
     * @return the last revision id
     */
    quint32 pageLastRevId() const;

    /**
     * @brief Set the number of views of the page
     * @param counter : no of views of the page
     */
    void setCounter(quint32 counter) const;

    /**
     * @brief Return the number of page views
     * @return the number of page views
     */
    quint32 pageCounter() const;

    /**
     * @brief Set the page size
     * @param length : page size
     */
    void setLength(quint32 length) const;

    /**
     * @brief Return the page size
     * @return the page size
     */
    quint32 pageLength() const;

    /**
     * @brief Set the page token.
     * @param editToken : page token
     */
    void setEditToken(const QString& editToken);

    /**
     * @brief Return the page token
     * @return page token
     */
    QString pageEditToken() const;

    /**
     * @brief Set the page ID of the talk page for each
     *         non-talk page.
     * @param talkid : page ID of the talk page for each non-talk page
     */
    void setTalkid(quint32 talkid) const;

    /**
     * @brief Return the page ID of the talk page for each non-talk page.
     * @return the page ID of the talk page for each non-talk page.
     */
    quint32 pageTalkid() const;

    /**
     * @brief Set the full url of the page
     * @param fullurl
     */
    void setFullurl(const QUrl& fullurl);

    /**
     * @brief Return the full url of the page
     * @return the full url
     */
    QUrl pageFullurl() const;

    /**
     * @brief set the edit url of the page
     * @param editurl
     */
    void setEditurl(const QUrl& editurl);

    /**
     * @brief return the edit url of the page
     * @return the edit url of the page
     */
    QUrl pageEditurl() const;

    /**
     * @brief set the readability of the page.
     * @param readable the readability of the page
     */
    void setReadable(const QString& readable);

    /**
     * @brief pageReadable
     * @return the readability of the page
     */
    QString pageReadable() const;

    /**
     * @brief Set the text returned by EditForm PreloadText
     * @param preload the text returned by EditForm PreloadText
     */
    void setPreload(const QString& preload);

    /**
     * @brief Return the text returned by EditForm PreloadText
     * @return the text returned by EditForm PreloadText
     */
    QString pagePreload() const;

    /**
     * @brief Set the last touched timestamp
     * @param touched the last touched timestamp
     */
    void setTouched(const QDateTime& touched);

    /**
     * @brief Return the last touched timestamp
     * @return the last touched timestamp
     */
    QDateTime pageTouched() const;

    /**
     * @brief set the timestamp when you obtained the edit token
     * (HH:MM:SS)
     * @param starttimestamp is obtained from the edit token
     */
    void setStarttimestamp(const QDateTime& starttimestamp);


    /**
     * @brief get the timestamp when you obtained the edit token
     * (HH:MM:SS)
     * @param timestamp is obtained from the edit token
     */
    QDateTime pageStarttimestamp() const;

private:

    class WikiPagePrivate;
    WikiPagePrivate* const d;

};

} // namespace mediawiki

#endif // WIKIPAGE_H
