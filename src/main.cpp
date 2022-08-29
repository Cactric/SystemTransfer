/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Cactric
*/

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>
#include <QObject>

#include "about.h"
#include "app.h"
#include "version-systemtransfer.h"
#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>

#include "systemtransferconfig.h"
#include "service.h"
#include "sender.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("SystemTransfer"));

    KAboutData aboutData(
                         // The program name used internally.
                         QStringLiteral("SystemTransfer"),
                         // A displayable program name string.
                         i18nc("@title", "SystemTransfer"),
                         // The program version string.
                         QStringLiteral(SYSTEMTRANSFER_VERSION_STRING),
                         // Short description of what the app does.
                         i18n("Transfer your data to a new computer"),
                         // The license this code is released under.
                         KAboutLicense::GPL,
                         // Copyright Statement.
                         i18n("(c) 2022 Cactric"));
    aboutData.addAuthor(i18nc("@info:credit", "Cactric"), i18nc("@info:credit", "Author"), NULL /*QStringLiteral("%{EMAIL}")*/, QStringLiteral("https://github.com/cactric"));
    KAboutData::setApplicationData(aboutData);

    QQmlApplicationEngine engine;

    auto config = SystemTransferConfig::self();

    qmlRegisterSingletonInstance("com.github.cactric.SystemTransfer", 1, 0, "Config", config);

    AboutType about;
    qmlRegisterSingletonInstance("com.github.cactric.SystemTransfer", 1, 0, "AboutType", &about);

    App application;
    qmlRegisterSingletonInstance("com.github.cactric.SystemTransfer", 1, 0, "App", &application);
    
    QList<FoundReceiverObject *> foundReceiversList;
    //engine.setInitialProperties({{"FoundReceiversList", QVariant::fromValue(foundReceiversList) }});
    
    Service service;
    service.setFoundReceiversList(foundReceiversList);
    qmlRegisterSingletonInstance("com.github.cactric.SystemTransfer", 1, 0, "Service", &service);
    
    Sender sender;
    QString defaultSource = qEnvironmentVariable("HOME");
    sender.setSource(defaultSource);
    qmlRegisterSingletonInstance("com.github.cactric.SystemTransfer", 1, 0, "Sender", &sender);

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
