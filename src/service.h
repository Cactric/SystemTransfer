/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#pragma once
//#include <QObject>
#include "foundReceiverObject.h"
#include <kdnssd/servicebrowser.h>

class Service : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString introductionText READ introductionText WRITE setIntroductionText NOTIFY introductionTextChanged)
    Q_PROPERTY(QString serviceInformationText READ serviceInformationText WRITE setServiceInformationText NOTIFY serviceInformationTextChanged)
    Q_PROPERTY(QString myIPaddressText READ myIPaddressText NOTIFY myIPaddressTextChanged)
    Q_PROPERTY(QList<FoundReceiverObject *> FoundReceiversList READ FoundReceiversList WRITE setFoundReceiversList NOTIFY FoundReceiversListChanged)

public:
    explicit Service(QObject *parent = nullptr);
    QString introductionText() const;
    void setIntroductionText(const QString &introductionText);
    Q_SIGNAL void introductionTextChanged();
    
    QString serviceInformationText();
    void setServiceInformationText(const QString &serviceInformationText);
    Q_SIGNAL void serviceInformationTextChanged();
    Q_SCRIPTABLE void serviceAnnounce();
    
    Q_SCRIPTABLE void init_service_browser();

    QString myIPaddressText() const;
    Q_SIGNAL void myIPaddressTextChanged(); // Not used
    
    Q_SCRIPTABLE static void storeInClipboard(const QString &text);
    
    void setFoundReceiversList(QList<FoundReceiverObject *> new_foundReceiversList);
    QList<FoundReceiverObject *> FoundReceiversList() const;
    Q_SIGNAL void FoundReceiversListChanged();
    
private:
    QString m_introductionText = "Hello world!";
    QString m_serviceInformationText = "Not announcing yet...";
    bool m_announcing = false;
    KDNSSD::ServiceBrowser *service_browser;
    QHash<QString, QString> m_protocols;
    QList<FoundReceiverObject *> m_foundReceiversList;

private Q_SLOTS:
    void servicesChanged();
};
