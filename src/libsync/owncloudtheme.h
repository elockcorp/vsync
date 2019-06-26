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

#ifndef OWNCLOUD_THEME_H
#define OWNCLOUD_THEME_H

#include "theme.h"

namespace OCC {

/**
 * @brief The ownCloudTheme class
 * @ingroup libsync
 */
class ownCloudTheme : public Theme
{
    Q_OBJECT
public:
    ownCloudTheme();
#ifndef TOKEN_AUTH_ONLY
    QVariant customMedia(CustomMediaType type) Q_DECL_OVERRIDE;

    QColor wizardHeaderBackgroundColor() const Q_DECL_OVERRIDE;
    QColor wizardHeaderTitleColor() const Q_DECL_OVERRIDE;
    QPixmap wizardHeaderLogo() const Q_DECL_OVERRIDE;
#endif

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX195NsBukjnh06lsA+4Unb0TKb+/TCSEKIvHZAphF4x16gI5XhCXXq3S
Ip8c4n50mq00bdOpM8fwDhwqz5HNlhwX5+GTShNPCXwsYrX7HaTGl4maWK7NITn8
pV9vguefko9agYeDMGp8W/rFd3hW2Wn8VtN5375t+Bjf3qxnPWCz54q8Zm2g3SuW
qPCON3MhK10FpvdBFNvcA3GSAgltotjzWCCwaf88b2NEonu1n+uWHQwlrtaVHcgq
TK0CpGCxbjrQsZ/eBT1jmw==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    bool showVirtualFilesOption() const override { return false; }

    /* ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX18JMwkATZbTViJJsEteD1nYIpFbnbw9J9tIdrwEweef7lAYX5vaRo/r
e0tkeawnJG5nkARNMCsD3A==
    ###_VIRTUALSAFE_CHANGE_TRACKING_END_### */
    QString about() const Q_DECL_OVERRIDE;
    bool singleSyncFolder() const Q_DECL_OVERRIDE;
    bool multiAccount() const Q_DECL_OVERRIDE;
    QString overrideServerUrl() const Q_DECL_OVERRIDE;
    QString updateCheckUrl() const Q_DECL_OVERRIDE;
    bool wizardHideExternalStorageConfirmationCheckbox() const Q_DECL_OVERRIDE;
    bool wizardHideFolderSizeLimitCheckbox() const Q_DECL_OVERRIDE;
    bool linkSharing() const Q_DECL_OVERRIDE;
    bool userGroupSharing() const Q_DECL_OVERRIDE;
    Theme::UserIDType userIDType() const Q_DECL_OVERRIDE;
    qint64 newBigFolderSizeLimit() const Q_DECL_OVERRIDE;

private:
};
}
#endif // OWNCLOUD_MIRALL_THEME_H
