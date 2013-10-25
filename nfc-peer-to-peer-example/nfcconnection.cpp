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

#include <qllcpserver.h>
#include <qnearfieldmanager.h>

#include "nfcconnection.h"
#include "p2pengine.h"

//! LLCP service URI that the server is listening on.
static const QLatin1String p2pUri("urn:nfc:sn:com.nokia.qtmobility.p2p");

NfcConnection::NfcConnection(QObject *parent, P2PEngine* engine) :
    QObject(parent), m_engine (engine), m_nfcServerSocket(0)
{
    m_nfcManager = new QNearFieldManager(this);

    connect(m_nfcManager, SIGNAL(targetDetected(QNearFieldTarget*)),
            this, SLOT(targetDetected(QNearFieldTarget*)));
    connect(m_nfcManager, SIGNAL(targetLost(QNearFieldTarget*)),
         this, SLOT(targetLost(QNearFieldTarget*)));

    // Only detect other NFC devices. Leave the phone to handle NFC tags.
    m_nfcManager->setTargetAccessModes(QNearFieldManager::NdefReadTargetAccess | QNearFieldManager::NdefWriteTargetAccess);
    m_nfcManager->startTargetDetection(QNearFieldTarget::NfcForumDevice);

    m_nfcServer = new QLlcpServer(this);
    connect(m_nfcServer, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));

    // Listen for incoming connections on the P2P service URI.
    m_nfcServer->listen(p2pUri);

    m_nfcClientSocket = new QLlcpSocket(this);

    connect(m_nfcClientSocket, SIGNAL(readyRead()), this, SLOT(readText()));
    connect(m_nfcClientSocket, SIGNAL(disconnected()), this, SLOT(clientSocketDisconnected()));
}

NfcConnection::~NfcConnection()
{
    // Empty implementation
}

void NfcConnection::targetDetected(QNearFieldTarget *target)
{
    // Check if the target supports LLCP access.
    QNearFieldTarget::AccessMethods accessMethods = target->accessMethods();
    if (accessMethods.testFlag(QNearFieldTarget::LlcpAccess))
    {
        m_nfcClientSocket->connectToService(target, p2pUri);
    }
}

void NfcConnection::targetLost(QNearFieldTarget *target)
{
    m_nfcClientSocket->disconnectFromService();
    target->deleteLater();
}

void NfcConnection::handleNewConnection()
{
    if (m_nfcServerSocket)
    {
        m_nfcServerSocket->deleteLater();
    }
    // The socket is a child of the server and will be deleted automatically.
    m_nfcServerSocket = m_nfcServer->nextPendingConnection();

    sendText();
}

void NfcConnection::clientSocketDisconnected()
{
  //  Client socket disconnected
}

QString NfcConnection::readText()
{
    QByteArray rawData = m_nfcClientSocket->readAll();
    QString data = QString::fromUtf8(rawData.constData(), rawData.size());
    if (!data.isEmpty())
    {
        m_engine->setRemoteIndexes(data);
    }
    return data;
}

bool NfcConnection::sendText()
{
    bool ret(false);
    QString text = m_engine->getLocalIndexString();
    if (m_nfcServerSocket && m_nfcServerSocket->isOpen() && m_nfcServerSocket->isWritable() &&
            m_nfcClientSocket && m_nfcClientSocket->isOpen() && !text.isEmpty())
    {
        // Send array of images
        m_nfcServerSocket->write(text.toUtf8());
        if(m_engine->isExchangeImageSet())
        {
            // Write index of exchange image
            text = m_engine->getExchangeIndexString();
            m_nfcServerSocket->write(text.toUtf8());
        }
    ret = true;
    }
return ret;
}

