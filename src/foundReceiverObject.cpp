/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#include "foundReceiverObject.h"
#include <KLocalizedString>

FoundReceiverObject::FoundReceiverObject(QObject* parent){
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
    Q_EMIT servicenameChanged();
}

void FoundReceiverObject::setHostname(const QString& hostname) {
    m_hostname = hostname;
    Q_EMIT hostnameChanged();
}

void FoundReceiverObject::setPort(const int port) {
    m_port = port;
}
