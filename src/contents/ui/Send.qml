// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Cactric

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.SystemTransfer 1.0

Kirigami.Page {
    id: send
    title: i18n("Send")
    
    ColumnLayout {
        width: page.width
        Kirigami.Heading {
            text: i18n("Send")
            Layout.alignment: Qt.AlignCenter
        }
        
        Controls.Label {
            text: i18n("Select a computer to send to or search by IP address")
            Layout.alignment: Qt.AlignHCenter
        }
        
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Controls.TextField {
                placeholderText: i18n("IP address")
            }
            Controls.Button {
                text: i18n("Send")
            }
        }
        
        Controls.Label {
            text: Service.serviceInformationText
        }
        
    }
}
