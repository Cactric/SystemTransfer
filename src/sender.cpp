/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/
#include "sender.h"
#include <QObject>
//#include <QDebug>

Sender::Sender(QObject* parent) : QObject(parent) {
}

QString Sender::hostname() const {
    return m_hostname;
}

void Sender::setHostname(const QString &hostname) {
    m_hostname = hostname;
    Q_EMIT hostnameChanged();
}

int Sender::port() const {
    return m_port;
}

void Sender::setPort(const int port) {
    m_port = port;
    Q_EMIT portChanged();
}

QString Sender::rsyncPath() const {
    return m_rsync_path;
}

void Sender::setRsyncPath(QString &rsyncPath) {
    m_rsync_path = rsyncPath;
    Q_EMIT rsyncPathChanged();
}

QString Sender::source() {
    return m_source;
}

void Sender::setSource(QString &newSource) {
    m_source = newSource;
    Q_EMIT sourceChanged();
}

QString Sender::destination() {
    return m_destination;
}

void Sender::setDestination(QString &newDestination) {
    m_destination = newDestination;
    Q_EMIT destinationChanged();
}

QStringList Sender::rsyncArgs() const {
    return m_rsync_args;
}

void Sender::setRsyncArgs(QStringList& newRsyncArgs) {
    m_rsync_args = newRsyncArgs;
    Q_EMIT rsyncArgsChanged();
}

void Sender::appendRsyncArg(QString& newRsyncArg) {
    m_rsync_args << newRsyncArg;
    Q_EMIT rsyncArgsChanged();
}

QProcess* Sender::rsyncProcess() const {
    return m_rsync_process;
}

void Sender::startRsyncProcess() {
    m_rsync_process = new QProcess();
    connect(m_rsync_process, SIGNAL(readyReadStandardError()), this, SLOT(moreRsyncOutput()));
    connect(m_rsync_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
    [=](int exitCode, QProcess::ExitStatus exitStatus){
        QString exitmsg;
        if(exitStatus == QProcess::CrashExit) {
            exitmsg = "Sending to %1 was unsuccessful because the process crashed :/";
        } else {
            // exitCode is only valid if there was a normal exit, according to Qt's docs
            if (exitCode == 0){
                // Good exit
                exitmsg = "Transfer to %1 appears to have been completed successfully.";
            } else {
                // Bad exit
                exitmsg = "Transfer to %1 appears to have stopped unsuccessfully (exit code " + QString::number(exitCode) + ".) Check the transfer log for more details"; 
            }
        }
        setStatus(exitmsg);
    });
    
    // Populate some default arguments (like the source and destination)
    QString destinationUrl = "rsync://" + m_hostname + ":" + QString::number(m_port) + "/" + m_destination + "/";
    
    // Add some default arguments - a way to change these will come later
    m_rsync_args << "--archive";
    m_rsync_args << "--verbose";
    m_rsync_args << "--progress";
    m_rsync_args << "--partial";
    
    m_rsync_args << m_source << destinationUrl;
    
    //qDebug() << "About to start rsync process:" << m_rsync_path << m_rsync_args;
    
    m_rsync_process->start(m_rsync_path, m_rsync_args);
    setStatus("Sending to %1...");
}

void Sender::cancelRsyncProcess() {
    m_rsync_process->terminate();
}

QString Sender::rsyncOutput() const {
    return m_rsync_output;
}

void Sender::moreRsyncOutput() {
    m_rsync_output = m_rsync_process->readAllStandardError();
    Q_EMIT rsyncOutputChanged();
}

QString Sender::status() const {
    return m_status;
}

void Sender::setStatus(const QString &newStatus) {
    m_status = newStatus;
    Q_EMIT statusChanged();
}
