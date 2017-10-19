
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

}










} // namespace mediawiki
