/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#pragma once
#include <QObject>

class Service : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString introductionText READ introductionText WRITE setIntroductionText NOTIFY introductionTextChanged)
    Q_PROPERTY(QString serviceInformationText READ serviceInformationText WRITE setServiceInformationText NOTIFY serviceInformationTextChanged)
    Q_PROPERTY(QString myIPaddressText READ myIPaddressText);

public:
    explicit Service(QObject *parent = nullptr);
    QString introductionText() const;
    void setIntroductionText(const QString &introductionText);
    Q_SIGNAL void introductionTextChanged();
    
    QString serviceInformationText();
    void setServiceInformationText(const QString &serviceInformationText);
    Q_SIGNAL void serviceInformationTextChanged();
    void serviceAnnounce();

    QString myIPaddressText() const;

private:
    QString m_introductionText = "Hello world!";
    QString m_serviceInformationText = "Not announcing yet...";
    bool m_announcing = false;
};
