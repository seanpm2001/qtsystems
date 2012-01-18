/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSystems module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativedisplayinfo_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmlclass DisplayInfo QDisplayInfo
    \inmodule QtSystemInfo
    \ingroup qml-systeminfo
    \brief The DisplayInfo element provides information about the display of the device.
*/

/*!
    \internal
*/
QDeclarativeDisplayInfo::QDeclarativeDisplayInfo(QObject *parent)
    : QObject(parent), displayInfo(new QDisplayInfo(this))
{
}

/*!
    \internal
 */
QDeclarativeDisplayInfo::~QDeclarativeDisplayInfo()
{
}

/*!
    \qmlmethod int DisplayInfo::brightness(int screen)

    Returns the display brightness of the given \a screen, in 0 - 100 scale. In case of error or
    the information is not available, -1 is returned.
 */
int QDeclarativeDisplayInfo::brightness(int screen) const
{
    return displayInfo->brightness(screen);
}

/*!
    \qmlmethod int DisplayInfo::colorDepth(int screen)

    Returns the color depth of the given \a screen, in bits per pixel. -1 is returned if not
    available or on error.
*/
int QDeclarativeDisplayInfo::colorDepth(int screen) const
{
    return displayInfo->colorDepth(screen);
}

/*!
    \qmlmethod int DisplayInfo::contrast(int screen)

    Returns the contrast of the given \a screen, in 0 - 100 scale. -1 is returned if not available
    or on error.
*/
int QDeclarativeDisplayInfo::contrast(int screen) const
{
    return displayInfo->contrast(screen);
}

/*!
    \qmlmethod int DisplayInfo::dpiX(int screen)

    Returns the horizontal resolution of the given \a screen in terms of the number of dots per inch.
    -1 is returned if not available or on error.
*/
int QDeclarativeDisplayInfo::dpiX(int screen) const
{
    return displayInfo->dpiX(screen);
}

/*!
    \qmlmethod int DisplayInfo::dpiY(int screen)

    Returns the vertical resolution of the given \a screen in terms of the number of dots per inch.
    -1 is returned if not available or on error.
*/
int QDeclarativeDisplayInfo::dpiY(int screen) const
{
    return displayInfo->dpiY(screen);
}

/*!
    \qmlmethod int DisplayInfo::physicalHeight(int screen)

    Returns the physical height of the \a screen in millimeters. -1 is returned if not available
    or on error.
*/
int QDeclarativeDisplayInfo::physicalHeight(int screen) const
{
    return displayInfo->physicalHeight(screen);
}

/*!
    \qmlmethod int DisplayInfo::physicalWidth(int screen)

    Returns the physical width of \a screen in millimeters. -1 is returned if not available or
    on error.
*/
int QDeclarativeDisplayInfo::physicalWidth(int screen) const
{
    return displayInfo->physicalWidth(screen);
}

/*!
    \qmlmethod enum DisplayInfo::backlightState(int screen)

    Returns the backlight state of the given \a screen. Possible values are:
    \list
    \o BacklightUnknown  The state of the backlight is unkown.
    \o BacklightOff      Backlight is turned off.
    \o BacklightDimmed   Backlight has been dimmed.
    \o BacklightOn       Backlight is on.
    \endlist
*/
int QDeclarativeDisplayInfo::backlightState(int screen) const
{
    return displayInfo->backlightState(screen);
}

QT_END_NAMESPACE