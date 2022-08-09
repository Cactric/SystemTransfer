/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

// This file will include support for announcing the service on the network
// and finding them

#include "service.h"
#include "foundReceiverObject.h"
#include <kdnssd/publicservice.h>
#include <kdnssd/servicebrowser.h>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QGuiApplication>
#include <QClipboard>
#include <KLocalizedString>

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

QString Service::serviceInformationText(){
    return m_serviceInformationText;
}

void Service::setServiceInformationText(const QString &serviceInformationText) {
    m_serviceInformationText = serviceInformationText;
    Q_EMIT serviceInformationTextChanged();
}

Q_SCRIPTABLE void Service::serviceAnnounce() {
    if (m_announcing) {
        return;
    }
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

Q_SCRIPTABLE void Service::init_service_browser() {
    service_browser = new KDNSSD::ServiceBrowser(
        QStringLiteral("_systemtransfer._tcp"),
        true // auto resolve. I guess I want this?
    );
    connect(service_browser, SIGNAL(finished()), this, SLOT(servicesChanged()));
    service_browser->startBrowse();
}

void Service::servicesChanged() {
    const QList<KDNSSD::RemoteService::Ptr> services = service_browser->services();
    
    // Clear the list of found computers
    m_foundReceiversList.clear();
    
    // Add the computers found
    for (const KDNSSD::RemoteService::Ptr& service : services) {
        // Check that it's not a duplicate (e.g. on another interface or different IP version)
        bool duplicate = false;
        for (const FoundReceiverObject* checkservice : m_foundReceiversList) {
            if (checkservice->servicename() == service->serviceName()) {
                if (checkservice->hostname() == service->hostName()) {
                    if (checkservice->port() == service->port()) {
                        duplicate = true;
                        break;
                    }
                }
            }            
        }
        if (duplicate == false) {
            m_foundReceiversList.append(new FoundReceiverObject(service->serviceName(), service->hostName(), service->port()));
        }
        //std::cout << "Adding service:\nService name: " << service->serviceName() << "\nHostname: " << service->hostName() << "\nPort: " << service->port() << "\n";
        std::cout << "Adding service:\nPort: " << service->port() << "\n";
    }
    
    //std::cout << "Emitting FoundReceiversListChanged.\n";
    //std::cout << "New length: " << m_foundReceiversList.count() << "\n";
    Q_EMIT FoundReceiversListChanged();
}

QList<FoundReceiverObject *> Service::FoundReceiversList() const {
    return m_foundReceiversList;
}

void Service::setFoundReceiversList(QList<FoundReceiverObject *> new_foundReceiversList) {
    m_foundReceiversList = new_foundReceiversList;
    Q_EMIT FoundReceiversListChanged();
}


Q_SCRIPTABLE void Service::storeInClipboard(const QString &text) {
    QGuiApplication::clipboard()->setText(text.trimmed());
}
