/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/
#include "receiver.h"
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Receiver::Receiver(QObject *parent) : QObject(parent) {
}

int Receiver::port() const {
    return m_port;
}

Q_SCRIPTABLE void Receiver::setPort(const int port) {
    m_port = port;
    Q_EMIT portChanged();
}

QString Receiver::rsyncPath() const {
    return m_rsync_path;
}

void Receiver::setRsyncPath(QString& rsyncPath) {
    m_rsync_path = rsyncPath;
    Q_EMIT rsyncPathChanged();
}

QStringList Receiver::rsyncArgs() const {
    return m_rsync_args;
}

void Receiver::setRsyncArgs(QStringList& newRsyncArgs) {
    m_rsync_args = newRsyncArgs;
    Q_EMIT rsyncArgsChanged();
}

void Receiver::appendRsyncArg(QString& newRsyncArg) {
    m_rsync_args << newRsyncArg;
    Q_EMIT rsyncArgsChanged();
}

QProcess* Receiver::rsyncProcess() const {
    return m_rsync_process;
}

void Receiver::startRsyncProcess() {
    m_rsync_process = new QProcess();
    connect(m_rsync_process, SIGNAL(readyReadStandardError()), this, SLOT(moreRsyncOutput()));
    connect(m_rsync_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
    [=](int exitCode, QProcess::ExitStatus exitStatus){
        QString exitmsg;
        if(exitStatus == QProcess::CrashExit) {
            exitmsg = "Receiving was unsuccessful because the process crashed :/";
        } else {
            // exitCode is only valid if there was a normal exit, according to Qt's docs
            if (exitCode == 0){
                // Good exit
                exitmsg = "Receiving appears to have been completed successfully.";
            } else {
                // Bad exit
                exitmsg = "Receiving appears to have stopped unsuccessfully (exit code " + QString::number(exitCode) + ".) Check the transfer log for more details"; 
            }
        }
        setStatus(exitmsg);
    });
    
    // Write config file
    if(!writeRsyncConfigFile()) {
        setStatus("Error: Failed to write config file!");
        return;
    }
    
    // m_configfilepath should be set by writeRsyncConfigFile
    if(m_configfilepath == "") {
        setStatus("What? Where's the config file? (if you're seeing this in the app, it's a bug)");
        return;
    }
    
    m_rsync_log_file = qEnvironmentVariable("XDG_RUNTIME_DIR") + "/systemtransfer_rsyncd.log";
    
    // Populate some default arguments
    // Add some default arguments - a way to change these will come later
    m_rsync_args << "--daemon";
    m_rsync_args << "--config=" + m_configfilepath;
    m_rsync_args << "--log-file=" + m_rsync_log_file;
    m_rsync_args << "--port=" + QString::number(m_port);
    m_rsync_args << "--no-detach";
    m_rsync_args << "--verbose";
    
    qDebug() << m_rsync_path << m_rsync_args;
    
    m_rsync_process->start(m_rsync_path, m_rsync_args);
    setStatus("Ready to receive...");
}

void Receiver::cancelRsyncProcess() {
    m_rsync_process->terminate();
}

QString Receiver::rsyncOutput() const {
    return m_rsync_output;
}

void Receiver::moreRsyncOutput() {
    m_rsync_output = m_rsync_process->readAllStandardError();
    Q_EMIT rsyncOutputChanged();
}

QString Receiver::status() const {
    return m_status;
}

void Receiver::setStatus(const QString &newStatus) {
    m_status = newStatus;
    Q_EMIT statusChanged();
}

int Receiver::writeRsyncConfigFile() {
    QString runtimeDir = qEnvironmentVariable("XDG_RUNTIME_DIR");
    m_configfilepath = runtimeDir + "/systemtransfer_rsyncd.conf";
    QFile config_file(m_configfilepath);
    if(!config_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return 0;
    }
    
    QTextStream config_out(&config_file);
    //config_out << "pid file = " << qEnvironmentVariable("XDG_RUNTIME_DIR") << "\n\n";
    // An option to set which places to transfer to will come at some point, right now it's just $HOME
    config_out << "[home]\n    path = " << qEnvironmentVariable("HOME") << "\n    comment = Home folder\n";
    
    // This should be good
    config_file.close();
    return 1;
}

void Receiver::openLogFile() {
    QString program = "xdg-open";
    QStringList args;
    args << m_rsync_log_file;
    QProcess *open_process = new QProcess();
    
    open_process->start(program, args);
}
