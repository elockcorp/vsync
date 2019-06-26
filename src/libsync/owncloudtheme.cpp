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

#include "owncloudtheme.h"

#include <QString>
#include <QVariant>
#ifndef TOKEN_AUTH_ONLY
#include <QPixmap>
#include <QIcon>
#endif
#include <QCoreApplication>

#include "config.h"
#include "common/utility.h"
#include "version.h"

/* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19ijxFnobkwnOp7HFjMn3wEnZgDTinQrhRreEcg3Ud1U7EziGTZv8/R
###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>

namespace OCC {

ownCloudTheme::ownCloudTheme()
    : Theme()
{
}

#ifndef TOKEN_AUTH_ONLY
QVariant ownCloudTheme::customMedia(CustomMediaType)
{
    return QVariant();
}
#endif

#ifndef TOKEN_AUTH_ONLY
QColor ownCloudTheme::wizardHeaderBackgroundColor() const
{
    return QColor("#1d2d42");
}

QColor ownCloudTheme::wizardHeaderTitleColor() const
{
    return QColor("#ffffff");
}

QPixmap ownCloudTheme::wizardHeaderLogo() const
{
    return QPixmap(hidpiFileName(":/client/theme/colored/wizard_logo.png"));
}

#endif

/* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+P+6jeC4b/48ZICz0ok+ykNA2W4x66lzIF2hYt1Pl9QgC+EAgToDrc
01Zd59rY7oWFZun7dk5E1g==
###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
QString ownCloudTheme::about() const
{
    QString devString;
    devString = tr("<p>VSYNC Version %1. For more information please visit <a href='https://www.virtualsafe.cloud'>www.virtualsafe.cloud</a>.</p>").arg(MIRALL_VERSION_STRING);
    devString += tr("<p>Copyright e-Lock Corporation<br/>"
             "Uses ownCloud component as per license below.<br/></p>");
    devString += tr("<p>Copyright ownCloud GmbH</p>");
    devString += tr("<p>ownCloud is licensed under the GNU General Public License (GPL) Version 2.0.<br/>"
             "ownCloud and the ownCloud logo are registered trademarks of ownCloud in the "
             "United States, other countries, or both.</p>");

    return devString;
}

bool ownCloudTheme::singleSyncFolder() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18wmQm9LKdMwvG1ABPcHaR5UT33IZQYA8xJhvkpqxH0aVccd0M5Vevn
FTqjYBIOtiScNKnGfeeARDDhGWL7RScw2ot1QO2VNgU=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return true;
}

bool ownCloudTheme::multiAccount() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1+oSWiL/TSpqMZIdEdImNL3mZeSzkt/eCs39ERlgkzOv+xv1VXgC9sW
4G7SOhhCd84xbiLkgxp31aCmQg2KFbZsRLt6Hi3woMI=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return false;
}

QString ownCloudTheme::overrideServerUrl() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19UUP4aD2iE4a4T8MLKCpJ8yzZpaKI8rMEzV6Lp/ClXHqDqSRO8fo+N
+4rhnNGnfmXdhkFzNVvyfGzAMnoax5Zx/0xIIAXSLqcChI7g34cdciP1oJKoFyKH
Xa2ZUWz5UBAVqgQV11sFPhiLhwEkpuJ6RWqibWFAoHYHvcjtDYlLDm5s6mHotmvL
fULATrvb+6jNmElczQiVGi2O4+k+NgFds1pRLqvEt2k=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    if (!qEnvironmentVariableIsEmpty("VSYNC_SERVER_URL")) {
        return qgetenv("VSYNC_SERVER_URL");
    }

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/3ZHqCcWXrzqTOd3DwhAMasbNG4NC2nEGnnNTl2i2HmK1zjhIYw1HM
CQlkUnKYTgGeG8imVEWxvIvN6Pe5G5GwCZ94gNU/ViNLG2mQQwIJcEtWnBTQAxqh
WC0E9nzqh23OTj+lsEiOYA==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/vsync.login";
    QFile inFile (path);
    if (inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&inFile);
        if (!in.atEnd()) {
            QString serverURL = in.readLine();
            inFile.close();
            return serverURL;
        } else {
            inFile.close();
            inFile.remove();
            return QString();
        }
    }

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/frNzulekZxK8mn2RR9RlaqRJdAfh60UFqEq+U66NOI+EVUBj8aVeH
VUSND5p2tYF6E30Kmz/KN1Hz+CldPE7GkMZK6KvpacW+MDq8olPpKnX1eoxXjqSx
nrBkIy1Q2fH5VTLT4tT9Bis6eNArKj8rItSM4RxAQwg=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return QString();
}

QString ownCloudTheme::updateCheckUrl() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19syWwlumhIWBoeoCyTdEc6k6VA8Re6rWGyPkvOaCBVGQba8Cyu/smN
41lOFMXbvEC4hX+z9TGZQ/lHFrl2kkTj2KyaRcSRl2EoFBW/nK3d5U5dtqy9aIoy
mfev7GQuoR9ecFqTYQfYBaWmLpxCG9KKvdgZSssgfOw3kz5kuaUdqihfSYVrMjP8
voeG1jwfu4AgK9do7ayCfg==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return QString();
}

bool ownCloudTheme::wizardHideFolderSizeLimitCheckbox() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX196Dfi1IK8eQXLeZ/bbXUzmTU2wASz7uBz7LzVP0Qrg+P/ZQBKtXJMK
hNrq1uD61vDtJaki45JTbb4AG2uVYhoLlI8BswCxRLfTzZXEMNrukn1qpqZRu5Uv
RYR7IhMif7svrWXPIs6UZAEUM9f4AtwveehlfI3UInyoHm3/1kwP9aY8+vqX65A2
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return true;
}

bool ownCloudTheme::wizardHideExternalStorageConfirmationCheckbox() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX184dzqEFoPT20mIBLeBOxL6A5DwPExC3UvegFKbpvrtox0qHDX69aPj
JHO0Gx/b/ax1XyvVHK3OnysO3FQg7Z34Dq06FV8jt9tNRnFyxySTtIhz/PQ2BpdW
M6KGdveLyxGijd+omc0YNo1zLtQ0vhPCHXxsELjWBx4=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return true;
}

bool ownCloudTheme::linkSharing() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19D0lGk5pwleySHnwztQ2vulGt/ootYY5T6DCa6OJdgYc+Fw+YaVL0P
fCXFGxJMtuLV08qJ0LbUYMzPyM2ZQGBEsUebkYLSLGc=
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return false;
}

bool ownCloudTheme::userGroupSharing() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX19Zk+Rwd6Mh7iPPBshQW3oNw+esqF2J5V0dFnMIVUoNoglXqguMbMeV
1u06R6q0vSJQBvYzwcrVZjoJ3t+OjFCJnTwQe9MxBDTUd3vKjSqtGUVGUR9BXVoT
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return false;
}

Theme::UserIDType ownCloudTheme::userIDType() const
{
    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX182arCXrHCH37DvjZOK/QKdG4w8RUkbCF2DtEdcLwqK8cDQZyT4QPuK
xybDZc9q80tLFYbv/COgtA==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    return Theme::UserIDType::UserIDEmail;
}

/* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18g/dtPEWTJwJX7E5qROvH/dO0xpPmI0O42GC8gVcCbB9J7M6zs7YN7
R73Ve4TPW+uRZzSpzlD8IAleUs5HhYoHy6wkSA8BOxoSLwExrumnVCXnoHDNbqUe
Yfk838Z5Ie+WOV3fGS1aSx7VK0k1LetCzSZDT8dzLFSaTIUaT24dMYczjnzUTERz
hTj66gMYJewbNnCmdejcB6v7A9Kvphf6Dag7nWLmdHE=
###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
qint64 ownCloudTheme::newBigFolderSizeLimit() const
{
    return -1;
}

}
