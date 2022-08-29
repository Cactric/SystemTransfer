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
                text: "PING archlinux.org(archlinux.org (2a01:4f9:c010:6b1f::1)) 56 data bytes
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=1 ttl=53 time=114 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=2 ttl=53 time=75.9 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=3 ttl=53 time=74.0 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=4 ttl=53 time=75.6 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=5 ttl=53 time=75.5 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=6 ttl=53 time=74.9 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=7 ttl=53 time=75.5 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=8 ttl=53 time=74.9 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=9 ttl=53 time=88.5 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=10 ttl=53 time=91.2 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=11 ttl=53 time=83.6 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=12 ttl=53 time=75.3 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=13 ttl=53 time=93.0 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=14 ttl=53 time=95.3 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=15 ttl=53 time=75.0 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=16 ttl=53 time=86.6 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=17 ttl=53 time=92.0 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=19 ttl=53 time=93.5 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=20 ttl=53 time=78.0 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=21 ttl=53 time=75.2 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=22 ttl=53 time=73.9 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=23 ttl=53 time=80.0 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=24 ttl=53 time=75.7 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=25 ttl=53 time=74.1 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=26 ttl=53 time=74.3 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=27 ttl=53 time=75.2 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=28 ttl=53 time=87.1 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=29 ttl=53 time=79.5 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=30 ttl=53 time=76.4 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=31 ttl=53 time=74.7 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=32 ttl=53 time=261 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=33 ttl=53 time=174 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=34 ttl=53 time=323 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=35 ttl=53 time=273 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=36 ttl=53 time=229 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=37 ttl=53 time=561 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=38 ttl=53 time=107 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=40 ttl=53 time=264 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=41 ttl=53 time=75.4 ms
64 bytes from archlinux.org (2a01:4f9:c010:6b1f::1): icmp_seq=43 ttl=53 time=274 ms
^C
--- archlinux.org ping statistics ---
44 packets transmitted, 40 received, 9.09091% packet loss, time 43095ms
rtt min/avg/max/mdev = 73.940/124.511/560.865/98.402 ms
"
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
