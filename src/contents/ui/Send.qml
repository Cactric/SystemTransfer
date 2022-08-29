// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Cactric

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import com.github.cactric.SystemTransfer 1.0

Kirigami.ScrollablePage {
    id: send
    title: i18n("Send")
    
    actions.main: Kirigami.Action {
        id: manualFind
        icon.name: "search"
        text: i18n("Find manually")
        onTriggered: manualFindSheet.open()
    }
    
    Kirigami.OverlaySheet {
        id: manualFindSheet
        
        header: Kirigami.Heading {
            text: "Search by IP address"
        }
        
        ColumnLayout {
            Controls.TextField {
                placeholderText: "IP address:"
            }
            
            Controls.Button {
                text: i18n("Send")
            }
        }
    }
    
    Kirigami.CardsListView {
        id: foundReceivers
        Kirigami.PlaceholderMessage {
            visible: foundReceivers.count === 0
            anchors.centerIn: parent
            icon.name: "network-wireless-disconnected"
            text: i18n("No receiving computers found on this network (yet)")
            helpfulAction: manualFind
        }
        model: Service.FoundReceiversList
        delegate: Kirigami.AbstractCard {
            id: foundReceiverDelegate
            
            contentItem: Item {
                implicitWidth: delegateLayout.implicitWidth
                implicitHeight: delegateLayout.implicitHeight
                GridLayout {
                    id: delegateLayout
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                    }
                    rowSpacing: Kirigami.Units.largeSpacing
                    columnSpacing: Kirigami.Units.largeSpacing
                    columns: root.wideScreen ? 4 : 2
                    
                    ColumnLayout {
                        Kirigami.Heading {
                            text: modelData.servicename
                            Layout.fillWidth: true
                        }
                        
                        Controls.Label {
                            text: i18n("Hostname: %1, Port %2", modelData.hostname, modelData.port)
                            Layout.fillWidth: true
                        }
                    }
                    
                    Controls.Button {
                        text: i18n("Send")
                        Layout.alignment: Qt.AlignRight
                        icon.name: "cloud-upload"
                        onClicked: {
                            Sender.setHostname(modelData.hostname);
                            Sender.setPort(modelData.port);
                            Sender.startRsyncProcess();
                        }
                    }
                }
            }
        }
        
    }
}
