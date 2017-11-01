

#include "wikipage.h"

// C++ includes

#include <algorithm>

// Qt includes

#include <QtCore/QUrl>

namespace mediawiki
{

class Q_DECL_HIDDEN WikiPage::WikiPagePrivate
{
public:

    unsigned int m_pageid;
    unsigned int m_ns;
    unsigned int m_lastrevid;
    unsigned int m_counter;
    unsigned int m_length;
    unsigned int m_talkid;
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

WikiPage::WikiPage( const WikiPage& other)
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
           pageNs()             == other.pageNs()        &&
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

void WikiPage::setPageId(unsigned int id)
{
    d->m_pageid=id;
}

unsigned int WikiPage::pageId() const
{
    return d->m_pageid;
}

void WikiPage::setTitle(const QString& title)
{
    d->m_title=title;
}

QString WikiPage::pageTitle() const
{
    return d->m_title;
}

void WikiPage::setNs(unsigned int ns) const
{
    d->m_ns=ns;
}

unsigned int WikiPage::pageNs() const
{
    return d->m_ns;
}

void WikiPage::setLastRevId(unsigned int lastRevId) const
{
    d->m_lastrevid=lastRevId;
}

unsigned int WikiPage::pageLastRevId() const
{
    return d->m_lastrevid;
}

void WikiPage::setCounter(unsigned int counter) const
{
    d->m_counter=counter;
}

unsigned int WikiPage::pageCounter() const
{
    return d->m_counter;
}

void WikiPage::setLength(unsigned int length) const
{
     d->m_length=length;
}

unsigned int WikiPage::pageLength() const
{
     return d->m_length;
}

void WikiPage::setEditToken(const QString& editToken)
{
    d->m_edittoken=editToken;
}

QString WikiPage::pageEditToken() const
{
    return d->m_edittoken;
}

void WikiPage::setTalkid(unsigned int talkid) const
{
     d->m_talkid=talkid;
}

unsigned int WikiPage::pageTalkid() const
{
     return d->m_talkid;
}

void WikiPage::setFullurl(const QUrl& fullurl)
{
    d->m_fullurl=fullurl;
}

QUrl WikiPage::pageFullurl() const
{
    return d->m_fullurl;
}

void WikiPage::setEditurl(const QUrl& editurl)
{
    d->m_editurl=editurl;
}

QUrl WikiPage::pageEditurl() const
{
    return d->m_editurl;
}

void WikiPage::setReadable(const QString& readable)
{
    d->m_readable=readable;
}

QString WikiPage::pageReadable() const
{
    return d->m_readable;
}

void WikiPage::setPreload(const QString& preload)
{
    d->m_preload=preload;
}

QString WikiPage::pagePreload() const
{
    return d->m_preload;
}

void WikiPage::setTouched(const QDateTime& touched)
{
    d->m_touched=touched;
}

QDateTime WikiPage::pageTouched() const
{
    return d->m_touched;
}

void WikiPage::setStarttimestamp(const QDateTime& starttimestamp)
{
    d->m_starttimestamp=starttimestamp;
}

QDateTime WikiPage::pageStarttimestamp() const
{
    return d->m_starttimestamp;
}

} // namespace mediawiki;
