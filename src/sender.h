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
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged) // Destination is the folder on the client (not including hostname)
    Q_PROPERTY(QStringList rsyncArgs READ rsyncArgs WRITE setRsyncArgs NOTIFY rsyncArgsChanged)
    Q_PROPERTY(QProcess rsyncProcess READ rsyncProcess)
    Q_PROPERTY(QString rsyncOutput READ rsyncOutput NOTIFY rsyncOutputChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    // Constructors
    //Q_SCRIPTABLE explicit Sender(QString hostname, int port, QObject *parent = nullptr);
    explicit Sender(QObject *parent = nullptr);
    
    // Functions for hostname Q_PROPERTY
    QString hostname() const;
    Q_SCRIPTABLE void setHostname(const QString &hostname);
    Q_SIGNAL void hostnameChanged();
    
    // Functions for port Q_PROPERTY
    int port() const;
    Q_SCRIPTABLE void setPort(const int port);
    Q_SIGNAL void portChanged();

    // Rsync sender stuff
    QString rsyncPath() const;
    Q_SCRIPTABLE void setRsyncPath(QString &rsyncPath);
    Q_SIGNAL void rsyncPathChanged();
    
    QString source();
    void setSource(QString &newSource);
    Q_SIGNAL void sourceChanged();
    
    QString destination();
    void setDestination(QString &newDestination);
    Q_SIGNAL void destinationChanged();
    
    QStringList rsyncArgs() const;
    void setRsyncArgs(QStringList &newRsyncArgs);
    void appendRsyncArg(QString &newRsyncArg);
    Q_SIGNAL void rsyncArgsChanged();
    
    QProcess* rsyncProcess() const;
    Q_SCRIPTABLE void startRsyncProcess();
    Q_SCRIPTABLE void cancelRsyncProcess();
    
    QString rsyncOutput() const;
    Q_SIGNAL void rsyncOutputChanged();
    
    QString status() const;
    void setStatus(const QString &newStatus);
    Q_SIGNAL void statusChanged();

private:
    QString m_hostname = "";
    int m_port = 0;
    QString m_rsync_path = "rsync";
    QStringList m_rsync_args;
    QProcess *m_rsync_process;
    QString m_rsync_output = "(empty)";
    QString m_source = "";
    QString m_destination = "home"; //default share name for the receiver
    QString m_status = "Transfer to %1 hasn't started";
    
private Q_SLOTS:
    void moreRsyncOutput();
};
