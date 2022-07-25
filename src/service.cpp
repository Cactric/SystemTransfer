/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

// This file will include support for announcing the service on the network
// and finding them

#include "service.h"
#include <kdnssd/publicservice.h>
#include <kdnssd/servicebrowser.h>
#include <QNetworkInterface>
#include <QHostInfo>
#include <KLocalizedString>

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

QString Service::serviceInformationText(){
    if(m_announcing == false) {
        serviceAnnounce();
    }
    return m_serviceInformationText;
}

void Service::setServiceInformationText(const QString &serviceInformationText) {
    m_serviceInformationText = serviceInformationText;
    Q_EMIT serviceInformationTextChanged();
}

void Service::serviceAnnounce() {
    KDNSSD::PublicService *public_service = new KDNSSD::PublicService(
        i18n("System transfer on %1", QHostInfo::localHostName()),
        QStringLiteral("_systemtransfer._tcp"),
        33599 // port number. Random hardcoded number for now
    );
    
    public_service->publishAsync();

    m_announcing = true;
    m_serviceInformationText = "Announcing to other computers on the local network...";
    Q_EMIT serviceInformationTextChanged();

}

// This function gets the (local) IP address of the computer, e.g. 192.168.0.37
QString Service::myIPaddressText() const {
    // Code stolen from krfb and changed a little bit (I don't need a port or hostname)
    // Figure out the address
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

void Service::init_service_browser() {
    service_browser = new KDNSSD::ServiceBrowser(
        QStringLiteral("_systemtransfer._tcp"),
        true // auto resolve. I guess I want this?
    );
    connect(service_browser, SIGNAL(finished()), this, SLOT(servicesChanged()));
    service_browser->startBrowse();
}

void Service::servicesChanged() {
    // something something with kirigami
}
