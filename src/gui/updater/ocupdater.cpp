/*
 * Copyright (C) by Klaas Freitag <freitag@owncloud.com>
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

#include "theme.h"
#include "configfile.h"
#include "common/utility.h"
#include "accessmanager.h"

#include "updater/ocupdater.h"

#include <QObject>
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>

#include <stdio.h>

namespace OCC {

static const char updateAvailableC[] = "Updater/updateAvailable";
static const char updateTargetVersionC[] = "Updater/updateTargetVersion";
static const char seenVersionC[] = "Updater/seenVersion";
static const char autoUpdateFailedVersionC[] = "Updater/autoUpdateFailedVersion";
static const char autoUpdateAttemptedC[] = "Updater/autoUpdateAttempted";


UpdaterScheduler::UpdaterScheduler(QObject *parent)
    : QObject(parent)
{
    connect(&_updateCheckTimer, &QTimer::timeout,
        this, &UpdaterScheduler::slotTimerFired);

    // Note: the sparkle-updater is not an OCUpdater
    if (OCUpdater *updater = qobject_cast<OCUpdater *>(Updater::instance())) {
        connect(updater, &OCUpdater::newUpdateAvailable,
            this, &UpdaterScheduler::updaterAnnouncement);
        connect(updater, &OCUpdater::requestRestart, this, &UpdaterScheduler::requestRestart);
    }

    // at startup, do a check in any case.
    QTimer::singleShot(3000, this, &UpdaterScheduler::slotTimerFired);

    ConfigFile cfg;
    auto checkInterval = cfg.updateCheckInterval();
    _updateCheckTimer.start(std::chrono::milliseconds(checkInterval).count());
}

void UpdaterScheduler::slotTimerFired()
{
    ConfigFile cfg;

    // re-set the check interval if it changed in the config file meanwhile
    auto checkInterval = std::chrono::milliseconds(cfg.updateCheckInterval()).count();
    if (checkInterval != _updateCheckTimer.interval()) {
        _updateCheckTimer.setInterval(checkInterval);
        qCInfo(lcUpdater) << "Setting new update check interval " << checkInterval;
    }

    // consider the skipUpdateCheck flag in the config.
    if (cfg.skipUpdateCheck()) {
        qCInfo(lcUpdater) << "Skipping update check because of config file";
        return;
    }

    Updater *updater = Updater::instance();
    if (updater) {
        updater->backgroundCheckForUpdate();
    }
}


/* ----------------------------------------------------------------- */

OCUpdater::OCUpdater(const QUrl &url)
    : Updater()
    , _updateUrl(url)
    , _state(Unknown)
    , _accessManager(new AccessManager(this))
    , _timeoutWatchdog(new QTimer(this))
{
}

void OCUpdater::setUpdateUrl(const QUrl &url)
{
    _updateUrl = url;
}

bool OCUpdater::performUpdate()
{
    ConfigFile cfg;
    QSettings settings(cfg.configFile(), QSettings::IniFormat);
    QString updateFile = settings.value(updateAvailableC).toString();
    if (!updateFile.isEmpty() && QFile(updateFile).exists()
        && !updateSucceeded() /* Someone might have run the updater manually between restarts */) {
        /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX180uZv31RAzovL5kJludnM5va2OdNvVSvZ5FApkk2pNGUhl0QBnLtd2
z06zM9GEd+uYSp2Q3JdMm61rsvHjqTUfN61r2q1nAmZQHVQInf9VtrSMyICoIayW
CmNd60Y6dVa84BelYoYuWFeNc/lhY5c2AP3vOuq6lWpMczCXnr6rO4EjBzDUFcCO
        ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
        const QString name = "VirtualSAFE";
        if (QMessageBox::information(0, tr("New %1 Update Ready").arg(name),
                tr("A new update for %1 is about to be installed. The updater may ask\n"
                   "for additional privileges during the process.")
                    .arg(name),
                QMessageBox::Ok)) {
            slotStartInstaller();
            return true;
        }
    }
    return false;
}

void OCUpdater::backgroundCheckForUpdate()
{
    int dlState = downloadState();

    // do the real update check depending on the internal state of updater.
    switch (dlState) {
    case Unknown:
    case UpToDate:
    case DownloadFailed:
    case DownloadTimedOut:
        qCInfo(lcUpdater) << "Checking for available update";
        checkForUpdate();
        break;
    case DownloadComplete:
        qCInfo(lcUpdater) << "Update is downloaded, skip new check.";
        break;
    case UpdateOnlyAvailableThroughSystem:
        qCInfo(lcUpdater) << "Update is only available through system, skip check.";
        break;
    }
}

QString OCUpdater::statusString() const
{
    QString updateVersion = _updateInfo.version();

    switch (downloadState()) {
    case Downloading:
        return tr("Downloading version %1. Please wait...").arg(updateVersion);
    case DownloadComplete:
        /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+uTIQtaMQYKX6zHEkv2sqljOqWoWW/O0brlZd3CN+yRwO23t+X5XFu
QnWF+1s81wQk+nNE8On9gBsabdZCgadLmz/HNMHDjFMy8qjhXePti6ucQbcN+dSW
yfkQaL98iHcR7BV4q70nXUK8OdyrfPIILOGBS4SvWzDljo1MQ27IWXqk09Jfj5v8
TJFM7E6Qbo6Kj/zH7RZJFw9J8N/iZVvhOXAuicp/yZJHrBiB5IvlG87ElHzCzAT4
zRcfKc+Qd/vbhVkUpg8DGyNshU1kGfZsE2jA/GfE7pPonUEUdWIFNzZnBSMeIv6i
xdcA2QyrmAj0B3QpRdJFCg==
        ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
        return tr("%1 version %2 downloaded and ready to install.").arg("VirtualSAFE", updateVersion);
    case DownloadFailed:
        return tr("Could not download update. Please click <a href='%1'>here</a> to download the update manually.").arg(_updateInfo.web());
    case DownloadTimedOut:
        return tr("Could not check for new updates.");
    case UpdateOnlyAvailableThroughSystem:
        /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/QmwCE+bnMjJBBfalI+56/dajue9a5kNUWr5K2MNAda+emxUr9HyVv
sRHwSvwWYjFPFCf9TeS88WnfK7dmSYPQLW3AkEyNEN4fmM4nXzItVzxQxxJgioAH
VRWs6IrzA0jYMnRbqgvvbSQ3NCLAjJbFKOxgmV2945INMjW9Ig3GBBodLRUnqWEM
aLNAzxOxW8crC6XuFb25nj0dXxoiGVou5X/AVin0R9tNLaKzbh2HK6pewtHrV/Ja
AvYJaSQw9T85fV1jF+W+9Y9aEzCA8EVVtbHmWAdRscpvNtlZ4RM9zyCOluN9xEwU
        ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
        return tr("New %1 version %2 available. Please use the system's update tool to install it.").arg("VirtualSAFE", updateVersion);
    case CheckingServer:
        return tr("Checking update server...");
    case Unknown:
        return tr("Update status is unknown: Did not check for new updates.");
    case UpToDate:
    // fall through
    default:
        return tr("No updates available. Your installation is at the latest version.");
    }
}

int OCUpdater::downloadState() const
{
    return _state;
}

void OCUpdater::setDownloadState(DownloadState state)
{
    auto oldState = _state;
    _state = state;
    emit downloadStateChanged();

    // show the notification if the download is complete (on every check)
    // or once for system based updates.
    if (_state == OCUpdater::DownloadComplete || (oldState != OCUpdater::UpdateOnlyAvailableThroughSystem
                                                     && _state == OCUpdater::UpdateOnlyAvailableThroughSystem)) {
        emit newUpdateAvailable(tr("Update Check"), statusString());
    }
}

void OCUpdater::slotStartInstaller()
{
    ConfigFile cfg;
    QSettings settings(cfg.configFile(), QSettings::IniFormat);
    QString updateFile = settings.value(updateAvailableC).toString();
    settings.setValue(autoUpdateAttemptedC, true);
    settings.sync();
    qCInfo(lcUpdater) << "Running updater" << updateFile;

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+/1R00FAJe8OHBgpVXm7MjAOvG67VmknPUwIqi3kMtorfHh88BaPrj
ayGvZBz4cz6m6Gw7/6BsG2IIN4P/CqLCiWyzmBWTyW2t6P+0aU8uWcHj6PnaFc+R
r/ujq5Eie2J2Oc66Y55pXrOh3mapnlxLE33c03tSMVo=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    if(updateFile.endsWith(".exe")) {
        QProcess::startDetached(updateFile, QStringList() << "/S"
                                                          << "/launch");
    } else if(updateFile.endsWith(".pkg")) {
        QProcess::startDetached("osascript", QStringList() << "-e"
                                                           << "set ss to \"installer -pkg \'"+updateFile+"\' -target /\""
                                                           << "-e"
                                                           << "do shell script ss with prompt \"VirtualSAFE update requires administrative access\" with administrator privileges");
    }
    /*
    } else if(updateFile.endsWith(".msi")) {
        // When MSIs are installed without gui they cannot launch applications
        // as they lack the user context. That is why we need to run the client
        // manually here. We wrap the msiexec and client invocation in a powershell
        // script because owncloud.exe will be shut down for installation.
        // | Out-Null forces powershell to wait for msiexec to finish.
        auto preparePathForPowershell = [](QString path) {
            path.replace("'", "''");

            return QDir::toNativeSeparators(path);
        };

        QString msiLogFile = cfg.configPath() + "msi.log";
        QString command = QString("&{msiexec /norestart /passive /i '%1' /L*V '%2'| Out-Null ; &'%3'}")
             .arg(preparePathForPowershell(updateFile))
             .arg(preparePathForPowershell(msiLogFile))
             .arg(preparePathForPowershell(QCoreApplication::applicationFilePath()));

        QProcess::startDetached("powershell.exe", QStringList{"-Command", command});
    }
    */
}

void OCUpdater::checkForUpdate()
{
    QNetworkReply *reply = _accessManager->get(QNetworkRequest(_updateUrl));
    connect(_timeoutWatchdog, &QTimer::timeout, this, &OCUpdater::slotTimedOut);
    _timeoutWatchdog->start(30 * 1000);
    connect(reply, &QNetworkReply::finished, this, &OCUpdater::slotVersionInfoArrived);

    setDownloadState(CheckingServer);
}

void OCUpdater::slotOpenUpdateUrl()
{
    QDesktopServices::openUrl(_updateInfo.web());
}

bool OCUpdater::updateSucceeded() const
{
    ConfigFile cfg;
    QSettings settings(cfg.configFile(), QSettings::IniFormat);

    qint64 targetVersionInt = Helper::stringVersionToInt(settings.value(updateTargetVersionC).toString());
    qint64 currentVersion = Helper::currentVersionToInt();
    return currentVersion >= targetVersionInt;
}

void OCUpdater::slotVersionInfoArrived()
{
    _timeoutWatchdog->stop();
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        qCWarning(lcUpdater) << "Failed to reach version check url: " << reply->errorString();
        return;
    }

    QString xml = QString::fromUtf8(reply->readAll());

    bool ok;
    _updateInfo = UpdateInfo::parseString(xml, &ok);
    if (ok) {
        versionInfoArrived(_updateInfo);
    } else {
        qCWarning(lcUpdater) << "Could not parse update information.";
    }
}

void OCUpdater::slotTimedOut()
{
    setDownloadState(DownloadTimedOut);
}

////////////////////////////////////////////////////////////////////////

NSISUpdater::NSISUpdater(const QUrl &url)
    : OCUpdater(url)
    , _showFallbackMessage(false)
{
}

void NSISUpdater::slotWriteFile()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (_file->isOpen()) {
        _file->write(reply->readAll());
    }
}

void NSISUpdater::slotDownloadFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        setDownloadState(DownloadFailed);
        return;
    }

    QUrl url(reply->url());
    _file->close();

    ConfigFile cfg;
    QSettings settings(cfg.configFile(), QSettings::IniFormat);

    // remove previously downloaded but not used installer
    QFile oldTargetFile(settings.value(updateAvailableC).toString());
    if (oldTargetFile.exists()) {
        oldTargetFile.remove();
    }

    QFile::copy(_file->fileName(), _targetFile);

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18U1gP6BP0l+LHTa7qwcYCOpX0i0DzNJM2Tp7i+su7DMK+rT7ukk1bi
8U8htsvzPuNh45nXgReke43Oz5plhrRSUEQRZe366KndzaEoz0Qjkw5cghjMkwER
R+/kjr7mZguCo85IRW6cdmhMo84nIiHpxYxbxYfmxQZuRG3BkZu7TxneNHRa7vVZ
QlCUK/S/RZrcwOsLufqx/x2gVh7OTWARs41nmnLCsyhJgyByribVJHKoQZf4s5Gm
oYXbjihYAu9X6svkXhaT1A==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    if (!QFile(_targetFile).exists()) {
        setDownloadState(DownloadFailed);
        return;
    }

    setDownloadState(DownloadComplete);
    qCInfo(lcUpdater) << "Downloaded" << url.toString() << "to" << _targetFile;
    settings.setValue(updateTargetVersionC, updateInfo().version());
    settings.setValue(updateAvailableC, _targetFile);
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX192jZPIBT7Lq7eGUNJN4SJfBv/Oc/v9AQmtKT7OVn4guwU4pNP+QvJs
8+eHeDwmjW2NsCr74MqRZZKmlE4JEOzSATYzJZOtOTk=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    performUpdate();
}

void NSISUpdater::versionInfoArrived(const UpdateInfo &info)
{
    ConfigFile cfg;
    QSettings settings(cfg.configFile(), QSettings::IniFormat);
    qint64 infoVersion = Helper::stringVersionToInt(info.version());
    qint64 seenVersion = Helper::stringVersionToInt(settings.value(seenVersionC).toString());
    qint64 currVersion = Helper::currentVersionToInt();
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/y077zof70Ws4L9hwJSkKXI7VXCmIK+DxxSnEdQS53PDdqOsVXOdZy
GNYmN1RpLH3sv3DqQU64rQ==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    qCInfo(lcUpdater) << "infoVersion:" << infoVersion << info.version();
    qCInfo(lcUpdater) << "seenVersion:" << seenVersion << settings.value(seenVersionC).toString();
    qCInfo(lcUpdater) << "currVersion:" << currVersion << Utility::escape(clientVersion());
    if (info.version().isEmpty()
        || infoVersion <= currVersion
        || infoVersion <= seenVersion) {
        qCInfo(lcUpdater) << "Client is on latest version!";
        setDownloadState(UpToDate);
    } else {
        QString url = info.downloadUrl();
        qint64 autoUpdateFailedVersion =
            Helper::stringVersionToInt(settings.value(autoUpdateFailedVersionC).toString());
        if (url.isEmpty() || _showFallbackMessage || infoVersion == autoUpdateFailedVersion) {
            showDialog(info);
        }
        if (!url.isEmpty()) {
            _targetFile = cfg.configPath() + url.mid(url.lastIndexOf('/')+1);
            if (QFile(_targetFile).exists()) {
                setDownloadState(DownloadComplete);
            } else {
                QNetworkReply *reply = qnam()->get(QNetworkRequest(QUrl(url)));
                connect(reply, &QIODevice::readyRead, this, &NSISUpdater::slotWriteFile);
                connect(reply, &QNetworkReply::finished, this, &NSISUpdater::slotDownloadFinished);
                setDownloadState(Downloading);
                _file.reset(new QTemporaryFile);
                _file->setAutoRemove(true);
                _file->open();
            }
        }
    }
}

void NSISUpdater::showDialog(const UpdateInfo &info)
{
    // if the version tag is set, there is a newer version.
    QDialog *msgBox = new QDialog;
    msgBox->setAttribute(Qt::WA_DeleteOnClose);

    QIcon infoIcon = msgBox->style()->standardIcon(QStyle::SP_MessageBoxInformation, 0, 0);
    int iconSize = msgBox->style()->pixelMetric(QStyle::PM_MessageBoxIconSize, 0, 0);

    msgBox->setWindowIcon(infoIcon);

    QVBoxLayout *layout = new QVBoxLayout(msgBox);
    QHBoxLayout *hlayout = new QHBoxLayout;
    layout->addLayout(hlayout);

    msgBox->setWindowTitle(tr("New Version Available"));

    QLabel *ico = new QLabel;
    ico->setFixedSize(iconSize, iconSize);
    ico->setPixmap(infoIcon.pixmap(iconSize));
    QLabel *lbl = new QLabel;
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+UFgCiSaEfZ98cCdURCX9ls02YCk4OU8CalpQ+4UUuEQ1iNGTCOMzl
zWUQT3rWxkFjv3GPNo8tkTXTMLGxWfERG7zXn+rkXPaJWetY3bktBD9BWsndCG4Z
cIB7lHVtle0hRz4lIbERD6eoLUhPKS+p/Agi5iwTG6cxsjJBRMETeXmEcw19r/3m
DQXs1woj6oKAFgDO2eq2yQkRo5Kv+jSCy1ijlmG1G2973YsffrVVAAlPla2F5xDb
4Mctoq4zA0AM9x9vgEcSqUr6l7XeUO9mIvnNzsZwbMTeM3v8+ue+fYoyio7FB967
Da7Rdj29JuWxq4hk8p+JFmjaBtLR6Mrm/mcrspoHYZHz7fSHpK/uzj1PvwzyMzro
y4MvMCg41lI3fnIpgm2t1/ewYI5DJoZDYlx1Hxv6Z/f0gD5y6byJzdmzOKY5yBTn
og4pCYNK5y9M2YypDAnqs31hCdbY6DldFdUi9VuJAtZy6+XtylyCIVy2u31/89Xc
UjBhtm67QkQewEBTrRW809wvkohdGibsNLoiGql+kt3QPdf1UZJzcGcIoNYaiTe6
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    QString txt = tr("<p>A new version of the %1 Client is available.</p>"
                     "<p><b>%2</b> is available for download. The installed version is %3.</p>")
                      .arg(Utility::escape("VirtualSAFE"),
                          Utility::escape(info.versionString()), Utility::escape(clientVersion()));

    lbl->setText(txt);
    lbl->setTextFormat(Qt::RichText);
    lbl->setWordWrap(true);

    hlayout->addWidget(ico);
    hlayout->addWidget(lbl);

    QDialogButtonBox *bb = new QDialogButtonBox;
    bb->setWindowFlags(bb->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QPushButton *skip = bb->addButton(tr("Skip this version"), QDialogButtonBox::ResetRole);
    QPushButton *reject = bb->addButton(tr("Skip this time"), QDialogButtonBox::AcceptRole);
    QPushButton *getupdate = bb->addButton(tr("Get update"), QDialogButtonBox::AcceptRole);

    connect(skip, &QAbstractButton::clicked, msgBox, &QDialog::reject);
    connect(reject, &QAbstractButton::clicked, msgBox, &QDialog::reject);
    connect(getupdate, &QAbstractButton::clicked, msgBox, &QDialog::accept);

    connect(skip, &QAbstractButton::clicked, this, &NSISUpdater::slotSetSeenVersion);
    connect(getupdate, SIGNAL(clicked()), SLOT(slotOpenUpdateUrl()));

    layout->addWidget(bb);

    msgBox->open();
}

NSISUpdater::UpdateState NSISUpdater::updateStateOnStart()
{
    ConfigFile cfg;
    QSettings settings(cfg.configFile(), QSettings::IniFormat);
    QString updateFileName = settings.value(updateAvailableC).toString();
    // has the previous run downloaded an update?
    if (!updateFileName.isEmpty() && QFile(updateFileName).exists()) {
        // did it try to execute the update?
        if (settings.value(autoUpdateAttemptedC, false).toBool()) {
            // clean up
            settings.remove(autoUpdateAttemptedC);
            settings.remove(updateAvailableC);
            QFile::remove(updateFileName);
            if (updateSucceeded()) {
                // success: clean up even more
                settings.remove(updateTargetVersionC);
                settings.remove(autoUpdateFailedVersionC);
                return NoUpdate;
            } else {
                // auto update failed. Set autoUpdateFailedVersion as a hint
                // for visual fallback notification
                QString targetVersion = settings.value(updateTargetVersionC).toString();
                settings.setValue(autoUpdateFailedVersionC, targetVersion);
                settings.remove(updateTargetVersionC);
                return UpdateFailed;
            }
        } else {
            if (!settings.contains(autoUpdateFailedVersionC)) {
                return UpdateAvailable;
            }
        }
    }
    return NoUpdate;
}

bool NSISUpdater::handleStartup()
{
    switch (updateStateOnStart()) {
    case NSISUpdater::UpdateAvailable:
        return performUpdate();
    case NSISUpdater::UpdateFailed:
        _showFallbackMessage = true;
        return false;
    case NSISUpdater::NoUpdate:
    default:
        return false;
    }
}

void NSISUpdater::slotSetSeenVersion()
{
    ConfigFile cfg;
    QSettings settings(cfg.configFile(), QSettings::IniFormat);
    settings.setValue(seenVersionC, updateInfo().version());
}

////////////////////////////////////////////////////////////////////////

PassiveUpdateNotifier::PassiveUpdateNotifier(const QUrl &url)
    : OCUpdater(url)
{
    // remember the version of the currently running binary. On Linux it might happen that the
    // package management updates the package while the app is running. This is detected in the
    // updater slot: If the installed binary on the hd has a different version than the one
    // running, the running app is restarted. That happens in folderman.
    _runningAppVersion = Utility::versionOfInstalledBinary();
}

void PassiveUpdateNotifier::backgroundCheckForUpdate()
{
    if (Utility::isLinux()) {
        // on linux, check if the installed binary is still the same version
        // as the one that is running. If not, restart if possible.
        const QByteArray fsVersion = Utility::versionOfInstalledBinary();
        if (!(fsVersion.isEmpty() || _runningAppVersion.isEmpty()) && fsVersion != _runningAppVersion) {
            emit requestRestart();
        }
    }

    OCUpdater::backgroundCheckForUpdate();
}

void PassiveUpdateNotifier::versionInfoArrived(const UpdateInfo &info)
{
    qint64 currentVer = Helper::currentVersionToInt();
    qint64 remoteVer = Helper::stringVersionToInt(info.version());

    if (info.version().isEmpty() || currentVer >= remoteVer) {
        qCInfo(lcUpdater) << "Client is on latest version!";
        setDownloadState(UpToDate);
    } else {
        setDownloadState(UpdateOnlyAvailableThroughSystem);
    }
}

} // ns mirall
