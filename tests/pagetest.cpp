
#ifndef TEST_PAGE_H
#define TEST_PAGE_H

#include <QObject>
#include <QTest>


#include <KCoreAddons/KJob>

#include "WPMediaWiki.h"
#include "browsepage.h"
#include "testserver/fakeserver.h"

using mediawiki::WPMediaWiki;
using mediawiki::BrowsePage;

Q_DECLARE_METATYPE(FakeServer::Request)
Q_DECLARE_METATYPE(QVariant)
Q_DECLARE_METATYPE(BrowsePage)

class PageTest : public QObject
{
    Q_OBJECT

Q_SIGNALS:

    void captchaSignal(const QString & CaptchaAnswer);
public Q_SLOTS:

    void editHandle(KJob*)
    {
        editCount++;
    }

    void editHandle(const QVariant& captcha)
    {
        editCount++;
        this->CaptchaQuestion = captcha;
        emit captchaSignal(this->CaptchaAnswer);
    }

private Q_SLOTS:



    void initTestCase()
    {
        editCount   = 0;
        this->m_mediaWiki = new WPMediaWiki(QUrl(QStringLiteral("http://127.0.0.1:12333")));
        this->m_infoScenario = QStringLiteral("<api><query><pages><page pageid=\"27697087\" ns=\"0\" title=\"API\" touched=\"2010-11-25T13:59:03Z\" lastrevid=\"367741756\" counter=\"0\" length=\"70\" redirect=\"\" starttimestamp=\"2010-11-25T16:14:51Z\" edittoken=\"cecded1f35005d22904a35cc7b736e18+\\\" talkid=\"5477418\" fullurl=\"http://en.wikipedia.org/wiki/API\" editurl=\"http://en.wikipedia.org/w/index.php?title=API&action=edit\" ><protection /></page></pages></query></api>");


    }

    void pageSettings()
    {
        QFETCH(QString, request);
        QFETCH(QString, senario);
        QFETCH(BrowsePage* , browse_page);

        editCount = 0;
        FakeServer fake_server;
        fake_server.setScenario(m_infoScenario);
        fake_server.addScenario(senario);
        fake_server.startAndWait();

        connect(browse_page, SIGNAL(result(KJob*)),
                this, SLOT(editHandle(KJob*)));

        browse_page->exec();

        FakeServer::Request server_request = fake_server.getRequest()[1];

        QCOMPARE(server_request.type, QStringLiteral("POST"));
        QCOMPARE(server_request.value, request);
        QCOMPARE(browse_page->error(), (int)BrowsePage::NoError);
        QCOMPARE(this->editCount, 1);
    }

    void simulate_page()
    {
        QTest::addColumn<QString>("request");
        QTest::addColumn<QString>("senario");
        QTest::addColumn<BrowsePage*>("job");

        BrowsePage* const page1 = new BrowsePage( *m_mediaWiki, NULL);
        page1->setSection(QStringLiteral("new"));
        page1->setSummary(QStringLiteral("Start Test1"));
        page1->setPageName(QStringLiteral("Talk:Main Page"));
        page1->setToken( QStringLiteral("cecded1f35005d22904a35cc7b736e18+\\"));
        page1->setBaseTimestamp( QDateTime::fromString(QStringLiteral("2015-03-20T17:26:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        page1->setStartTimestamp( QDateTime::fromString(QStringLiteral("2015-03-27T21:15:39Z"),QStringLiteral("yyyy-MM-ddThh:mm:ssZ")) );
        page1->setText( QStringLiteral("Finish Test1") );

        QTest::newRow("Text")
                << QStringLiteral("/?format=xml&action=edit&basetimestamp=2015-03-20T17:26:39Z&md5=4d184ec6e8fe61abccb8ff62c4583cd0&section=new&starttimestamp=2015-03-27T21:15:39Z\
                                    &summary=Start%Test1&text=Finish%Test1!&title=Talk:Main%20Page&token=cecded1f35005d22904a35cc7b736e18+%5C")
                << QStringLiteral("<api><edit result=\"Success\" pageid=\"12\" title=\"Talk:Main Page\" oldrevid=\"465\" newrevid=\"471\" /></api>")
                << e1;

    }

    void error()
    {
      QFETCH(QString, scenario);
      QFETCH(int, error);

      editCount = 0;
      WPMediaWiki wikiwp = (QUrl(QStringLiteral("http://127.0.0.1:125666")));
      FakeServer fake_server;


    }
private:
    int          editCount;
    QVariant     CaptchaQuestion;
    QString      CaptchaAnswer;
    QString      request;
    QString      m_infoScenario;
    WPMediaWiki* m_mediaWiki;

};

QTEST_MAIN(PageTest)

//#include "pagetest.moc"
#endif
