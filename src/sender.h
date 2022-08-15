/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#pragma once
#include <QObject>
#include <QProcess>

class Sender : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    
    Q_PROPERTY(QString rsyncPath READ rsyncPath WRITE setRsyncPath NOTIFY rsyncPathChanged)
    Q_PROPERTY(QStringList rsyncArgs READ rsyncArgs WRITE setRsyncArgs NOTIFY rsyncArgsChanged)
    Q_PROPERTY(QProcess rsyncProcess READ rsyncProcess)

public:
    // Constructors
    Q_SCRIPTABLE explicit Sender(QString hostname, int port, QObject *parent = nullptr);
    explicit Sender(QObject *parent = nullptr);
    
    // Functions for hostname Q_PROPERTY
    QString hostname() const;
    void setHostname(const QString &hostname);
    Q_SIGNAL void hostnameChanged();
    
    // Functions for port Q_PROPERTY
    int port() const;
    void setPort(const int port);
    Q_SIGNAL void portChanged();

    // Rsync sender stuff
    QString rsyncPath() const;
    void setRsyncPath(QString &rsyncPath);
    Q_SIGNAL void rsyncPathChanged();
    
    QStringList rsyncArgs() const;
    void setRsyncArgs(QStringList &newRsyncArgs);
    void appendRsyncArg(QString &newRsyncArg);
    Q_SIGNAL void rsyncArgsChanged();
    
    QProcess* rsyncProcess() const;
    void startRsyncProcess();

private:
    QString m_hostname = "";
    int m_port = 0;
    QString m_rsync_path = "rsync";
    QStringList m_rsync_args;
    QProcess *m_rsync_process;
};
