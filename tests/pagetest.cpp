#ifndef TEST_PAGE_H
#define TEST_PAGE_H

#include <QObject>
#include <QTest>

#include <KCoreAddons/KJob>

#include "WPMediaWiki.h"
#include "browsepage.h"
#include "server/fakeserver.h"

using mediawiki::WPMediaWiki;
using mediawiki::BrowsePage;

Q_DECLARE_METATYPE(FakeServer::Request)
Q_DECLARE_METATYPE(QVariant)
Q_DECLARE_METATYPE(BrowsePage*)


class PageTest : public QObject
{
    Q_OBJECT

Q_SIGNALS:

    void captchaSignal(const QString & CaptchaAnswer);

public Q_SLOTS:

    void pageHandle(KJob* )
    {
        editCount++;
    }

    void pageHandle(const QVariant& captcha)
    {
        editCount++;
        this->CaptchaQuestion = captcha;
        emit captchaSignal(this->CaptchaAnswer);
    }

private Q_SLOTS:

    void initTestCase()
    {
        editCount            = 0;
  //      this->m_mediaWiki    = new WPMediaWiki(QUrl(QStringLiteral("http://127.0.0.1:12566")));

        this->m_mediaWiki    = new WPMediaWiki(QUrl(QStringLiteral("https://en.wikipedia.org/api/rest_v1/page/mobile-sections-lead/Hyuna")));

        this->m_infoScenario = QStringLiteral("<api><query><pages><page pageid=\"27697087\" ns=\"0\" title=\"API\" touched=\"2010-11-25T13:59:03Z\" lastrevid=\"367741756\" counter=\"0\" length=\"70\" redirect=\"\" starttimestamp=\"2010-11-25T16:14:51Z\" edittoken=\"cecded1f35005d22904a35cc7b736e18+\\\" talkid=\"5477418\" fullurl=\"http://en.wikipedia.org/wiki/API\" editurl=\"http://en.wikipedia.org/w/index.php?title=API&action=edit\" ><protection /></page></pages></query></api>");
    }

    void editSetters()
    {
        QFETCH(QString, request);
        QFETCH(QString, senario);
        QFETCH(BrowsePage*, job);

        editCount = 0;
        FakeServer fakeserver;
        fakeserver.setScenario(m_infoScenario);
        fakeserver.addScenario(senario);
        fakeserver.startAndWait();

        connect(job, SIGNAL(result(KJob*)),
                this, SLOT(pageHandle(KJob*)));

        job->exec();
        FakeServer::Request serverrequest = fakeserver.getRequest()[1];
        QCOMPARE(serverrequest.type, QStringLiteral("POST"));
        QCOMPARE(serverrequest.value, request);
        QCOMPARE(job->error(), (int)BrowsePage::NoError);
        QCOMPARE(this->editCount, 1);
    }
    void editSetters_data()
    {
        QTest::addColumn<QString>("request");
        QTest::addColumn<QString>("senario");
        QTest::addColumn<BrowsePage*>("job");

        BrowsePage* const e1 = new BrowsePage( *m_mediaWiki, NULL);
        e1->setSection(QStringLiteral("new"));
        e1->setSummary(QStringLiteral("Hello World") );
        e1->setPageName( QStringLiteral("Talk:Main WikiPage") );
        e1->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
        e1->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        e1->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        e1->setText( QStringLiteral("Hello everyone!") );
        QTest::newRow("Text")
                << QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
                << e1;

    }
//        BrowsePage* const e2 = new BrowsePage( *m_mediaWiki, NULL);
//        e2->setSection(QStringLiteral("new"));
//        e2->setSummary(QStringLiteral("Hello World"));
//        e2->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e2->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e2->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e2->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e2->setAppendText( QStringLiteral("Hello everyone!") );
//        QTest::newRow("Append")
//                << QStringLiteral("/?format=xml&action=edit&appendtext=Hello%20everyone!&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e2;

//        BrowsePage* const e3 = new BrowsePage( *m_mediaWiki, NULL);
//        e3->setSection(QStringLiteral("new"));
//        e3->setSummary(QStringLiteral("Hello World"));
//        e3->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e3->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e3->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e3->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e3->setPrependText( QStringLiteral("Hello everyone!") );
//        QTest::newRow("Prepend")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&prependtext=Hello%20everyone!&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e3;

//        BrowsePage* const e4 = new BrowsePage( *m_mediaWiki, NULL);
//        e4->setSummary(QStringLiteral("Hello World"));
//        e4->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e4->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e4->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e4->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e4->setUndo(13585);
//        QTest::newRow("Undo")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&title=Talk:Main%20Page&undo=13585&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e4;

//        BrowsePage* const e5 = new BrowsePage( *m_mediaWiki, NULL);
//        e5->setSummary(QStringLiteral("Hello World"));
//        e5->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e5->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e5->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e5->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e5->setUndoAfter(13585);
//        QTest::newRow("Undo After")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&title=Talk:Main%20Page&undoafter=13585&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e5;

//        BrowsePage* const e6 = new BrowsePage( *m_mediaWiki, NULL);
//        e6->setSummary(QStringLiteral("Hello World"));
//        e6->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e6->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e6->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e6->setText( QStringLiteral("Hello everyone!") );
//        e6->setRecreate(true);
//        e6->setSection(QStringLiteral("new"));
//        e6->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        QTest::newRow("Recreate")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&recreate=on&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e6;

//        BrowsePage* const e7 = new BrowsePage( *m_mediaWiki, NULL);
//        e7->setSummary(QStringLiteral("Hello World"));
//        e7->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e7->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e7->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e7->setText( QStringLiteral("Hello everyone!") );
//        e7->setCreateonly(true);
//        e7->setSection(QStringLiteral("new"));
//        e7->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        QTest::newRow("CreateOnly")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&createonly=on&md5=4d184ec6e8fe61abccb8ff62c4583cd0&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e7;

//        BrowsePage* const e8 = new BrowsePage( *m_mediaWiki, NULL);
//        e8->setSummary(QStringLiteral("Hello World"));
//        e8->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e8->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e8->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e8->setText( QStringLiteral("Hello everyone!") );
//        e8->setNocreate(true);
//        e8->setSection(QStringLiteral("new"));
//        e8->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        QTest::newRow("No Create")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&nocreate=on&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e8;

//        BrowsePage* const e9 = new BrowsePage( *m_mediaWiki, NULL);
//        e9->setSummary(QStringLiteral("Hello World"));
//        e9->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e9->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e9->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e9->setText( QStringLiteral("Hello everyone!") );
//        e9->setMinor(true);
//        e9->setSection(QStringLiteral("new"));
//        e9->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        QTest::newRow("Minor")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&minor=on&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e9;

//        BrowsePage* const e10 = new BrowsePage( *m_mediaWiki, NULL);
//        e10->setSummary(QStringLiteral("Hello World"));
//        e10->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e10->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e10->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e10->setText( QStringLiteral("Hello everyone!") );
//        e10->setWatchList(BrowsePage::watch);
//        QTest::newRow("WatchList watch")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&watchlist=watch&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e10;

//        BrowsePage* const e11 = new BrowsePage( *m_mediaWiki, NULL);
//        e11->setSummary(QStringLiteral("Hello World"));
//        e11->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e11->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e11->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e11->setText( QStringLiteral("Hello everyone!") );
//        e11->setWatchList(BrowsePage::unwatch);
//        QTest::newRow("WatchList unwatch")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&watchlist=unwatch&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e11;

//        BrowsePage* const e12 = new BrowsePage( *m_mediaWiki, NULL);
//        e12->setSummary(QStringLiteral("Hello World"));
//        e12->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e12->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e12->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e12->setText( QStringLiteral("Hello everyone!") );
//        e12->setWatchList(BrowsePage::preferences);
//        QTest::newRow("WatchList preferences")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&watchlist=preferences&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e12;

//        BrowsePage* const e13 = new BrowsePage( *m_mediaWiki, NULL);
//        e13->setSummary(QStringLiteral("Hello World"));
//        e13->setPageName( QStringLiteral("Talk:Main WikiPage") );
//        e13->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
//        e13->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
//        e13->setText( QStringLiteral("Hello everyone!") );
//        e13->setWatchList(BrowsePage::nochange);
//        QTest::newRow("WatchList nochange")
//                <<  QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&watchlist=nochange&token=cecded1f35005d22904a35cc7b736e18+%5C")
//                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>")
//                << e13;
//    }

    void error()
    {
        QFETCH(QString, scenario);
        QFETCH(int, error);


        editCount = 0;
        WPMediaWiki mediawiki(QUrl(QStringLiteral("http://127.0.0.1:12566")));
        FakeServer fakeserver;

        if(scenario != QStringLiteral("error serveur"))
        {
            fakeserver.setScenario(m_infoScenario);
            fakeserver.addScenario(scenario);
            fakeserver.startAndWait();
        }

        BrowsePage* const job = new BrowsePage(mediawiki, NULL);
        job->setSection(QStringLiteral("new"));
        job->setSummary(QStringLiteral("Hello World") );
        job->setPageName( QStringLiteral("Talk:Main WikiPage") );
        job->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
        job->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        job->setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        job->setText( QStringLiteral("Hello everyone!") );

        connect(job,  SIGNAL(result(KJob*)),
                this, SLOT(pageHandle(KJob*)));

        job->exec();

        if(scenario != QStringLiteral("error serveur"))
        {
            QList<FakeServer::Request> requests = fakeserver.getRequest();
            QCOMPARE(requests.size(), 2);
        }

        QCOMPARE(job->error(), error);
        QCOMPARE(editCount, 1);

        if(scenario != QStringLiteral("error serveur"))
        {
            QVERIFY(fakeserver.isAllScenarioDone());
        }
    }
    void error_data()
    {
        QTest::addColumn<QString>("scenario");
        QTest::addColumn<int>("error");

        QTest::newRow("No text")
                << QStringLiteral("<api><error code=\"notext\" info=\"\" /> </api>")
                << int(BrowsePage::TextMissing);
        QTest::newRow("Invalide section")
                << QStringLiteral("<api><error code=\"invalidsection\" info=\"\" /> </api>")
                << int(BrowsePage::InvalidSection);
        QTest::newRow("Invalide section")
                << QStringLiteral("<api><error code=\"invalidsection\" info=\"\" /> </api>")
                << int(BrowsePage::InvalidSection);
        QTest::newRow("Protected Title")
                << QStringLiteral("<api><error code=\"protectedtitle\" info=\"\" /> </api>")
                << int(BrowsePage::TitleProtected);
        QTest::newRow("Cant Create")
                << QStringLiteral("<api><error code=\"cantcreate\" info=\"\" /> </api>")
                << int(BrowsePage::CreatePagePermissionMissing);
        QTest::newRow("Cant Create Anonymous")
                << QStringLiteral("<api><error code=\"cantcreate-anon\" info=\"\" /> </api>")
                << int(BrowsePage::AnonymousCreatePagePermissionMissing);
        QTest::newRow("Cant Create Anonymous")
                << QStringLiteral("<api><error code=\"cantcreate-anon\" info=\"\" /> </api>")
                << int(BrowsePage::AnonymousCreatePagePermissionMissing);
        QTest::newRow("Article Duplication")
                << QStringLiteral("<api><error code=\"articleexists\" info=\"\" /> </api>")
                << int(BrowsePage::ArticleDuplication);
        QTest::newRow("Anonymous Create Image Permission Missing")
                << QStringLiteral("<api><error code=\"noimageredirect-anon\" info=\"\" /> </api>")
                << int(BrowsePage::AnonymousCreateImagePermissionMissing);
        QTest::newRow("Create Image Permission Missing")
                << QStringLiteral("<api><error code=\"noimageredirect\" info=\"\" /> </api>")
                << int(BrowsePage::CreateImagePermissionMissing);
        QTest::newRow("Spam Detected")
                << QStringLiteral("<api><error code=\"spamdetected\" info=\"\" /> </api>")
                << int(BrowsePage::SpamDetected);
        QTest::newRow("Filtered")
                << QStringLiteral("<api><error code=\"filtered\" info=\"\" /> </api>")
                << int(BrowsePage::Filtered);
        QTest::newRow("Article Size Exceed")
                << QStringLiteral("<api><error code=\"contenttoobig\" info=\"\" /> </api>")
                << int(BrowsePage::ArticleSizeExceed);
        QTest::newRow("Anonymous no edit")
                << QStringLiteral("<api><error code=\"noedit-anon\" info=\"\" /> </api>")
                << int(BrowsePage::AnonymousEditPagePermissionMissing);
        QTest::newRow("No edit")
                << QStringLiteral("<api><error code=\"noedit\" info=\"\" /> </api>")
                << int(BrowsePage::EditPagePermissionMissing);
        QTest::newRow("WikiPage delete")
                << QStringLiteral("<api><error code=\"pagedeleted\" info=\"\" /> </api>")
                << int(BrowsePage::PageDeleted);
        QTest::newRow("Empty page")
                << QStringLiteral("<api><error code=\"emptypage\" info=\"\" /> </api>")
                << int(BrowsePage::EmptyPage);
        QTest::newRow("Empty section")
                << QStringLiteral("<api><error code=\"emptynewsection\" info=\"\" /> </api>")
                << int(BrowsePage::EmptySection);
        QTest::newRow("BrowsePage conflict")
                << QStringLiteral("<api><error code=\"editconflict\" info=\"\" /> </api>")
                << int(BrowsePage::EditConflict);
        QTest::newRow("Revision wrong page")
                << QStringLiteral("<api><error code=\"revwrongpage\" info=\"\" /> </api>")
                << int(BrowsePage::RevWrongPage);
        QTest::newRow("Undo Failed")
                << QStringLiteral("<api><error code=\"undofailure\" info=\"\" /> </api>")
                << int(BrowsePage::UndoFailed);
    }

    void editTestTextCaptchaTrue()
    {
        editCount = 0;
        FakeServer fakeserver;

        this->request = QStringLiteral("/?format=xml&action=edit&basetimestamp=2008-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&section=new&starttimestamp=2008-03-27T21:15:39Z&summary=Hello%20World&text=Hello%20everyone!&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C");
        QString senario(QStringLiteral("<api><edit result=\"Failure\"><captcha type=\"math\" mime=\"text/tex\" id=\"509895952\" question=\"36 + 4 = \" /></edit></api>"));

        fakeserver.setScenario(m_infoScenario);
        fakeserver.addScenario(senario);
        senario = QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main WikiPage\" oldrevid=\"465\" newrevid=\"471\" /></api>");
        fakeserver.addScenario(senario);
        fakeserver.startAndWait();

        BrowsePage edit( *m_mediaWiki, NULL);
        edit.setSection(QStringLiteral("new"));
        edit.setSummary(QStringLiteral("Hello World") );
        edit.setPageName( QStringLiteral("Talk:Main WikiPage") );
        edit.setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\") );
        edit.setBaseTimestamp( QDateTime::fromString(QStringLiteral("2008-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        edit.setStartTimestamp( QDateTime::fromString(QStringLiteral("2008-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        edit.setText( QStringLiteral("Hello everyone!") );

        connect(&edit, SIGNAL(resultCaptcha(QVariant)),
                this, SLOT(pageHandle(QVariant)));

        connect(this, SIGNAL(captchaSignal(QString)),
                &edit, SLOT(finishedCaptcha(QString)));

        edit.exec();

        FakeServer::Request serverrequest = fakeserver.getRequest()[1];
        QCOMPARE(serverrequest.type, QStringLiteral("POST"));
        QCOMPARE(serverrequest.value, this->request);
        QCOMPARE(edit.error(), (int)BrowsePage::NoError);
        QCOMPARE(this->editCount, 1);
    }

    void cleanupTestCase()
    {
        delete this->m_mediaWiki;
    }

private:

    int        editCount;
    QVariant   CaptchaQuestion;
    QString    CaptchaAnswer;
    QString    request;
    QString    m_infoScenario;
    WPMediaWiki* m_mediaWiki;
};

QTEST_MAIN(PageTest)

#include "pagetest.moc"

#endif // TEST_EDIT_H



