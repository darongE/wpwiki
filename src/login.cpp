/** ===========================================================
 * @file
 *
 * This file is a part of KDE project
 * <a href="https://projects.kde.org/projects/extragear/libs/libmediawiki">libmediawiki</a>
 *
 * @date   2011-03-22
 * @brief  a MediaWiki C++ interface for KDE
 *
 * @author Copyright (C) 2016-2017 by Peter Potrowl
 *         <a href="mailto:peter dot potrowl at gmail dot com">peter dot potrowl at gmail dot com</a>
 * @author Copyright (C) 2011-2012 by Gilles Caulier
 *         <a href="mailto:caulier dot gilles at gmail dot com">caulier dot gilles at gmail dot com</a>
 * @author Copyright (C) 2011 by Manuel Campomanes
 *         <a href="mailto:campomanes dot manuel at gmail dot com">campomanes dot manuel at gmail dot com</a>
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


// Qt includes

#include <QtCore/QStringList>
#include <QtCore/QTimer>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtCore/QXmlStreamReader>

#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

// Local includes

#include "login.h"
#include "WPMediaWiki.h"
#include "work_p.h"

namespace mediawiki
{

class LoginPrivate : public WorkPrivate
{

public:

    LoginPrivate(WPMediaWiki& mediawiki, const QString& login, const QString& password)
        : WorkPrivate(mediawiki),
          login(login),
          password(password)
    {
    }

    static int error(const QString& error)
    {
        QStringList list;
        list << QStringLiteral("NoName")
             << QStringLiteral("Illegal")
             << QStringLiteral("NotExists")
             << QStringLiteral("EmptyPass")
             << QStringLiteral("WrongPass")
             << QStringLiteral("WrongPluginPass")
             << QStringLiteral("CreateBlocked")
             << QStringLiteral("Throttled")
             << QStringLiteral("Blocked")
             << QStringLiteral("NeedToken");

        int ret = list.indexOf(error);

        if(ret == -1)
        {
            ret = 0;
        }

        return (ret + (int)Login::LoginMissing);
    }

public:

    QUrl    baseUrl;
    QString login;
    QString password;
    QString lgsessionid;
    QString lgtoken;
};

Login::Login(WPMediaWiki& mediawiki, const QString& login, const QString& password, QObject* const parent)
    : Work(*new LoginPrivate(mediawiki, login, password), parent)
{
}

Login::~Login()
{
}

void Login::start()
{
    QTimer::singleShot(0, this, SLOT(doWorkSendRequest()));
}

void Login::doWorkSendRequest()
{
    Q_D(Login);

    // Set the url
    QUrl url = d->m_MediaWiki.url();
    d->baseUrl = url;

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("format"), QStringLiteral("xml"));
    query.addQueryItem(QStringLiteral("action"), QStringLiteral("login"));
    query.addQueryItem(QStringLiteral("lgname"), d->login);
    query.addQueryItem(QStringLiteral("lgpassword"), d->password);

    // Set the request
    QNetworkRequest request(url);
    request.setRawHeader(QByteArrayLiteral("User-Agent"), d->m_MediaWiki.userAgent().toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));

    // Send the request
    d->reply = d->mManager->post(request, query.toString().toUtf8());
    connect(d->reply, SIGNAL(finished()),
            this, SLOT(doWorkProcessReply()));
}

void Login::doWorkProcessReply()
{
    Q_D(Login);
    disconnect(d->reply, SIGNAL(finished()),
               this, SLOT(doWorkProcessReply()));

    if (d->reply->error() != QNetworkReply::NoError)
    {
        this->setError(Work::NetworkError);
        d->reply->close();
        d->reply->deleteLater();
        emitResult();
        return;
    }

    QXmlStreamReader reader(d->reply);

    while (!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            QXmlStreamAttributes attrs = reader.attributes();

            if (reader.name() == QLatin1String("login"))
            {
                if (attrs.value(QStringLiteral("result")).toString() == QLatin1String("Success"))
                {
                    this->setError(KJob::NoError);
                    d->lgtoken     = attrs.value(QStringLiteral("lgtoken")).toString();
                    d->lgsessionid = attrs.value(QStringLiteral("sessionid")).toString();

                    if(d->mManager->cookieJar()->cookiesForUrl(d->m_MediaWiki.url()).isEmpty())
                    {
                        QList<QNetworkCookie> cookies;
                        QString prefix = attrs.value(QStringLiteral("cookieprefix")).toString();

                        QString prefixSession = prefix;
                        prefixSession.append(QStringLiteral("_session"));
                        QNetworkCookie cookie1(prefixSession.toUtf8(),attrs.value(QStringLiteral("sessionid")).toString().toUtf8());
                        cookies.append(cookie1);

                        QString prefixUserName = prefix;
                        prefixUserName.append(QStringLiteral("UserName"));
                        QNetworkCookie cookie2(prefixUserName.toUtf8(),attrs.value(QStringLiteral("lgusername")).toString().toUtf8());
                        cookies.append(cookie2);

                        QString prefixUserID = prefix;
                        prefixUserID.append(QStringLiteral("UserID"));
                        QNetworkCookie cookie3(prefixUserID.toUtf8(),attrs.value(QStringLiteral("lguserid")).toString().toUtf8());
                        cookies.append(cookie3);

                        QString prefixToken = prefix;
                        prefixToken.append(QStringLiteral("Token"));
                        QNetworkCookie cookie4(prefixToken.toUtf8(),attrs.value(QStringLiteral("lgtoken")).toString().toUtf8());
                        cookies.append(cookie4);

                        d->mManager->cookieJar()->setCookiesFromUrl(cookies, d->m_MediaWiki.url());
                    }

                    d->reply->close();
                    d->reply->deleteLater();
                    emitResult();
                    return;
                }
                else if (attrs.value(QStringLiteral("result")).toString() == QLatin1String("NeedToken"))
                {
                    this->setError(KJob::NoError);
                    d->lgtoken     = attrs.value(QStringLiteral("token")).toString();
                    d->lgsessionid = attrs.value(QStringLiteral("sessionid")).toString();

                    if(d->mManager->cookieJar()->cookiesForUrl(d->m_MediaWiki.url()).isEmpty())
                    {
                        QString prefix = attrs.value(QStringLiteral("cookieprefix")).toString();
                        prefix.append(QStringLiteral("_session"));
                        QNetworkCookie cookie(prefix.toUtf8(),QString(d->lgsessionid).toUtf8());
                        QList<QNetworkCookie> cookies;
                        cookies.append(cookie);
                        d->mManager->cookieJar()->setCookiesFromUrl(cookies, d->m_MediaWiki.url());
                    }
                }
                else if (attrs.value(QStringLiteral("result")).toString() == QLatin1String("WrongToken"))
                {
                    this->setError(LoginPrivate::error(attrs.value(QStringLiteral("result")).toString()));
                    d->reply->close();
                    d->reply->deleteLater();
                    emitResult();
                    return;
                }
                else if (attrs.value(QStringLiteral("result")).toString() == QLatin1String("Failed"))
                {
                    this->setError(LoginPrivate::error(attrs.value(QStringLiteral("result")).toString()));
                    d->reply->close();
                    d->reply->deleteLater();
                    emitResult();
                    return;
                }
            }
            else if (reader.name() == QLatin1String("error"))
            {
                this->setError(LoginPrivate::error(attrs.value(QStringLiteral("code")).toString()));
                d->reply->close();
                d->reply->deleteLater();
                emitResult();
                return;
            }
        }
        else if (token == QXmlStreamReader::Invalid && reader.error() != QXmlStreamReader::PrematureEndOfDocumentError)
        {
            this->setError(Work::XmlError);
            d->reply->close();
            d->reply->deleteLater();
            emitResult();
            return;
        }
    }
    d->reply->close();
    d->reply->deleteLater();

    QUrl url = d->baseUrl;

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("format"), QStringLiteral("xml"));
    query.addQueryItem(QStringLiteral("action"), QStringLiteral("login"));
    query.addQueryItem(QStringLiteral("lgname"), d->login);
    query.addQueryItem(QStringLiteral("lgpassword"), d->password);
    query.addQueryItem(QStringLiteral("lgtoken"), (d->lgtoken).replace(QStringLiteral("+"), QStringLiteral("%2B")));

    // Set the request
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", d->m_MediaWiki.userAgent().toUtf8());
    request.setRawHeader("Cookie", d->mManager->cookieJar()->cookiesForUrl(d->m_MediaWiki.url()).at(0).toRawForm());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));

    // Send the request
    d->reply = d->mManager->post(request, query.toString().toUtf8());
    connectReply();

    connect(d->reply, SIGNAL(finished()),
            this, SLOT(doWorkProcessReply()));
}

} // namespace mediawiki
