// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Cactric

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import com.github.cactric.SystemTransfer 1.0

Kirigami.Page {
    id: receive
    title: i18n("Receive")
    
    onBackRequested: {
        Receiver.cancelRsyncProcess();
        Service.stopAnnouncingService();
    }

    ColumnLayout {
        width: page.width

        Kirigami.Heading {
            text: i18n("Receive")
            Layout.alignment: Qt.AlignCenter
        }
        
        Controls.Label {
            text: i18n("This computer should be visible to others using this app on the same network")
            Layout.alignment: Qt.AlignHCenter
        }
        Controls.Label {
            text: i18n("Alternatively, you can search by IP address on the other computer")
            Layout.alignment: Qt.AlignHCenter
        }
        Controls.Button {
            text: i18n("Show IP address")
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                const ipaddrdialog = unhideDialog.createObject(root, {})
                ipaddrdialog.open()
            }
        }
                
        Controls.Label {
            text: Service.serviceInformationText
        }
        
        Controls.Label {
            text: Receiver.status
        }
        
        Controls.Button {
            text: i18n("Show log file")
            Layout.alignment: Qt.AlignLeft
            icon.name: "viewlog"
            onClicked: Receiver.openLogFile()
        }
    }
    
    Component {
        // This component was stolen from kcm_about-distro (originally used for a serial number)
        id: unhideDialog
        Kirigami.PromptDialog {
            title: i18nc("@title", "IPv4 address of this computer")
            subtitle: Service.myIPaddressText
            flatFooterButtons: true
            standardButtons: Kirigami.Dialog.NoButton
            customFooterActions: [
                Kirigami.Action {
                    text: i18nc("@action:button", "Copy to Clipboard")
                    icon.name: "edit-copy"
                    onTriggered: Service.storeInClipboard(subtitle)
                    shortcut: StandardKey.Copy
                }
            ]
        }
    }

    Kirigami.Dialog {
        id: "logDialogue"
        title: "Transfer log"
        standardButtons: Kirigami.Dialog.NoButton
        
        Controls.ScrollView {
            focusPolicy: Qt.StrongFocus
            implicitWidth: Kirigami.Units.gridUnit * 48
            implicitHeight: Kirigami.Units.gridUnit * 32
            Controls.TextArea {
                font.family: "Monospace"
                height: parent.height
                readOnly: true
                text: Receiver.rsyncOutput
            }
        }
    }
    
}
