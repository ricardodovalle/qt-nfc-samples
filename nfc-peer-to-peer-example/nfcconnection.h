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
* Description:  Implements NFC connection functionality.
*/

#ifndef NFCCONNECTION_H
#define NFCCONNECTION_H

/*!
 * \file
 * \brief Implements NFC LLCP connection functionality.
 */

#include <QObject>
#include <qmobilityglobal.h>

// Forward declarations.
QTM_BEGIN_NAMESPACE
class QLlcpServer;
class QLlcpSocket;
class QNearFieldManager;
class QNearFieldTarget;
QTM_END_NAMESPACE

class P2PEngine;

// Qt Mobility namespace.
QTM_USE_NAMESPACE

//!  Implements NFC LLCP connection functionality.
/*!
  This class creates a connection between two NFC devices using the NFC LLCP communication
  protocol. The class establishes peer-to-peer communication between two NFC-enabled devices
  and makes it possible to accept incoming LLCP socket connections.

  LLCP server takes care of listening for NFC targets and starts an LLCP connection to the client.
  The LLCP server is listening for incoming connections at a specified URI and then
  sends data to the client.
*/

class NfcConnection : public QObject
{
    Q_OBJECT

public:
    //! Class Constructor.
    /*!
     *  \param parent Parent for the object.
     *  \param engine Reference to P2PEngine, ownership is not transferred.
     */
    explicit NfcConnection(QObject *parent, P2PEngine *engine);

    //! Destructor.
    virtual ~NfcConnection();

    //! Reads all available data from the device.
    /*!
      \return QString data read as a string.
    */
    Q_INVOKABLE QString readText();

    //! Writes the content of byteArray to the device.
    /*!
      \return Returns true on success; otherwise returns false.
    */
    bool sendText();

private slots:

    //! Connects to the target at a specified URI.
    /*!
      \param target The near field target that was detected.
    */
    void targetDetected(QNearFieldTarget *target);

    //! Disconnects the socket.
    /*!
      \param target The near field target that was lost.
    */
    void targetLost(QNearFieldTarget *target);

    //! Creates the next pending connection as a connected QLlcpSocket object.
    void handleNewConnection();

    //! Slot called when socket has been disconnected.
    void clientSocketDisconnected();

private:
    P2PEngine *m_engine;             //! Reference to P2PEngine, not owned.
    QLlcpSocket *m_nfcServerSocket;  //! NFC LLCP server socket.
    QNearFieldManager *m_nfcManager; //! Sets the target access modes to NFC devices.
    QLlcpServer *m_nfcServer;        //! Provides an NFC LLCP socket based server.
    QLlcpSocket *m_nfcClientSocket;  //! NFC LLCP client socket.
    };

#endif // NFCCONNECTION_H
