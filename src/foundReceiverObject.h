/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#pragma once
#include <QObject>

class FoundReceiverObject : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString servicename READ servicename WRITE setServiceName NOTIFY servicenameChanged)
    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    
public:
    FoundReceiverObject(QObject* parent = nullptr);
    
    QString servicename() const;
    void setServiceName(const QString &servicename);
    Q_SIGNAL void servicenameChanged();
    
    QString hostname() const;
    void setHostname(const QString &hostname);
    Q_SIGNAL void hostnameChanged();
    
    int port() const;
    void setPort(const int port);
    Q_SIGNAL void portChanged();

private:
    int m_port = 0;
    QString m_hostname = "";
    QString m_servicename = "";
};
