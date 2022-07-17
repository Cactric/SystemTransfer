/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#pragma once
#include <QObject>

class Service : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString introductionText READ introductionText WRITE setIntroductionText NOTIFY introductionTextChanged)
    
public:
    explicit Service(QObject *parent = nullptr);
    QString introductionText() const;
    void setIntroductionText(const QString &introductionText);
    Q_SIGNAL void introductionTextChanged();

private:
    QString m_introductionText = "Hello world!";
};
