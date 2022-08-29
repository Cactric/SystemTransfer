/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/
#include "sender.h"
#include <QObject>
#include <iostream>

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
    std::cout << "Starting rsync...\n";
    m_rsync_process = new QProcess();
    connect(m_rsync_process, SIGNAL(readyReadStandardError()), this, SLOT(moreRsyncOutput()));
    m_rsync_process->start(m_rsync_path, m_rsync_args);
}

void Sender::cancelRsyncProcess() {
    m_rsync_process->terminate();
}

QString Sender::rsyncOutput() const {
    return m_rsync_output;
}

void Sender::moreRsyncOutput() {
    m_rsync_output = m_rsync_process->readAllStandardError();
}
