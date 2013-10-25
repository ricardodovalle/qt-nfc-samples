import QtQuick 1.0

/*!
 *  \file
 *  \brief Message box for common use.
 *
 *  Message box for start up and congratulation notifications.
 */

Rectangle {
    id: myMessageBox
    x: 32
    y: 60
    width: 305
    height: 435
    anchors.centerIn: parent
    visible: true;

    border {width: 1; color: "gray"}
    radius: 5
    opacity: 0.9
    anchors.verticalCenterOffset: -2
    anchors.horizontalCenterOffset: -7

    Text {
        id: title
        x: 62
        y: 26
        width: 230
        height: 35
        text: "NFC peer-to-peer example"
        style: Text.Raised
        font.italic: false
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.family: "Times New Roman"
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 17
    }

    Image {
        id: icon
        x: 16
        y: 17
        width: 53
        height: 53
        source: "p2p_icon.png"
    }

    Rectangle {
        id: button
        x: 64;
        y: 380;
        width: 168;
        height: 36;
        color: "#9b98af";
        radius: 15;
        border.color: "#9b98af";
        border.width: 6;
        anchors.verticalCenterOffset: 144;
        anchors.horizontalCenterOffset: 0

        MouseArea {
            id: mouseArea
            anchors.fill: parent;
            onClicked: myMessageBox.visible = false
            }
        Text {
            id: textButton
            text: "Start to play"
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            font.family: "Times New Roman"
            font.pixelSize: 21
            }
        }
}
