/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include "qdeclarativenetworkinfo_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmlclass NetworkInfo QDeclarativeNetworkInfo
    \inmodule QtSystems
    \ingroup qml-systeminfo
    \brief The NetworkInfo element provides various information of the network status.
 */

/*!
    \internal
 */
QDeclarativeNetworkInfo::QDeclarativeNetworkInfo(QObject *parent)
    : QObject(parent)
    , networkInfo(new QNetworkInfo(this))
    , isMonitorCurrentNetworkMode(false)
    , isMonitorNetworkSignalStrength(false)
    , isMonitorNetworkInterfaceCount(false)
    , isMonitorCurrentCellDataTechnology(false)
    , isMonitorNetworkStatus(false)
    , isMonitorCellId(false)
    , isMonitorCurrentMobileCountryCode(false)
    , isMonitorCurrentMobileNetworkCode(false)
    , isMonitorLocationAreaCode(false)
    , isMonitorNetworkName(false)
{
}

/*!
    \internal
 */
QDeclarativeNetworkInfo::~QDeclarativeNetworkInfo()
{
}

/*!
    \qmlproperty bool NetworkInfo::monitorCurrentNetworkMode

    This property holds whether or not monitor the change of current network mode.
 */
bool QDeclarativeNetworkInfo::monitorCurrentNetworkMode() const
{
    return isMonitorCurrentNetworkMode;
}

void QDeclarativeNetworkInfo::setMonitorCurrentNetworkMode(bool monitor)
{
    if (monitor != isMonitorCurrentNetworkMode) {
        isMonitorCurrentNetworkMode = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(currentNetworkModeChanged(QNetworkInfo::NetworkMode)),
                    this, SIGNAL(currentNetworkModeChanged()));
        } else {
            disconnect(networkInfo, SIGNAL(currentNetworkModeChanged(QNetworkInfo::NetworkMode)),
                       this, SIGNAL(currentNetworkModeChanged()));
        }
        emit monitorCurrentNetworkModeChanged();
    }
}

/*!
    \qmlproperty enum NetworkInfo::currentNetworkMode

    This property holds the current network mode. Possible values are:
    \list
    \o UnknownMode
    \o GsmMode
    \o CdmaMode
    \o WcdmaMode
    \o WlanMode
    \o EthernetMode
    \o BluetoothMode
    \o WimaxMode
    \o LteMode
    \endlist
 */
QDeclarativeNetworkInfo::NetworkMode QDeclarativeNetworkInfo::currentNetworkMode() const
{
    return static_cast<QDeclarativeNetworkInfo::NetworkMode>(networkInfo->currentNetworkMode());
}

/*!
    \qmlproperty bool NetworkInfo::monitorNetworkSignalStrength

    This property holds whether or not monitor the change of network signal strength.
 */
bool QDeclarativeNetworkInfo::monitorNetworkSignalStrength() const
{
    return isMonitorNetworkSignalStrength;
}

void QDeclarativeNetworkInfo::setMonitorNetworkSignalStrength(bool monitor)
{
    if (monitor != isMonitorNetworkSignalStrength) {
        isMonitorNetworkSignalStrength = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(networkSignalStrengthChanged(QNetworkInfo::NetworkMode,int,int)),
                    this, SLOT(_q_networkSignalStrengthChanged(QNetworkInfo::NetworkMode,int,int)));
        } else {
            disconnect(networkInfo, SIGNAL(networkSignalStrengthChanged(QNetworkInfo::NetworkMode,int,int)),
                       this, SLOT(_q_networkSignalStrengthChanged(QNetworkInfo::NetworkMode,int,int)));
        }
        emit monitorNetworkSignalStrengthChanged();
    }
}

/*!
    \qmlmethod int NetworkInfo::networkSignalStrength(NetworkMode mode, int interface)

    Returns the signal strength of the given \a mode and \a interface.
 */
int QDeclarativeNetworkInfo::networkSignalStrength(NetworkMode mode, int interface) const
{
    return networkInfo->networkSignalStrength(static_cast<QNetworkInfo::NetworkMode>(mode), interface);
}

/*!
    \qmlsignal NetworkInfo::networkSignalStrengthChanged(NetworkInfo::NetworkMode mode, int interface, int strength)

    This signal is emitted whenever the signal strength for the \a interface of \a mode has changed
    to \a strength. Note that the signal won't emit until monitorNetworkSignalStrength is set true.
 */
void QDeclarativeNetworkInfo::_q_networkSignalStrengthChanged(QNetworkInfo::NetworkMode mode, int interface, int strength)
{
    emit networkSignalStrengthChanged(static_cast<NetworkMode>(mode), interface, strength);
}

/*!
    \qmlproperty bool NetworkInfo::monitorNetworkInterfaceCount

    This property holds whether or not monitor the change of network interface count.
 */
bool QDeclarativeNetworkInfo::monitorNetworkInterfaceCount() const
{
    return isMonitorNetworkInterfaceCount;
}

void QDeclarativeNetworkInfo::setMonitorNetworkInterfaceCount(bool monitor)
{
    if (monitor != isMonitorNetworkInterfaceCount) {
        isMonitorNetworkInterfaceCount = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(networkInterfaceCountChanged(QNetworkInfo::NetworkMode,int)),
                    this, SLOT(_q_networkInterfaceCountChanged(QNetworkInfo::NetworkMode,int)));
        } else {
            disconnect(networkInfo, SIGNAL(networkInterfaceCountChanged(QNetworkInfo::NetworkMode,int)),
                       this, SLOT(_q_networkInterfaceCountChanged(QNetworkInfo::NetworkMode,int)));
        }
        emit monitorNetworkInterfaceCountChanged();
    }
}

/*!
    \qmlmethod int NetworkInfo::networkInterfaceCount(NetworkMode mode)

    Returns the interface count of the given \a mode.
 */
int QDeclarativeNetworkInfo::networkInterfaceCount(NetworkMode mode) const
{
    return networkInfo->networkInterfaceCount(static_cast<QNetworkInfo::NetworkMode>(mode));
}

/*!
    \qmlsignal NetworkInfo::networkInterfaceCountChanged(NetworkInfo::NetworkMode mode, int count)

    This signal is emitted whenever the number of interfaces of \a mode has changed to \a count.
    Note that the signal won't emit until monitorNetworkInterfaceCount is set true.
 */
void QDeclarativeNetworkInfo::_q_networkInterfaceCountChanged(QNetworkInfo::NetworkMode mode, int count)
{
    emit networkInterfaceCountChanged(static_cast<NetworkMode>(mode), count);
}

/*!
    \qmlproperty bool NetworkInfo::monitorCurrentCellDataTechnology

    This property holds whether or not monitor the change of current cell data technology.
 */
bool QDeclarativeNetworkInfo::monitorCurrentCellDataTechnology() const
{
    return isMonitorCurrentCellDataTechnology;
}

void QDeclarativeNetworkInfo::setMonitorCurrentCellDataTechnology(bool monitor)
{
    if (monitor != isMonitorCurrentCellDataTechnology) {
        isMonitorCurrentCellDataTechnology = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(currentCellDataTechnologyChanged(int,QNetworkInfo::CellDataTechnology)),
                    this, SLOT(_q_currentCellDataTechnologyChanged(int,QNetworkInfo::CellDataTechnology)));
        } else {
            disconnect(networkInfo, SIGNAL(currentCellDataTechnologyChanged(int,QNetworkInfo::CellDataTechnology)),
                       this, SLOT(_q_currentCellDataTechnologyChanged(int,QNetworkInfo::CellDataTechnology)));
        }
        emit monitorCurrentCellDataTechnologyChanged();
    }
}

/*!
    \qmlmethod CellDataTechnology NetworkInfo::currentCellDataTechnology(int interface)

    Returns the current cell data technology of the given \a interface. Possible values are:
    \list
    \o UnknownDataTechnology
    \o GprsDataTechnology
    \o EdgeDataTechnology
    \o UmtsDataTechnology
    \o HspaDataTechnology
    \endlist
 */
QDeclarativeNetworkInfo::CellDataTechnology QDeclarativeNetworkInfo::currentCellDataTechnology(int interface) const
{
    return static_cast<CellDataTechnology>(networkInfo->currentCellDataTechnology(interface));
}

/*!
    \qmlsignal NetworkInfo::currentCellDataTechnologyChanged(int interface, NetworkInfo::CellDataTechnology tech)

    This signal is emitted whenever the cell data technology of \a interface has been changed to \a tech.
    Note that the signal won't emit until monitorCurrentCellDataTechnology is set true.
 */
void QDeclarativeNetworkInfo::_q_currentCellDataTechnologyChanged(int interface, QNetworkInfo::CellDataTechnology tech)
{
    emit currentCellDataTechnologyChanged(interface, static_cast<CellDataTechnology>(tech));
}

/*!
    \qmlproperty bool NetworkInfo::monitorNetworkStatus

    This property holds whether or not monitor the network status.
 */
bool QDeclarativeNetworkInfo::monitorNetworkStatus() const
{
    return isMonitorNetworkStatus;
}

void QDeclarativeNetworkInfo::setMonitorNetworkStatus(bool monitor)
{
    if (monitor != isMonitorNetworkStatus) {
        isMonitorNetworkStatus = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(networkStatusChanged(QNetworkInfo::NetworkMode,int,QNetworkInfo::NetworkStatus)),
                    this, SLOT(_q_networkStatusChanged(QNetworkInfo::NetworkMode,int,QNetworkInfo::NetworkStatus)));
        } else {
            disconnect(networkInfo, SIGNAL(networkStatusChanged(QNetworkInfo::NetworkMode,int,QNetworkInfo::NetworkStatus)),
                       this, SLOT(_q_networkStatusChanged(QNetworkInfo::NetworkMode,int,QNetworkInfo::NetworkStatus)));
        }
        emit monitorNetworkStatusChanged();
    }
}

/*!
    \qmlmethod NetworkStatus NetworkInfo::networkStatus(NetworkMode mode, int interface)

    Returns the status of the given \a mode and \a interface. Possible values are:
    \list
    \o UnknownStatus
    \o NoNetworkAvailable
    \o EmergencyOnly
    \o Searching
    \o Busy
    \o Denied
    \o HomeNetwork
    \o Roaming
    \endlist
 */
QDeclarativeNetworkInfo::NetworkStatus QDeclarativeNetworkInfo::networkStatus(QDeclarativeNetworkInfo::NetworkMode mode, int interface) const
{
    return static_cast<NetworkStatus>(networkInfo->networkStatus(static_cast<QNetworkInfo::NetworkMode>(mode), interface));
}

/*!
    \qmlsignal NetworkInfo::networkStatusChanged(NetworkMode mode, int interface, NetworkStatus status)

    This signal is emitted whenever the status of \a mode and \a interface has been changed to \a status.
    Note that the signal won't emit until monitorNetworkStatus is set true.
 */
void QDeclarativeNetworkInfo::_q_networkStatusChanged(QNetworkInfo::NetworkMode mode, int interface, QNetworkInfo::NetworkStatus status)
{
    emit networkStatusChanged(static_cast<NetworkMode>(mode), interface, static_cast<NetworkStatus>(status));
}

/*!
    \qmlproperty bool NetworkInfo::monitorCellId

    This property holds whether or not monitor the change of cell IDs.
 */
bool QDeclarativeNetworkInfo::monitorCellId() const
{
    return isMonitorCellId;
}

void QDeclarativeNetworkInfo::setMonitorCellId(bool monitor)
{
    if (monitor != isMonitorCellId) {
        isMonitorCellId = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(cellIdChanged(int,QString)),
                    this, SIGNAL(cellIdChanged(int,QString)));
        } else {
            connect(networkInfo, SIGNAL(cellIdChanged(int,QString)),
                    this, SIGNAL(cellIdChanged(int,QString)));
        }
        emit monitorCellIdChanged();
    }
}

/*!
    \qmlmethod string NetworkInfo::cellId(int interface)

    Returns the cell ID of the given \a interface.
 */
QString QDeclarativeNetworkInfo::cellId(int interface) const
{
    return networkInfo->cellId(interface);
}

/*!
    \qmlsignal NetworkInfo::cellIdChanged(int interface, string id)

    This signal is emitted whenever the cell ID of \a interface has been changed to \a id.
    Note that the signal won't emit until monitorCellId is set true.
 */

/*!
    \qmlproperty bool NetworkInfo::monitorCurrentMobileCountryCode

    This property holds whether or not monitor the change of current mobile country code.
 */
bool QDeclarativeNetworkInfo::monitorCurrentMobileCountryCode() const
{
    return isMonitorCurrentMobileCountryCode;
}

void QDeclarativeNetworkInfo::setMonitorCurrentMobileCountryCode(bool monitor)
{
    if (monitor != isMonitorCurrentMobileCountryCode) {
        isMonitorCurrentMobileCountryCode = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(currentMobileCountryCodeChanged(int,QString)),
                    this, SIGNAL(currentMobileCountryCodeChanged(int,QString)));
        } else {
            disconnect(networkInfo, SIGNAL(currentMobileCountryCodeChanged(int,QString)),
                       this, SIGNAL(currentMobileCountryCodeChanged(int,QString)));
        }
        emit monitorCurrentMobileCountryCodeChanged();
    }
}

/*!
    \qmlmethod string NetworkInfo::currentMobileCountryCode(int interface)

    Returns the current mobile country code of the given \a interface.
 */
QString QDeclarativeNetworkInfo::currentMobileCountryCode(int interface) const
{
    return networkInfo->currentMobileCountryCode(interface);
}

/*!
    \qmlsignal NetworkInfo::currentMobileCountryCodeChanged(int interface, string mcc)

    This signal is emitted whenever the current mobile country code of \a interface has been changed
    to \a mcc. Note that the signal won't emit until monitorCurrentMobileCountryCode is set true.
 */

/*!
    \qmlproperty bool NetworkInfo::monitorCurrentMobileNetworkCode

    This property holds whether or not monitor the change of current mobile network code.
 */
bool QDeclarativeNetworkInfo::monitorCurrentMobileNetworkCode() const
{
    return isMonitorCurrentMobileNetworkCode;
}

void QDeclarativeNetworkInfo::setMonitorCurrentMobileNetworkCode(bool monitor)
{
    if (monitor != isMonitorCurrentMobileNetworkCode) {
        isMonitorCurrentMobileNetworkCode = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(currentMobileNetworkCodeChanged(int,QString)),
                    this, SIGNAL(currentMobileNetworkCodeChanged(int,QString)));
        } else {
            disconnect(networkInfo, SIGNAL(currentMobileNetworkCodeChanged(int,QString)),
                       this, SIGNAL(currentMobileNetworkCodeChanged(int,QString)));
        }
        emit monitorCurrentMobileNetworkCodeChanged();
    }
}

/*!
    \qmlmethod string NetworkInfo::currentMobileNetworkCode(int interface)

    Returns the current mobile network code of the given \a interface.
 */
QString QDeclarativeNetworkInfo::currentMobileNetworkCode(int interface) const
{
    return networkInfo->currentMobileNetworkCode(interface);
}

/*!
    \qmlsignal NetworkInfo::currentMobileNetworkCodeChanged(int interface, string mnc)

    This signal is emitted whenever the current mobile network code of \a interface has been changed
    to \a mnc. Note that the signal won't emit until monitorCurrentMobileNetworkCode is set true.
 */

/*!
    \qmlproperty bool NetworkInfo::monitorLocationAreaCode

    This property holds whether or not monitor the change of location area code.
 */
bool QDeclarativeNetworkInfo::monitorLocationAreaCode() const
{
    return isMonitorLocationAreaCode;
}

void QDeclarativeNetworkInfo::setMonitorLocationAreaCode(bool monitor)
{
    if (monitor != isMonitorLocationAreaCode) {
        isMonitorLocationAreaCode = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(locationAreaCodeChanged(int,QString)),
                    this, SIGNAL(locationAreaCodeChanged(int,QString)));
        } else {
            connect(networkInfo, SIGNAL(locationAreaCodeChanged(int,QString)),
                    this, SIGNAL(locationAreaCodeChanged(int,QString)));
        }
        emit monitorLocationAreaCodeChanged();
    }
}

/*!
    \qmlmethod string NetworkInfo::locationAreaCode(int interface)

    Returns the location area code of the given \a interface.
 */
QString QDeclarativeNetworkInfo::locationAreaCode(int interface) const
{
    return networkInfo->locationAreaCode(interface);
}

/*!
    \qmlsignal NetworkInfo::locationAreaCodeChanged(int interface, string lac)

    This signal is emitted whenever the location area code of \a interface has been changed to \a lac.
    Note that the signal won't emit until monitorLocationAreaCode is set true.
 */

/*!
    \qmlproperty bool NetworkInfo::monitorNetworkName

    This property holds whether or not monitor the change of network names.
 */
bool QDeclarativeNetworkInfo::monitorNetworkName() const
{
    return isMonitorNetworkName;
}

void QDeclarativeNetworkInfo::setMonitorNetworkName(bool monitor)
{
    if (monitor != isMonitorNetworkName) {
        isMonitorNetworkName = monitor;
        if (monitor) {
            connect(networkInfo, SIGNAL(networkNameChanged(QNetworkInfo::NetworkMode,int,QString)),
                    this, SIGNAL(_q_networkNameChanged(QNetworkInfo::NetworkMode,int,QString)));
        } else {
            connect(networkInfo, SIGNAL(networkNameChanged(QNetworkInfo::NetworkMode,int,QString)),
                    this, SIGNAL(_q_networkNameChanged(QNetworkInfo::NetworkMode,int,QString)));
        }
        emit monitorNetworkNameChanged();
    }
}

/*!
    \qmlmethod string NetworkInfo::networkName(NetworkInfo::NetworkMode mode, int interface)

    Returns the name of the given \a mode and \a interface.
 */
QString QDeclarativeNetworkInfo::networkName(NetworkMode mode, int interface) const
{
    return networkInfo->networkName(static_cast<QNetworkInfo::NetworkMode>(mode), interface);
}

/*!
    \qmlsignal NetworkInfo::networkNameChanged(NetworkMode mode, int interface, string name)

    This signal is emitted whenever the network name of \a mode and \a interface has been changed
    to \a name. Note that the signal won't emit until monitorNetworkName is set true.
 */
void QDeclarativeNetworkInfo::_q_networkNamedChanged(QNetworkInfo::NetworkMode mode, int interface, const QString &name)
{
    emit networkNameChanged(static_cast<NetworkMode>(mode), interface, name);
}

/*!
    Returns the MAC address for \a interface of \a mode. If the MAC address is not available or error
    occurs, an empty string is returned.
*/
QString QDeclarativeNetworkInfo::macAddress(QDeclarativeNetworkInfo::NetworkMode mode, int interface) const
{
    return networkInfo->macAddress(static_cast<QNetworkInfo::NetworkMode>(mode), interface);
}

/*!
    Returns the home Mobile Country Code (MCC) for \a interface. An empty string is returned if the
    information is not available or on error.
*/
QString QDeclarativeNetworkInfo::homeMobileCountryCode(int interface) const
{
    return networkInfo->homeMobileCountryCode(interface);
}

/*!
    Returns the home Mobile Network Code (MNC) for \a interface. An empty string is returned if the
    information is not available or on error.
*/
QString QDeclarativeNetworkInfo::homeMobileNetworkCode(int interface) const
{
    return networkInfo->homeMobileNetworkCode(interface);
}

/*!
    Returns the International Mobile Subscriber Identity (IMSI) for \a interface. If this information is
    not available, or error occurs, an empty string is returned.
*/
QString QDeclarativeNetworkInfo::imsi(int interface) const
{
    return networkInfo->imsi(interface);
}

QT_END_NAMESPACE