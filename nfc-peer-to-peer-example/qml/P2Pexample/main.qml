import QtQuick 1.0
//import QtMobility.feedback 1.1
import P2PEngine 1.0

/*!
 *  \file
 *  \brief Main qml file for the application.
 *
 *  Main application view shows the local images and remote images.
 */

Rectangle {
    id: mainView
    width: 360
    height: 640

    P2PEngine {
        id: iEngine
        // Update remote images
        onShowRemoteImages: {
            anim.running = false;
            image6.source = iEngine.getRemoteImageFile(0);
            image7.source = iEngine.getRemoteImageFile(1);
            image8.source = iEngine.getRemoteImageFile(2);
            image9.source = iEngine.getRemoteImageFile(3);
            image10.source = iEngine.getRemoteImageFile(4);
            image11.source = iEngine.getRemoteImageFile(5);
            }

        // Update view after exchange has been done or start new game
        onUpdateView: {
            anim.running = false;
            image0.source = iEngine.getLocalImageFile(0);
            image1.source = iEngine.getLocalImageFile(1);
            image2.source = iEngine.getLocalImageFile(2);
            image3.source = iEngine.getLocalImageFile(3);
            image4.source = iEngine.getLocalImageFile(4);
            image5.source = iEngine.getLocalImageFile(5);
            image6.source = iEngine.getRemoteImageFile(0);
            image7.source = iEngine.getRemoteImageFile(1);
            image8.source = iEngine.getRemoteImageFile(2);
            image9.source = iEngine.getRemoteImageFile(3);
            image10.source = iEngine.getRemoteImageFile(4);
            image11.source = iEngine.getRemoteImageFile(5);
            }

        // Show congratulation message
        onShowWinnerMessage:{
            congratulations.visible = true;
            }
        }

    RectangleBackground {
            id: localListOfImages
            x: 19
            y: 16
            anchors.right:remoteListOfImages.left
            anchors.left: parent.left

            Grid {
                id: localImageGrid
                anchors.fill: parent
                anchors.rightMargin: 20
                anchors.leftMargin: 20
                rows: 6; columns: 1;

                // Show local images
                Image {
                    id: image0                 
                    source: {iEngine.getLocalImageFile(0)}
                    MouseArea {
                        id: myMouse0
                        anchors.fill: parent
                        onClicked: {
                            //themeEffect.play();
                            anim.running = false;
                            anim.target = image0;
                            anim.running = true;
                            iEngine.setImageForExchange(0);
                            }
                        }
                    }

                Image {
                 id: image1
                 source: {iEngine.getLocalImageFile(1)}
                    MouseArea {
                        id: myMouse1
                        anchors.fill: parent
                        onClicked: {
                            //themeEffect.play();
                            anim.running = false;
                            anim.target = image1;
                            anim.running = true;
                            iEngine.setImageForExchange(1);
                            }
                        }
                    }

                Image {
                    id: image2
                    source: {iEngine.getLocalImageFile(2)}
                    MouseArea {
                        id: myMouse2
                        anchors.fill: parent
                        onClicked: {
                            //themeEffect.play();
                            anim.running = false;
                            anim.target = image2;
                            anim.running = true;
                            iEngine.setImageForExchange(2);
                            }
                        }
                    }

                Image {
                    id: image3
                    source: {iEngine.getLocalImageFile(3)}
                    MouseArea {
                        id: myMouse3
                        anchors.fill: parent
                        onClicked: {
                            //themeEffect.play();
                            anim.running = false;
                            anim.target = image3;
                            anim.running = true;
                            iEngine.setImageForExchange(3);
                            }
                        }
                    }

                Image {
                    id: image4
                    source: {iEngine.getLocalImageFile(4)}
                    MouseArea {
                        id: myMouse4
                        anchors.fill: parent
                        onClicked: {
                            //themeEffect.play();
                            anim.running = false;
                            anim.target = image4;
                            anim.running = true;
                            iEngine.setImageForExchange(4);
                            }
                        }
                    }

                Image {
                    id: image5
                    source: {iEngine.getLocalImageFile(5)}
                    MouseArea {
                        id: myMouse5
                        anchors.fill: parent
                        onClicked: {
                            //themeEffect.play();
                            anim.running = false;
                            anim.target = image5;
                            anim.running = true;
                            iEngine.setImageForExchange(5);
                            }
                        }
                    }
              }
        }

        RectangleBackground {
            id: remoteListOfImages
            x: 195
            y: 16
            anchors.right: parent.right

            // Show remote shapes
            Grid {
                 id: remoteImageGrid
                 anchors.fill: parent
                 anchors.rightMargin: 20
                 anchors.leftMargin: 20
                 rows: 6; columns: 1;

                Image { id: image6 }
                Image { id: image7 }
                Image { id: image8 }
                Image { id: image9 }
                Image { id: image10 }
                Image { id: image11 }
                }
        }

   /*  ThemeEffect {
         id: themeEffect
         effect: ThemeEffect.SensitiveItem;
     }
*/
     // Animate image for exchange
     RotationAnimation on rotation {
         id: anim;
         loops: Animation.Infinite
         from: 0
         to: 360
         duration: 4000;
         running: false;
         property: "rotation" ;
         }

    // How to play description
    MessageBox {
        id: aboutP2PExample
        Text {
             id: aboutText
             x: 16
             y: 70
             width: 270
             wrapMode: Text.WordWrap
             font.family: "Times New Roman"
             font.pixelSize: 17
             text: "This example application shows how to create a peer-to-peer connection between two NFC devices using the LLCP protocol.<BR><B>Goal of the game:</B><BR>You need to collect shapes of one type.<BR><B>How to play:</B><BR> Touch another device to see the other player's shapes. Tap the shape on the left which you would like to change. Touch the other device again to exchange shapes.<BR>Good luck!<BR>"
             }
        }

    // Congratulation message
    MessageBox {
        id: congratulations
        visible: false;
        Text {
            id: congratulationsText
            x: 16
            y: 70
            width: 270
            color: "red";
            horizontalAlignment: Text.AlignHCenter
            text: "<BR><B>CONGRATULATIONS!<BR><BR>You are a Winner!</B>"
            font.family: "Times New Roman"
            font.pixelSize: 25
            }
        MouseArea {
            id: mouseArea1
            anchors.fill: parent;
            onClicked: {
                iEngine.doReset();
                anim.running = false;
                congratulations.visible = false
                }
            }
        }
/*
    Image {
           source : "close.png"
           x:  mainView.width - width
           y: 5
           width: 50;
           height: 50;
           MouseArea {
               anchors.fill: parent;
               onClicked: { Qt.quit(); }
           }
     }
 */
}


