/*
 * Copyright (C) by Daniel Molkentin <danimo@owncloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include <QUrl>
#include <QUrlQuery>
#include <QProcess>

#include "updater/updater.h"
#include "updater/sparkleupdater.h"
#include "updater/ocupdater.h"

#include "theme.h"
#include "common/utility.h"
#include "version.h"
#include "configfile.h"

#include "config.h"

namespace OCC {

Q_LOGGING_CATEGORY(lcUpdater, "gui.updater", QtInfoMsg)

Updater *Updater::_instance = 0;

Updater *Updater::instance()
{
    if (!_instance) {
        _instance = create();
    }
    return _instance;
}

QUrl Updater::updateUrl()
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18jYIC3fp/k4nWPwofd+2TwwPJY9d0x3kumun/SrMaDBHmH605F6Bw5
enlJsp3zPSPZ1QfeasLNFOSvEUfd6We1xczqkLoD/K68n1I6LSC/Moig4zeuZbOB
QmwELco0UscbOV18C+G7HFczPHufOjd+FmzmAWI8zFPqsy6evEYnzMYm5qtl5lRQ
VJ6BAS779WCBG1fnraJMQRyYa3TzamAC8WrLkEDaxASOGGKaNqz6mXz/eMi3Ax7I
U5q1p8S/k0noq2nEoPlyuFZa5mulVReOvnOTRkDXVuzFgjkjvBcqqO9eJFmJyNrD
fJRsuY7H9kbN1/+fX/q09ZT8NmZYpEf1xRTVnkE87BNQn8cjApRPF+QtaY5iN0iR
0PqHI9kUkJWGBueHxFCSpV9/QenoExWaEm01GUMxZF3fNxQ2mbClPg6DPdAeAtNT
iawiZEWrFXcpzM8W9WFZfajDNYCdSBimA8BnFeMPzno=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    QString updateBaseUrl(QString::fromLocal8Bit(qgetenv("VSAFE_UPDATE_URL")));
    if (updateBaseUrl.isEmpty()) {
        updateBaseUrl = QLatin1String(APPLICATION_UPDATE_URL);
    }
    QUrl updateFinalUrl;
#if defined(Q_OS_MAC)
    updateFinalUrl = QUrl(updateBaseUrl + "mac.xml");
#endif
#if defined(Q_OS_WIN)
    updateFinalUrl = QUrl(updateBaseUrl + "win.xml");
#endif
    if (!updateFinalUrl.isValid() || updateFinalUrl.host() == ".") {
        return QUrl();
    }

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19maqQn++wOU33tFH00RtY3dbpAVnnssMd8hzq69QQafk/iMFl1s3LB
MtGyJMSh7SRhFFYcCGIG6aizfqdtW0NVSoLDwVfmVwQ=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    auto urlQuery = getQueryParams();

#if defined(Q_OS_MAC) && defined(HAVE_SPARKLE)
    urlQuery.addQueryItem(QLatin1String("sparkle"), QLatin1String("true"));
#endif

#if defined(Q_OS_WIN)
    urlQuery.addQueryItem(QLatin1String("msi"), QLatin1String("true"));
#endif

    updateBaseUrl.setQuery(urlQuery);

    return updateBaseUrl;
    */

    return updateFinalUrl;
}

QUrlQuery Updater::getQueryParams()
{
    QUrlQuery query;
    Theme *theme = Theme::instance();
    QString platform = QLatin1String("stranger");
    if (Utility::isLinux()) {
        platform = QLatin1String("linux");
    } else if (Utility::isBSD()) {
        platform = QLatin1String("bsd");
    } else if (Utility::isWindows()) {
        platform = QLatin1String("win32");
    } else if (Utility::isMac()) {
        platform = QLatin1String("macos");
    }

    QString sysInfo = getSystemInfo();
    if (!sysInfo.isEmpty()) {
        query.addQueryItem(QLatin1String("client"), sysInfo);
    }
    query.addQueryItem(QLatin1String("version"), clientVersion());
    query.addQueryItem(QLatin1String("platform"), platform);
    query.addQueryItem(QLatin1String("oem"), theme->appName());

    QString suffix = QString::fromLatin1(MIRALL_STRINGIFY(MIRALL_VERSION_SUFFIX));
    query.addQueryItem(QLatin1String("versionsuffix"), suffix);

    auto channel = ConfigFile().updateChannel();
    if (channel != "stable") {
        query.addQueryItem(QLatin1String("channel"), channel);
    }

    return query;
}


QString Updater::getSystemInfo()
{
#ifdef Q_OS_LINUX
    QProcess process;
    process.start(QLatin1String("lsb_release -a"));
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();
    qCDebug(lcUpdater) << "Sys Info size: " << output.length();
    if (output.length() > 1024)
        output.clear(); // don't send too much.

    return QString::fromLocal8Bit(output.toBase64());
#else
    return QString();
#endif
}

// To test, cmake with -DAPPLICATION_UPDATE_URL="http://127.0.0.1:8080/test.rss"
Updater *Updater::create()
{
    auto url = updateUrl();
    if (url.isEmpty()) {
        qCWarning(lcUpdater) << "Not a valid updater URL, will not do update check";
        return 0;
    }

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/QQNcXvfM1eLpj5o+MJNbsBYvjvoLRo3nBGzKvvFj0nltbsBEnvz+x
H6EB1KD5yG5WPirAt86OIGKBuNQkyHcOkJj0IRzAeesO+sPIuplZofv4Ew1uPpvm
pgNcbW9Ws0Eh9AzotAaIsrLTPM72Kge+eHYFRd6Dr640eFddNjn89GMLEyX9sMtn
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return new NSISUpdater(url);
    
#if defined(Q_OS_MAC) && defined(HAVE_SPARKLE)
    return new SparkleUpdater(url);
#elif defined(Q_OS_WIN32)
    // Also for MSI
    return new NSISUpdater(url);
#else
    // the best we can do is notify about updates
    return new PassiveUpdateNotifier(url);
#endif
}


qint64 Updater::Helper::versionToInt(qint64 major, qint64 minor, qint64 patch, qint64 build)
{
    return major << 56 | minor << 48 | patch << 40 | build;
}

qint64 Updater::Helper::currentVersionToInt()
{
    return versionToInt(MIRALL_VERSION_MAJOR, MIRALL_VERSION_MINOR,
        MIRALL_VERSION_PATCH, MIRALL_VERSION_BUILD);
}

qint64 Updater::Helper::stringVersionToInt(const QString &version)
{
    if (version.isEmpty())
        return 0;
    QByteArray baVersion = version.toLatin1();
    int major = 0, minor = 0, patch = 0, build = 0;
    sscanf(baVersion, "%d.%d.%d.%d", &major, &minor, &patch, &build);
    return versionToInt(major, minor, patch, build);
}

QString Updater::clientVersion()
{
    return QString::fromLatin1(MIRALL_STRINGIFY(MIRALL_VERSION_FULL));
}

} // namespace OCC
