/** ===========================================================
 * @file
 *
 * This file is a part of KDE project
 * <a href="https://projects.kde.org/projects/extragear/libs/libmediawiki">libmediawiki</a>
 *
 * @date   2011-03-22
 * @brief  a MediaWiki C++ interface for KDE
 *
 * @author Copyright (C) 2010 by Alexandre Mendes
 *         <a href="mailto:alex dot mendes1988 at gmail dot com">alex dot mendes1988 at gmail dot com</a>
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

#ifndef TEST_QUERYINFO_H
#define TEST_QUERYINFO_H

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <QDebug>

#include <KCoreAddons/KJob>

#include "WPMediaWiki.h"
#include "query.h"
#include "wikipage.h"
#include "shield.h"
#include "server/fakeserver.h"

using mediawiki::WPMediaWiki;
using mediawiki::Query;
using mediawiki::WikiPage;
using mediawiki::Shield;

Q_DECLARE_METATYPE(WikiPage)
Q_DECLARE_METATYPE(Shield)
Q_DECLARE_METATYPE(Query*)
Q_DECLARE_METATYPE(QVector <Shield>)

class QueryInfoTest : public QObject
{
    Q_OBJECT

public Q_SLOTS:

    void queryInfoHandlePages(const WikiPage& page)
    {
        ++queryInfoCount;
        queryInfoResultsPage = page;
    }

    void queryInfoHandleProtection(const QVector<Shield>& protection)
    {
        ++queryInfoCount;
        queryInfoResultsProtections = protection;
    }

private Q_SLOTS:

    void initTestCase()
    {
        queryInfoCount    = 0;
 //     this->m_mediaWiki = new MediaWiki(QUrl(QStringLiteral("http://127.0.0.1:12566")));
//      this->m_mediaWiki = new WPMediaWiki(QUrl(QStringLiteral("http://en.wiki.org/w")));

        //this->m_mediaWiki = new WPMediaWiki(QUrl("https://en.wikipedia.org/w/api.php?action=query&meta=siteinfo&siprop=general|statistics&format=xml&formatversion=2"));

    }

    void constructQuery()
    {
        QFETCH(QString, request);
        QFETCH(Query*, job);

        queryInfoCount = 0;
        FakeServer fakeserver;
        fakeserver.startAndWait();

        job->exec();

        QList<FakeServer::Request> requests = fakeserver.getRequest();
        QCOMPARE(requests.size(), 1);

        FakeServer::Request requestServeur = requests[0];
//        QCOMPARE(requestServeur.agent, m_mediaWiki->userAgent());
//        QCOMPARE(requestServeur.type, QStringLiteral("GET"));
//        QCOMPARE(requestServeur.value, request);
    }

    void constructQuery_data()
    {
        QTest::addColumn<QString>("request");
        QTest::addColumn<Query*>("job");

        Query* const j1 = new Query(*m_mediaWiki);
        j1->setPageName(QStringLiteral("API"));

        QTest::newRow("Name pages")
                << QStringLiteral("/?format=xml&action=query&prop=info&inprop=protection%7Ctalkid%7Cwatched%7Csubjectid%7Curl%7Creadable%7Cpreload&titles=API")
                << j1;

//        Query* const j2 = new Query(*m_mediaWiki);
//        j2->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );

//        QTest::newRow("Token")
//                << QStringLiteral("/?format=xml&action=query&prop=info&inprop=protection%7Ctalkid%7Cwatched%7Csubjectid%7Curl%7Creadable%7Cpreload&intoken=cecded1f35005d22904a35cc7b736e18+%5C")
//                << j2;

//        Query* const j3 = new Query(*m_mediaWiki);
//        j3->setPageId(25255);

//        QTest::newRow("WikiPage Id")
//                << QStringLiteral("/?format=xml&action=query&prop=info&inprop=protection%7Ctalkid%7Cwatched%7Csubjectid%7Curl%7Creadable%7Cpreload&pageids=25255")
//                << j3;

//        Query *j4 = new Query(*m_mediaWiki);
//        j4->setRevisionID(44545);

//        QTest::newRow("Revision Id")
//                << QStringLiteral("/?format=xml&action=query&prop=info&inprop=protection%7Ctalkid%7Cwatched%7Csubjectid%7Curl%7Creadable%7Cpreload&revids=44545")
//                << j4;
    }

    void parseData()
    {
        QFETCH(QString,scenario);
        QFETCH(WikiPage ,page);
        QFETCH(QVector<Shield> ,protections);

        Query job(*m_mediaWiki);
        queryInfoCount = 0;
        FakeServer fakeserver;
        fakeserver.addScenario(scenario);
        fakeserver.startAndWait();

        connect(&job, SIGNAL(page(WikiPage)),
                this,SLOT(queryInfoHandlePages(WikiPage)));

        connect(&job, SIGNAL(protection(QVector<Shield>)),
                this,SLOT(queryInfoHandleProtection(QVector<Shield>)));

        job.exec();

        QList<FakeServer::Request> requests = fakeserver.getRequest();
        QCOMPARE(requests.size(), 1);

        QCOMPARE(queryInfoCount, 2);
        QCOMPARE(queryInfoResultsPage, page);
        QCOMPARE(queryInfoResultsProtections, protections);
        QVERIFY(fakeserver.isAllScenarioDone());
    }

    void parseData_data()
    {
        QTest::addColumn<QString>("scenario");
        QTest::addColumn< WikiPage >("page");
        QTest::addColumn< QVector<Shield> >("protections");

        Shield pr1;
        pr1.setType(QStringLiteral("edit"));
        pr1.setLevel(QStringLiteral("sysop"));
        pr1.setExpiry(QStringLiteral("infinity"));
        pr1.setSource(QString());

        Shield pr2;
        pr2.setType(QStringLiteral("move"));
        pr2.setLevel(QStringLiteral("sysop"));
        pr2.setExpiry(QStringLiteral("infinity"));
        pr2.setSource(QString());

        WikiPage page;
        page.setPageId(27697087);
        page.setTitle(QStringLiteral("API"));
        page.setNs(0);
        page.setTouched( QDateTime::fromString(QStringLiteral("2010-11-25T13:59:03Z"), QStringLiteral("yyyy'-'MM'-'dd'T'hh':'mm':'ss'Z'")) );
        page.setLastRevId(367741756);
        page.setCounter(0);
        page.setLength(70);
        page.setStarttimestamp(QDateTime::fromString(QStringLiteral("2010-11-25T16:14:51Z"), QStringLiteral("yyyy'-'MM'-'dd'T'hh':'mm':'ss'Z'")));
        page.setEditToken(QStringLiteral("+\\"));
        page.setTalkid(5477418);
        page.setFullurl(QUrl(QStringLiteral("http://en.wikipedia.org/wiki/API")));
        page.setEditurl(QUrl(QStringLiteral("http://en.wikipedia.org/w/index.php?title=API&action=edit")));
        page.setReadable(QString());
        page.setPreload(QString());

       // page.

        QTest::newRow("No protection")
                << QStringLiteral("<api><query><pages><page pageid=\"27697087\" ns=\"0\" title=\"API\" touched=\"2010-11-25T13:59:03Z\" lastrevid=\"367741756\" counter=\"0\" length=\"70\" redirect=\"\" starttimestamp=\"2010-11-25T16:14:51Z\" edittoken=\"+\\\" talkid=\"5477418\" fullurl=\"http://en.wikipedia.org/wiki/API\" editurl=\"http://en.wikipedia.org/w/index.php?title=API&action=edit\" ><protection /></page></pages></query></api>")
                << page
                << QVector<Shield>();

        QTest::newRow("One pages and one protection")
                << QStringLiteral("<api><query><pages><page pageid=\"27697087\" ns=\"0\" title=\"API\" touched=\"2010-11-25T13:59:03Z\" lastrevid=\"367741756\" counter=\"0\" length=\"70\" redirect=\"\" starttimestamp=\"2010-11-25T16:14:51Z\" edittoken=\"+\\\" talkid=\"5477418\" fullurl=\"http://en.wikipedia.org/wiki/API\" editurl=\"http://en.wikipedia.org/w/index.php?title=API&action=edit\" ><protection><pr type=\"edit\" level=\"sysop\" expiry=\"infinity\"/></protection></page></pages></query></api>")
                << page
                << (QVector<Shield>() << pr1);

        QTest::newRow("One pages and two protection")
                << QStringLiteral("<api><query><pages><page pageid=\"27697087\" ns=\"0\" title=\"API\" touched=\"2010-11-25T13:59:03Z\" lastrevid=\"367741756\" counter=\"0\" length=\"70\" redirect=\"\" starttimestamp=\"2010-11-25T16:14:51Z\" edittoken=\"+\\\" talkid=\"5477418\" fullurl=\"http://en.wikipedia.org/wiki/API\" editurl=\"http://en.wikipedia.org/w/index.php?title=API&action=edit\" ><protection><pr type=\"edit\" level=\"sysop\" expiry=\"infinity\"/><pr type=\"move\" level=\"sysop\" expiry=\"infinity\"/></protection></page></pages></query></api>")
                << page
                << (QVector<Shield>() << pr1 << pr2);
    }

    void cleanupTestCase()
    {
        delete this->m_mediaWiki;
    }

private:

    int                  queryInfoCount;
    WikiPage                 queryInfoResultsPage;
    QVector <Shield> queryInfoResultsProtections;
    WPMediaWiki*           m_mediaWiki;
};

QTEST_MAIN(QueryInfoTest)

#include "queryinfotest.moc"

#endif // TEST_QUERYINFO_H
