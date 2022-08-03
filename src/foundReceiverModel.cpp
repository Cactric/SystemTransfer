/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#include "foundReceiverModel.h"
#include <KLocalizedString>

FoundReceiverModel::FoundReceiverModel(QObject* parent){
}

// Getters
QString FoundReceiverModel::servicename() const {
    return m_servicename;
}

QString FoundReceiverModel::hostname() const {
    return m_hostname;
}

int FoundReceiverModel::port() const {
    return m_port;
}

// Setters
void FoundReceiverModel::setServiceName(const QString& servicename) {
    m_servicename = servicename;
    Q_EMIT servicenameChanged();
}

void FoundReceiverModel::setHostname(const QString& hostname) {
    m_hostname = hostname;
    Q_EMIT hostnameChanged();
}

void FoundReceiverModel::setPort(const int port) {
    m_port = port;
}
