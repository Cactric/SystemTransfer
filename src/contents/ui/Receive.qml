// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Cactric

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami

Kirigami.Page {
    id: receive
    title: i18n("Receive")

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
        }
    }

}