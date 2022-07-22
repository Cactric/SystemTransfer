/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

// This file will include support for announcing the service on the network
// and finding them

#include "service.h"
#include <kdnssd/publicservice.h>
#include <QNetworkInterface>
#include <QHostInfo>
#include <iostream>

Service::Service(QObject* parent) : QObject(parent) {
}

QString Service::introductionText() const
{
    return m_introductionText;
}

void Service::setIntroductionText(const QString &introductionText)
{
    m_introductionText = introductionText;
    Q_EMIT introductionTextChanged();
}

QString Service::serviceInformationText() const {
    serviceAnnounce();
    return m_serviceInformationText;
}

void Service::setServiceInformationText(const QString &serviceInformationText) {
    m_serviceInformationText = serviceInformationText;
    Q_EMIT serviceInformationTextChanged();
}

void Service::serviceAnnounce() const {
    KDNSSD::PublicService();
}

// This function gets the (local) IP address of the computer, e.g. 192.168.0.37
QString Service::myIPaddressText() const {
    // Code stolen from krfb and changed a little bit (I don't need a port or hostname)
    // Figure out the address
    std::cout << "Reached ip addr getter";
    const QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface& interface : interfaceList) {
        // Skip loopback interfaces that'll just contain localhost, etc.
        if(interface.flags() & QNetworkInterface::IsLoopBack)
            continue;

        if(interface.flags() & QNetworkInterface::IsRunning && !interface.addressEntries().isEmpty()) {
            const QString ipAddress = interface.addressEntries().constFirst().ip().toString();
            const QString formattedIPAddress = QStringLiteral("%1").arg(ipAddress);
            return formattedIPAddress;
        }
    }
    return QStringLiteral("Unknown");

}
