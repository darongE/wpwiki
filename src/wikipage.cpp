
#include "wikipage.h"

#include <algorithm>
#include <QUrl>


namespace  mediawiki
{

class Q_DECL_HIDDEN WikiPage::WikiPagePrivate
{
public:

    quint32      m_pageid;
    quint32      m_ns;
    quint32      m_lastrevid;
    quint32      m_counter;
    quint32      m_length;
    quint32      m_talkid;
    QString      m_edittoken;
    QString      m_title;
    QString      m_readable;
    QString      m_preload;
    QUrl         m_fullurl;
    QUrl         m_editurl;
    QDateTime    m_touched;
    QDateTime    m_starttimestamp;

};


WikiPage::WikiPage()
        :d(new WikiPagePrivate())
{

}

WikiPage::~WikiPage()
{
    delete d;
}

WikiPage::WikiPage(const WikiPage &other)
                : d(new WikiPagePrivate(*(other.d)))

{
}

WikiPage& WikiPage::operator=(WikiPage other)
{
    *d = *other.d;
    return *this;
}

bool WikiPage::operator==(const WikiPage& other) const
{
    return pageId()             == other.pageId()        &&
           pageTitle()          == other.pageTitle()     &&
           pageNS()             == other.pageNS()        &&
           pageLastRevId()      == other.pageLastRevId() &&
           pageCounter()        == other.pageCounter()   &&
           pageLength()         == other.pageLength()    &&
           pageEditToken()      == other.pageEditToken() &&
           pageTalkid()         == other.pageTalkid()    &&
           pageFullurl()        == other.pageFullurl()   &&
           pageEditurl()        == other.pageEditurl()   &&
           pageReadable()       == other.pageReadable()  &&
           pagePreload()        == other.pagePreload()   &&
           pageTouched()        == other.pageTouched()   &&
           pageStarttimestamp() == other.pageStarttimestamp();


}

void WikiPage::setPageId(quint32 id)
{
   d->m_pageid = id;

}

quint32 WikiPage::pageId() const
{
    return d->m_pageid;
}

void WikiPage::setTitle(const QString& title)
{
    d->m_title = title;
}

QString WikiPage::pageTitle() const
{
    return d->m_title;
}

void WikiPage::setNS(quint32 ns) const
{
   d->m_ns = ns;
}

quint32 WikiPage::pageNS() const
{
    return d->m_ns;
}

void WikiPage::setLastRevId(quint32 lastRevId) const
{
    d->m_lastrevid = lastRevId;
}

quint32 WikiPage::pageLastRevId() const
{
    return d->m_lastrevid;
}

void WikiPage::setCounter(quint32 counter) const
{
    d->m_counter = counter;
}

quint32 WikiPage::pageCounter() const
{
    return d->m_counter;
}

void WikiPage::setLength(quint32 length) const
{
    d->m_length = length;
}

quint32 WikiPage::pageLength() const
{
    return d->m_length;
}

void WikiPage::setEditToken(const QString &editToken)
{
    d->m_edittoken = editToken;
}

QString WikiPage::pageEditToken() const
{
    return d->m_edittoken;
}

void WikiPage::setFullurl(const QUrl &fullurl)
{
    d->m_fullurl = fullurl;
}

QUrl WikiPage::pageFullurl() const
{
    return d->m_fullurl;
}

void WikiPage::setReadable(const QString &readable)
{
    d->m_readable = readable;
}


void WikiPage::pageReadable() const
{
    return d->m_readable;
}

void WikiPage::setPreload(const QString &preload)
{
    d->m_preload = preload;
}

QString WikiPage::pagePreload() const
{
    return d->m_touched;
}


} // namespace mediawiki
