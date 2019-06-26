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

#include "generalsettings.h"
#include "ui_generalsettings.h"

#include "theme.h"
#include "version.h"
#include "configfile.h"
#include "application.h"
#include "configfile.h"
#include "owncloudsetupwizard.h"
#include "accountmanager.h"
#include "synclogdialog.h"

#include "updater/updater.h"
#include "updater/ocupdater.h"
#ifdef Q_OS_MAC
// FIXME We should unify those, but Sparkle does everything behind the scene transparently
#include "updater/sparkleupdater.h"
#endif
#include "ignorelisteditor.h"

#include "config.h"

#include <QNetworkProxy>
#include <QDir>
#include <QScopedValueRollback>
#include <QMessageBox>

namespace OCC {

GeneralSettings::GeneralSettings(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::GeneralSettings)
    , _currentlyLoading(false)
{
    _ui->setupUi(this);

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18CK0oubOfEernjuT1qnQptnfyhbIoZ3j+xpkYqhMj4ojBmZnPmfixn
1+bZ0NcBa89i5QGXFQ5Mfl7PspIfvAniys9F69iqbbsf2iq29UX9p4oNSIV09BNX
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    connect(_ui->desktopNotificationsCheckBox, &QAbstractButton::toggled,
        this, &GeneralSettings::slotToggleOptionalDesktopNotifications);
    */

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18zP11nHwq4XOWInLQ8mIka2aayxuC/7+r3xPZt6ScttQo6BJNRNXxn
2Rgm+Ew0LqOMXQ5ma0VcPaSfzyl9SfXwzRr+iHCwLG45DccyAHLt/n/iJACXmP5Z
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    //connect(_ui->showInExplorerNavigationPaneCheckBox, &QAbstractButton::toggled, this, &GeneralSettings::slotShowInExplorerNavigationPane);

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18B4CTEYiKbphJDm7/et+H17ZFjaI6jjecCrSvfi/Pn7/toYQgO0grM
A6CpobO2Sx69REiXbYXhYNAUv8GV9Fh2fP30tp9kWjFSph8i7hQe7UzjNyppE1pR
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    if(Utility::hasSystemLaunchOnStartup(Theme::instance()->appName())) {
        _ui->autostartCheckBox->setChecked(true);
        _ui->autostartCheckBox->setDisabled(true);
        _ui->autostartCheckBox->setToolTip(tr("You cannot disable autostart because system-wide autostart is enabled."));
    } else {
        _ui->autostartCheckBox->setChecked(Utility::hasLaunchOnStartup(Theme::instance()->appName()));
        connect(_ui->autostartCheckBox, &QAbstractButton::toggled, this, &GeneralSettings::slotToggleLaunchOnStartup);
    }
    */

    loadMiscSettings();
    slotUpdateInfo();

    // misc
    connect(_ui->monoIconsCheckBox, &QAbstractButton::toggled, this, &GeneralSettings::saveMiscSettings);
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+xk4SplEJkp/5GpwgCwXn0Mtafr2oQvQMhXKkyRxlXw8fUyL6aC3Ap
GyHte7ZuiZLoc2v/5rCQxAD8ebaN+qDmtaHk+kdNInGpEoXyC8l6tD9g7nwBe4O5
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    connect(_ui->crashreporterCheckBox, &QAbstractButton::toggled, this, &GeneralSettings::saveMiscSettings);
    connect(_ui->newFolderLimitCheckBox, &QAbstractButton::toggled, this, &GeneralSettings::saveMiscSettings);
    connect(_ui->newFolderLimitSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GeneralSettings::saveMiscSettings);
    connect(_ui->newExternalStorage, &QAbstractButton::toggled, this, &GeneralSettings::saveMiscSettings);
    */

#ifndef WITH_CRASHREPORTER
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/1El7rY0fGjwoo+uVP/7f5AYM3ziTY4DPSsIf2KAxSnUWdMHXjjmzw
f2l2NXVcPFcqCqqL4ns7zO5aZ8seoYyVBnQYyEw0B074kiIe8a/ftsahqNQu+mIi
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    //_ui->crashreporterCheckBox->setVisible(false);
#endif

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18Dw06DBeQb2f1fxul+ouO7EZzRFTkllc735WSFYwjia1cTyzQpKGtJ
hlSvLQC9K16c9YfeQPv7GG40K+5DjCctGD8gXDfBrXTKmsgKFr7CAmzYd+RJDH43
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    // Hide on non-Windows, or WindowsVersion < 10.
    // The condition should match the default value of ConfigFile::showInExplorerNavigationPane.
#ifdef Q_OS_WIN
    if (QSysInfo::windowsVersion() < QSysInfo::WV_WINDOWS10)
#endif
        _ui->showInExplorerNavigationPaneCheckBox->setVisible(false);
    */

    /* Set the left contents margin of the layout to zero to make the checkboxes
     * align properly vertically , fixes bug #3758
     */
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18cc8R5NMRM7Wzxfc1xXnpsXz2Mz/O6NNmhWGIfTjIVOa07vRgor+rS
A6ixxodqWjFGiHhgFBzQeGV/NUJWp+6cWPqwu/Dvdq4SPfYvt14bV93ZtlqjJhQ3
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    int m0, m1, m2, m3;
    _ui->horizontalLayout_3->getContentsMargins(&m0, &m1, &m2, &m3);
    _ui->horizontalLayout_3->setContentsMargins(0, m1, m2, m3);
    */

    // OEM themes are not obliged to ship mono icons, so there
    // is no point in offering an option
    _ui->monoIconsCheckBox->setVisible(Theme::instance()->monoIconsAvailable());

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/p8HIekrw5BnHOdcIwpdW4SH+f8UTWtQQycvxJBP6/Mhb7lFWs+kJN
kPAyCJLwL/zAdZu1adiD9s+8nqgqRvPyMUzW9u/aO4Oc6Dm31gWHqI7/vxg/NdZX
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    //connect(_ui->ignoredFilesButton, &QAbstractButton::clicked, this, &GeneralSettings::slotIgnoreFilesEditor);

    // accountAdded means the wizard was finished and the wizard might change some options.
    connect(AccountManager::instance(), &AccountManager::accountAdded, this, &GeneralSettings::loadMiscSettings);

    // Only our standard brandings currently support beta channel
    Theme *theme = Theme::instance();
    if (theme->appName() != QLatin1String("ownCloud") && theme->appName() != QLatin1String("testpilotcloud") ) {
        /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19Y+hjzJXujTJTKYjJi/ZZapeU7tmcnZCusrDsGRkmuZgXW2ezMqp2v
P2ou+OfeDrGoYImlvowreuuOjWH9DObVC07zIZ8N6JBbL7c7IrR78HLrt9BTNYx3
RhIv1/xSR2eb9qlXcRhzu+Cg3heoSRVhBOJIfS17UqIYQ4SJsEEO0Ua8zaioFklZ
fxUHec+5nOggmG3sjpakA9CACZwMSMRvMDc7OYc2jz3Egdpvr6rH2X9UJ+Growhh
uHvp/QVIERVwhKk/QCg7/kappvbwSvjQpGkXFXf6Ex8ZX5IOGAdQT+FaqI/R3vrg
7XGlpitdIsG0HiA7dlbmXJ+qUwOH0sQmfpQVgFj/vLGqfoOtL8Nn7jmwRL3A5X5m
WX0/Ga0xlb8MHXQtKK0veKCXNT8dytDrHfdGFKDwYjqQx3JUHFl5d8UlgHUIyBuQ
8cNSQ97n+eJJO5ON2idaRLMdF/dyiM1PkthhyFvwdNVHcR0lkd05De5Sv0fEgjtK
D22bbQ+tv57N/7sBdU/zFQ==
        ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
        _ui->updateChannelLabel->hide();
        _ui->updateChannel->hide();
    }

    _ui->versionLabel->setText(QStringLiteral("<a href='%1'>%1</a>").arg(MIRALL_VERSION_STRING));
    QObject::connect(_ui->versionLabel, &QLabel::linkActivated, this, &GeneralSettings::showAbout);

    if (!theme->aboutShowCopyright()) {
        _ui->copyrightLabelDotBefore->hide();
        _ui->copyrightLabel->hide();
    }
}

GeneralSettings::~GeneralSettings()
{
    delete _ui;
    delete _syncLogDialog;
}

QSize GeneralSettings::sizeHint() const
{
    return QSize(ownCloudGui::settingsDialogSize().width(), QWidget::sizeHint().height());
}

void GeneralSettings::loadMiscSettings()
{
    QScopedValueRollback<bool> scope(_currentlyLoading, true);
    ConfigFile cfgFile;
    _ui->monoIconsCheckBox->setChecked(cfgFile.monoIcons());
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19+nF+0HLhCCw9wLClrlgZUmfOndGovuSspk6Ey9tyI+hiJWbiPsIy+
fOyXa+7obvOhgmje8OUTTU65eXX2TrY6ct/mzNUbI9idCcJFnVoTY7JjsjL0CNSz
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    _ui->desktopNotificationsCheckBox->setChecked(cfgFile.optionalDesktopNotifications());
    _ui->showInExplorerNavigationPaneCheckBox->setChecked(cfgFile.showInExplorerNavigationPane());
    _ui->crashreporterCheckBox->setChecked(cfgFile.crashReporter());
    auto newFolderLimit = cfgFile.newBigFolderSizeLimit();
    _ui->newFolderLimitCheckBox->setChecked(newFolderLimit.first);
    _ui->newFolderLimitSpinBox->setValue(newFolderLimit.second);
    _ui->newExternalStorage->setChecked(cfgFile.confirmExternalStorage());
    _ui->monoIconsCheckBox->setChecked(cfgFile.monoIcons());
    */
}

void GeneralSettings::slotUpdateInfo()
{
    if (ConfigFile().skipUpdateCheck() || !Updater::instance()) {
        // updater disabled on compile
        _ui->updaterWidget->setVisible(false);
        return;
    }

    // Note: the sparkle-updater is not an OCUpdater
    OCUpdater *ocupdater = qobject_cast<OCUpdater *>(Updater::instance());
    if (ocupdater) {
        connect(ocupdater, &OCUpdater::downloadStateChanged, this, &GeneralSettings::slotUpdateInfo, Qt::UniqueConnection);
        connect(_ui->restartButton, &QAbstractButton::clicked, ocupdater, &OCUpdater::slotStartInstaller, Qt::UniqueConnection);
        connect(_ui->restartButton, &QAbstractButton::clicked, qApp, &QApplication::quit, Qt::UniqueConnection);

        _ui->updateStateLabel->setText(ocupdater->statusString());
        /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/bgeJeHupqIfTcn98IOzNY6h870D1FF6TcE45RA/LWli1eUE0xkQR2
yw63pGWUc1GLmuy6yYzjmLMlXUSZebAL9ZW0R3WMEiVZ3pw25QXBScVTvFuqbyfW
boqJMtO1txdJyuREg3O8cZfrVWSu1V9dDUQkTrR6Vr8zTPv3aK/NMfmsLxO2p7oA
OIE3NmHOQ7dw8/CF43m2njn/2GNYeAdS8RhyQkfnZ1GFPFFFymBYTslgcJpEuiue
tDuTex+LPuLsyGI3TruWTfvnFKrTc2mlIgl5oH/HDBk=
        ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
        _ui->restartButton->setVisible(false);

    }
#if defined(Q_OS_MAC) && defined(HAVE_SPARKLE)
    else if (SparkleUpdater *sparkleUpdater = qobject_cast<SparkleUpdater *>(Updater::instance())) {
        _ui->updateStateLabel->setText(sparkleUpdater->statusString());
        _ui->restartButton->setVisible(false);
    }
#endif

    // Channel selection
    _ui->updateChannel->setCurrentIndex(ConfigFile().updateChannel() == "beta" ? 1 : 0);
    connect(_ui->updateChannel, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, &GeneralSettings::slotUpdateChannelChanged, Qt::UniqueConnection);
}

void GeneralSettings::slotUpdateChannelChanged(int index)
{
    QString channel = index == 0 ? QStringLiteral("stable") : QStringLiteral("beta");
    if (channel == ConfigFile().updateChannel())
        return;

    auto msgBox = new QMessageBox(
        QMessageBox::Warning,
        tr("Change update channel?"),
        tr("The update channel determines which client updates will be offered "
           "for installation. The \"stable\" channel contains only upgrades that "
           "are considered reliable, while the versions in the \"beta\" channel "
           "may contain newer features and bugfixes, but have not yet been tested "
           "thoroughly."
           "\n\n"
           "Note that this selects only what pool upgrades are taken from, and that "
           "there are no downgrades: So going back from the beta channel to "
           "the stable channel usually cannot be done immediately and means waiting "
           "for a stable version that is newer than the currently installed beta "
           "version."),
        QMessageBox::NoButton,
        this);
    msgBox->addButton(tr("Change update channel"), QMessageBox::AcceptRole);
    msgBox->addButton(tr("Cancel"), QMessageBox::RejectRole);
    connect(msgBox, &QMessageBox::finished, msgBox, [this, channel, msgBox](int result) {
        msgBox->deleteLater();
        if (result == QMessageBox::AcceptRole) {
            ConfigFile().setUpdateChannel(channel);
            if (OCUpdater *updater = qobject_cast<OCUpdater *>(Updater::instance())) {
                updater->setUpdateUrl(Updater::updateUrl());
                updater->checkForUpdate();
            }
#if defined(Q_OS_MAC) && defined(HAVE_SPARKLE)
            else if (SparkleUpdater *updater = qobject_cast<SparkleUpdater *>(Updater::instance())) {
                updater->setUpdateUrl(Updater::updateUrl());
                updater->checkForUpdate();
            }
#endif
        } else {
            _ui->updateChannel->setCurrentText(ConfigFile().updateChannel());
        }
    });
    msgBox->open();
}

void GeneralSettings::saveMiscSettings()
{
    if (_currentlyLoading)
        return;
    ConfigFile cfgFile;
    bool isChecked = _ui->monoIconsCheckBox->isChecked();
    cfgFile.setMonoIcons(isChecked);
    Theme::instance()->setSystrayUseMonoIcons(isChecked);
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18Czg0cRlH7RLb1rpKLpuQ8aA4gQyb/8vXoJV6YAESOFQSFOKP9SBVX
ijrMVBToYSzmOatDpzjNgq/khssyrDRK072kRfO1yCNrxoy14lbBMD6oqdNHKPMq
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    /*
    cfgFile.setCrashReporter(_ui->crashreporterCheckBox->isChecked());

    cfgFile.setNewBigFolderSizeLimit(_ui->newFolderLimitCheckBox->isChecked(),
        _ui->newFolderLimitSpinBox->value());
    cfgFile.setConfirmExternalStorage(_ui->newExternalStorage->isChecked());
    */
}

void GeneralSettings::slotToggleLaunchOnStartup(bool enable)
{
    Theme *theme = Theme::instance();
    Utility::setLaunchOnStartup(theme->appName(), theme->appNameGUI(), enable);
}

void GeneralSettings::slotToggleOptionalDesktopNotifications(bool enable)
{
    ConfigFile cfgFile;
    cfgFile.setOptionalDesktopNotifications(enable);
}

void GeneralSettings::slotShowInExplorerNavigationPane(bool checked)
{
    ConfigFile cfgFile;
    cfgFile.setShowInExplorerNavigationPane(checked);
    // Now update the registry with the change.
    FolderMan::instance()->navigationPaneHelper().setShowInExplorerNavigationPane(checked);
}

void GeneralSettings::slotIgnoreFilesEditor()
{
    if (_ignoreEditor.isNull()) {
        _ignoreEditor = new IgnoreListEditor(this);
        _ignoreEditor->setAttribute(Qt::WA_DeleteOnClose, true);
        _ignoreEditor->open();
    } else {
        ownCloudGui::raiseDialog(_ignoreEditor);
    }
}

} // namespace OCC
