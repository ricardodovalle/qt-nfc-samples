/*
* Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Main.
*/

/*!
 * \file
 * \brief Declaration of the main() function for the P2Pexample application.
 */

/*! \mainpage P2P via NFC example
 *
 *  \section intro_sec Introduction
 *
 *  The P2Pexample is a sample application that demonstrates how to use the peer-to-peer communication between
 *  multiple NFC devices using the NFC LLCP communication protocol.
 *  The P2Pexample application is a multiplayer game, the purpose of which is to collect a full stack of matching images.
 *  Each player starts with a random set of images. The players can view each other's images and exchange a single
 *  image during each connection session.
 *
 *  A custom Qt Quick user interface shows the players' images and allows the selection of a single image
 *  for exchange during the next NFC connection session. Dialog boxes are displayed at game startup and when a
 *  player meets the winning condition. After winning, the winning player's game is reset.
 *
 *  The C++ class P2PEngine represents a game logic engine. It is contains the images used in the game, the
 *  lists of local and remote players' images, and the image selected for exchange.
 *  The game stage is updated based on messages from the NFCconnection class. P2PEngine emits
 *  three signals that are listened to by the Qt UI.
 *
 *  The C++ class NfcConnection creates a peer-to-peer connection between NFC devices using the NFC LLCP communication
 *  protocol. The class is responsible for sending and receiving messages between two NFC devices.
 *  LLCP server takes care of listening for NFC targets and starts an LLCP connection to the client.
 *  The LLCP server is listening for incoming connections at a specified URI and then sends data to the client.
 *
 *  \section prerequisites_sec Prerequisites
 *
 *  Qt and Qt Quick basics.
 *
 *  \section capability_sec Required capablities
 *
 *  The application requires no capabilities that cannot be granted by the user at install time. The SIS installation file can be self-signed.
 *
 *  \section knownissues_sec Known issues
 *
 *  None.
 *
 *  \section build_install_sec Building and installation
 *
 *  \subsection build_install_preparations_subsec Preparations
 *
 *  Make sure that you have installed Qt 4.7.3 and Qt Mobility 1.2 (or later if applicable
 *  to your version of the Qt SDK) binaries on your device. These can be installed using
 *  the SIS installation packages included with Qt SDK. This sample requires Qt SDK 1.1 or later is
 *  required to compile the application.
 *
 *  Additionally, create a target for Qt 4.7.3 and Qt Mobility 1.2
 *  for Symbian^3 following the instructions from:
 *  https://projects.forum.nokia.com/QtM12bSymb
 *
 *  Two or more Nokia C7-00 devices with Symbian Anna firmware are required to run the application.
 *
 *  \subsection build_install_qt_sdk_subsec Build & installation instructions using Qt SDK
 *
 *  <ol>
 *    <li>
 *      Open P2Pexample.pro by selecting the menu item File > Open File or Project... and select P2Pexample.pro.
 *    </li>
 *    <li>
 *      Select the "Qt 4.7.3 for Symbian^3 with QtM1.2b" target and press the Finish button.
 *    </li>
 *    <li>
 *      Make sure that an NFC enabled Symbian device is connected to your development PC via USB,
 *      ensure that the "Symbian Device" target is selected in the Target Selector and press the Run
 *      button to build the project and create the P2Pexample.sis Symbian install package. The application
 *      is automatically installed on the device.
 *    </li>
 *  </ol>
 *
 *  \section usage_sec Usage
 *
 *  \subsection usage_prerequisites_subsec Usage prerequisites
 *
 *  Two or more NFC enabled devices that all have the P2Pexample application installed and
 *  running are needed to be able play.
 *
 *  \subsection usage_game_start_subsec Game start
 *
 *  When the application is launched it randomly initializes images for each player.
 *  A dialog is shown to remind the player of the game rules. Ater tapping the OK button the player can start to play.
 *
 *  \subsection usage_playing_the_game_subsec Playing the game
 *
 *  The player can select one image that he/she wants to exchange by tapping on it.
 *  The selection can be changed by tapping on another image. Players can see each other's images on their device by
 *  placing two NFC sensors together. If both players have selected images, the images will be exchanged.
 *
 *  \subsection usage_winning_the_game_subsec Winning the game
 *
 *  When a player collects a full stack of identical image the game won dialog is shown. After tapping the OK button game state is reset.
 *
 *  \section compatibility_sec Compatibility
 *
 *  This sample application has been tested using the following hardware and
 *  software:
 *
 *  <ul>
 *    <li>Nokia C7-00 with Symbian Anna Firmware</li>
 *    <li>Nokia Qt SDK 1.1</li>
 *    <li>QtMobility 1.2 Beta1</li>
 *  </ul>
 *
 *  \section change_history_sec Change history
 *
 *  1.0 First version
 *
 * \section references_sec References
 *
 *  NFC
 *  http://www.forum.nokia.com/NFC
 *
 *  Qt for Symbian
 *  http://qt.nokia.com/downloads
 */

#ifndef MAIN_H
#define MAIN_H

/*!
 * \fn int main(int argc, char *argv[])
 * \brief The <code>main()</code> function for the P2P example application.
 *
 * Constructs the main window of the application.
 */

int main(int argc, char *argv[]);

#endif // MAIN_H
