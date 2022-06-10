// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Cactric

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15

import org.kde.kirigami 2.19 as Kirigami

Kirigami.ApplicationWindow {
    id: root

    title: i18n("SystemTransfer")

    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    globalDrawer: Kirigami.GlobalDrawer {
        title: i18n("SystemTransfer")
        titleIcon: "applications-graphics"
        isMenu: !root.isMobile
        actions: [
            Kirigami.Action {
                text: i18n("Send")
                icon.name: "cloud-upload"
                onTriggered: pageStack.layers.push('qrc:Send.qml')
            },
            Kirigami.Action {
                text: i18n("Receive")
                icon.name: "cloud-download"
                onTriggered: pageStack.layers.push('qrc:Receive.qml')
            },
            Kirigami.Action {
                text: i18n("About System Transfer")
                icon.name: "help-about"
                onTriggered: pageStack.layers.push('qrc:About.qml')
            },
            Kirigami.Action {
                text: i18n("Quit")
                icon.name: "application-exit"
                onTriggered: Qt.quit()
            }
        ]
    }

    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }

    pageStack.initialPage: page

    Kirigami.Page {
        id: page
        Layout.fillWidth: true
        title: i18n("Main Page")
        ColumnLayout {
            width: page.width

            anchors.centerIn: parent

            Kirigami.Heading {
                Layout.alignment: Qt.AlignCenter
                text: i18n("System transfer")
            }
            
            Controls.Label {
                Layout.alignment: Qt.AlignCenter
                text: i18n("Transfer your files to another computer")
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Controls.Button {
                    Layout.alignment: Qt.AlignHCenter
                    text: i18n("Send")
                    icon.name: "cloud-upload"
                    onClicked: pageStack.layers.push('Send.qml')
                }
                Controls.Button {
                    Layout.alignment: Qt.AlignHCenter
                    text: i18n("Receive")
                    icon.name: "cloud-download"
                    onClicked: pageStack.layers.push('qrc:Receive.qml')
                }
            }
        }
    }
}
