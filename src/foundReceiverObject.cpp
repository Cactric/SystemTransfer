/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#include "foundReceiverObject.h"
#include <KLocalizedString>
#include <QDebug>

FoundReceiverObject::FoundReceiverObject(QObject* parent){
}

// Alternate constructor
FoundReceiverObject::FoundReceiverObject(const QString &servicename, const QString &hostname, int port, QObject* parent) {
    m_servicename = servicename;
    m_hostname = hostname;
    m_port = port;
    qDebug() << "Service name is now " << servicename;
    Q_EMIT servicenameChanged();
    qDebug() << "Hostname is now " << hostname;
    Q_EMIT hostnameChanged();
    qDebug() << "Port is now " << port;
    Q_EMIT portChanged();
}


// Getters
QString FoundReceiverObject::servicename() const {
    return m_servicename;
}

QString FoundReceiverObject::hostname() const {
    return m_hostname;
}

int FoundReceiverObject::port() const {
    return m_port;
}

// Setters
void FoundReceiverObject::setServiceName(const QString& servicename) {
    m_servicename = servicename;
    qDebug() << "Service name is now " << servicename;
    Q_EMIT servicenameChanged();
}

void FoundReceiverObject::setHostname(const QString& hostname) {
    m_hostname = hostname;
    qDebug() << "Hostname is now " << hostname;
    Q_EMIT hostnameChanged();
}

void FoundReceiverObject::setPort(const int port) {
    m_port = port;
    qDebug() << "Port is now " << port;
    Q_EMIT portChanged();
}
