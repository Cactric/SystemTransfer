// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Cactric

// This is the page to show progress when actually sending
// Don’t confuse it with Send.qml, which allows the user to pick which computer to send it to

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import com.github.cactric.SystemTransfer 1.0

Kirigami.Page {
    id: sender
    title: i18n("Sending to %1...", Sender.hostname)
    
    actions.main: Kirigami.Action {
        id: cancelSend
        icon.name: "dialog-cancel"
        text: i18n("Cancel")
        onTriggered: {
            Sender.cancelRsyncProcess();
            pageStack.layers.pop();
        }
    }
    
    Kirigami.Dialog {
        id: "logDialogue"
        title: "Transfer log"
        standardButtons: Kirigami.Dialog.NoButton
        
        Controls.ScrollView {
            focusPolicy: Qt.StrongFocus
            //implicitWidth: Kirigami.Units.gridUnit * 16
            implicitHeight: Kirigami.Units.gridUnit * 32
            Controls.TextArea {
                height: parent.height
                readOnly: true
                text: Sender.rsyncOutput
            }
        }
    }
    
    ColumnLayout {
        Controls.Label {
            Layout.alignment: Qt.AlignLeft
            text: i18n("Sending to %1...", Sender.hostname)
        }
        Controls.ProgressBar {
            from: 0
            to: 100
            value: 25
            Layout.fillWidth: true
        }
        
        Controls.Button {
            text: i18n("Show transfer log")
            Layout.alignment: Qt.AlignLeft
            icon.name: "viewlog"
            onClicked: logDialogue.open()
        }
    }
}
