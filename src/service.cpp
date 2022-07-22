/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

// This file will include support for announcing the service on the network
// and finding them

#include "service.h"

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
    return m_serviceInformationText;
}

void Service::setServiceInformationText(const QString &serviceInformationText) {
    m_serviceInformationText = serviceInformationText;
    Q_EMIT serviceInformationTextChanged();
}
