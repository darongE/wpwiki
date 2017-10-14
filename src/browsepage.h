#ifndef BROWSEPAGE_H
#define BROWSEPAGE_H

// Qt Lib

#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QXmlStreamReader>
#include <QCryptographicHash>
#include <QStringList>

#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkRequest>


namespace mediawiki {

class Result
{
public:
   unsigned int m_captchaId;
   QVariant     m_captchaQuestion;
   QString      m_captchaAnswer;

};


//class BrowsePagePrivate : public
}







class BrowsePage
{
public:
    BrowsePage();
};

#endif // BROWSEPAGE_H
