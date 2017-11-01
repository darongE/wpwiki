/** ===========================================================
 * @file
 *
 * This file is a part of KDE project
 * <a href="https://projects.kde.org/projects/extragear/libs/libmediawiki">libmediawiki</a>
 *
 * @date   2011-03-22
 * @brief  a MediaWiki C++ interface for KDE
 *
 * @author Copyright (C) 2011-2012 by Gilles Caulier
 *         <a href="mailto:caulier dot gilles at gmail dot com">caulier dot gilles at gmail dot com</a>
 * @author Copyright (C) 2010 by Joris Munoz
 *         <a href="mailto:munozjoris at gmail dot com">munozjoris at gmail dot com</a>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef WIKIWikiPage_H
#define WIKIWikiPage_H

// Qt includes

#include <QDateTime>
#include <QUrl>

// Local includes

#include "mediawiki_export.h"

namespace mediawiki
{

/**
 * @brief An image info.
 */
class MEDIAWIKI_EXPORT WikiPage
{

public:

    /**
     * @brief Constructs a WikiPage.
     */
    WikiPage();

    /**
     * @brief Constructs a WikiPage from an other WikiPage.
     * @param other an other WikiPage
     */
    WikiPage(const WikiPage& other);

    /**
     * @brief Destructs a WikiPage.
     */
    ~WikiPage();

    /**
     * @brief Assingning a WikiPage from an other WikiPage.
     * @param other an other WikiPage
     */
    WikiPage& operator=(WikiPage other);

    /**
     * @brief Returns true if this instance and other are equal, else false.
     * @param other instance to compare
     * @return true if there are equal, else false
     */
    bool operator==(const WikiPage& other) const;

    /**
     * @brief Set the WikiPageId of the WikiPage.
     * @param id the WikiPage id of the WikiPage
     */
    void setPageId(unsigned int id);

    /**
     * @brief Return the WikiPage id of the WikiPage.
     * @return the WikiPage id of the WikiPage
     */
    unsigned int pageId() const;

    /**
     * @brief Set the title of the WikiPage.
     * @param title the title of the WikiPage
     */
    void setTitle(const QString& title);

    /**
     * @brief Return the title of the WikiPage.
     * @return the title of the WikiPage
     */
    QString pageTitle() const;

    /**
     * @brief Set the namespace of the WikiPage.
     * @param ns the namespace of the WikiPage
     */
    void setNs(unsigned int ns) const;

    /**
     * @brief Return the namespace of the WikiPage.
     * @return the namespace of the WikiPage
     */
    unsigned int pageNs() const;

    /**
     * @brief Set the last revision id of the WikiPage.
     * @param lastRevId the last revision id of the WikiPage
     */
    void setLastRevId(unsigned int lastRevId) const;

    /**
     * @brief Return the last revision id of the WikiPage.
     * @return the last revision id of the WikiPage
     */
    unsigned int pageLastRevId() const;

    /**
     * @brief Set the number of views of the WikiPage.
     * @param counter the number of views of the WikiPage
     */
    void setCounter(unsigned int counter) const;

    /**
     * @brief Return the number of views of the WikiPage.
     * @return the number of views of the WikiPage
     */
    unsigned int pageCounter() const;

    /**
     * @brief Set the WikiPage size.
     * @param length the WikiPage size
     */
    void setLength(unsigned int length) const;

    /**
     * @brief Return the WikiPage size.
     * @return the WikiPage size
     */
    unsigned int pageLength() const;

    /**
     * @brief Set the WikiPage token.
     * @param editToken the WikiPage token
     */
    void setEditToken(const QString& editToken);

    /**
     * @brief Return the WikiPage token.
     * @return the WikiPage token
     */
    QString pageEditToken() const;

    /**
     * @brief Set the WikiPage ID of the talk WikiPage for each non-talk WikiPage.
     * @param talkid the WikiPage ID of the talk WikiPage for each non-talk WikiPage
     */
    void setTalkid(unsigned int talkid) const;

    /**
     * @brief Return the WikiPage ID of the talk WikiPage for each non-talk WikiPage.
     * @return the WikiPage ID of the talk WikiPage for each non-talk WikiPage
     */
    unsigned int pageTalkid() const;

    /**
     * @brief Set the full url of the WikiPage.
     * @param fullurl the full url of the WikiPage
     */
    void setFullurl(const QUrl& fullurl);

    /**
     * @brief Return the full url of the WikiPage.
     * @return the full url of the WikiPage
     */
    QUrl pageFullurl() const;

    /**
     * @brief Set the edit url of the WikiPage.
     * @param editurl the edit url of the WikiPage
     */
    void setEditurl(const QUrl& editurl);

    /**
     * @brief Return the edit url of the WikiPage.
     * @return the edit url of the WikiPage
     */
    QUrl pageEditurl() const;

    /**
     * @brief Set the readability of the WikiPage.
     * @param readable the readability of the WikiPage
     */
    void setReadable(const QString& readable);

    /**
     * @brief Return the readability of the WikiPage.
     * @return the readability of the WikiPage
     */
    QString pageReadable() const;

    /**
     * @brief Set the text returned by EditFormPreloadText.
     * @param preload the text returned by EditFormPreloadText
     */
    void setPreload(const QString& preload);

    /**
     * @brief Return the text returned by EditFormPreloadText.
     * @return the text returned by EditFormPreloadText
     */
    QString pagePreload() const;

    /**
     * @brief Set the last touched timestamp.
     * @param touched the last touched timestamp
     */
    void setTouched(const QDateTime& touched);

    /**
     * @brief Return the last touched timestamp.
     * @return the last touched timestamp
     */
    QDateTime pageTouched() const;

    /**
     * @brief Set the timestamp when you obtained the edit token.
     * @param starttimestamp the timestamp when you obtained the edit token
     */
    void setStarttimestamp(const QDateTime& starttimestamp);

    /**
     * @brief Return the timestamp when you obtained the edit token.
     * @return the timestamp when you obtained the edit token
     */
    QDateTime pageStarttimestamp() const;

private:

    class WikiPagePrivate;
    WikiPagePrivate* const d;
};

} // namespace mediawiki

#endif // WikiPage_H
