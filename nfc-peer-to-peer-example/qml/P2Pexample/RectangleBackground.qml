import QtQuick 1.0

/*!
 *  \file
 *  \brief Rectangle component for local/remote view background.
 *
 *  Defines the background component for main view.
 */

Rectangle {
    id: myRectangleBackground
    width: 140
    height: 603
    radius: 15
    gradient: Gradient {
        GradientStop {
            position: 0.1
            color: "#ffffff"
        }
        GradientStop {
            position: 0.94
            color: "#ffffff"
        }
        GradientStop {
            position: 0.52
            color: "#7c6363"
        }
    }
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.rightMargin: 29
    anchors.bottomMargin: 21
    anchors.topMargin: 16
    anchors.leftMargin: 20
    border.color: "#f9f6f6"
    border.width: 0
}
