/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#pragma once
#include <QObject>
#include <QProcess>

class Receiver : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    
    Q_PROPERTY(QString rsyncPath READ rsyncPath WRITE setRsyncPath NOTIFY rsyncPathChanged)
    Q_PROPERTY(QStringList rsyncArgs READ rsyncArgs WRITE setRsyncArgs NOTIFY rsyncArgsChanged)
    Q_PROPERTY(QProcess rsyncProcess READ rsyncProcess)
    Q_PROPERTY(QString rsyncOutput READ rsyncOutput NOTIFY rsyncOutputChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    // Constructors
    explicit Receiver(QObject *parent = nullptr);
    
    // Functions for port Q_PROPERTY
    int port() const;
    Q_SCRIPTABLE void setPort(const int port);
    Q_SIGNAL void portChanged();

    // Rsync receiver stuff
    QString rsyncPath() const;
    Q_SCRIPTABLE void setRsyncPath(QString &rsyncPath);
    Q_SIGNAL void rsyncPathChanged();
    
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
    
    int writeRsyncConfigFile();
    Q_SCRIPTABLE void openLogFile();

private:
    int m_port = 33599;
    QString m_rsync_path = "rsync";
    QStringList m_rsync_args;
    QProcess *m_rsync_process;
    QString m_rsync_output = "(empty)";
    QString m_status = "Waiting to start daemon...";
    // Should be something like /run/user/1000/systemtransfer_rsync.conf
    QString m_configfilepath = "";
    QString m_rsync_log_file = "";
    
private Q_SLOTS:
    void moreRsyncOutput();
};
