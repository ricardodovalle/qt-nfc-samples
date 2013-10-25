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
* Description:  Implementation of application engine. It contains game logic and responds
* to connection events.
*/

#include <QTime>

#include "nfcconnection.h"
#include "p2pengine.h"

//!  Constant defines number of images in the game for one player.
static const int KMaxNumberOfImageIndexes = 6;

//! Constant for not selected image
static const int KImageNotSelected = -1;

//! Constants for file's names string
static const QLatin1String shape1("0.png");
static const QLatin1String shape2("1.png");
static const QLatin1String shape3("2.png");
static const QLatin1String shape4("3.png");
static const QLatin1String shape5("4.png");
static const QLatin1String shape6("5.png");

P2PEngine::P2PEngine(QObject *parent) : QObject(parent),
    m_indexOfImageForExchange(KImageNotSelected),
    m_placeOfImageForExchange(KImageNotSelected),
    m_exchangeImageSet(false)
{
    // Create NFC connection
    m_nfcConnection = new NfcConnection(0, this);

    // Load list of image filenames
    m_arrayOfImageNames << shape1 << shape2 << shape3 << shape4 << shape5 << shape6;

    // Initialize local image indices to random numbers.
    initLocalImageIndexes();
}

P2PEngine::~P2PEngine()
{
    // Empty implementation
}

void P2PEngine::initLocalImageIndexes()
{
    // Create seed for the random number generator.
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    for (int i = 0; i<KMaxNumberOfImageIndexes; i++)
    {
        // Get a random index number.
        int randomIndex = qrand()%KMaxNumberOfImageIndexes;
        m_localImageIndexes.append( randomIndex );
    }
}

QString P2PEngine::getLocalImageFile(int index) const
{
    QString filename;
    if ( index < m_localImageIndexes.size() )
    {
        filename = getImageFileNameByIndex( m_localImageIndexes.at(index) );
    }
    return filename;
}

QString P2PEngine::getRemoteImageFile(int index) const
{
   QString filename;
   if ( index < m_remoteImageIndexes.size() )
   {
       filename = getImageFileNameByIndex( m_remoteImageIndexes.at(index) );
   }
   return filename;
}

QString P2PEngine::getImageFileNameByIndex(int index) const
{
    QString filename;
    if( ( index < KMaxNumberOfImageIndexes ) && ( index >= 0) )
    {
        filename = m_arrayOfImageNames.at(index).toLocal8Bit().constData();
    }
    return filename;
}

void P2PEngine::setRemoteIndexes(QString indexString)
{
    // Exchange mode.
    if ( indexString.size() == 1 && m_exchangeImageSet )
    {
        // Do the exchange.
        int remoteExchangeIndex = indexString.toInt();
        m_localImageIndexes.replace(m_placeOfImageForExchange, remoteExchangeIndex);

        m_indexOfImageForExchange = KImageNotSelected;
        m_placeOfImageForExchange = KImageNotSelected;
        m_exchangeImageSet = false;
        emit updateView();
        // Check winner condition.
        if ( isWinner() )
        {
            // Show winner message.
            emit showWinnerMessage();
        }
        // Let NFC connection send new local image indices to the remote host.
        m_nfcConnection->sendText();
    }
    else if ( indexString.size() == KMaxNumberOfImageIndexes )
    {
        // Remote image indexes update mode.
        // Clear list of remote images.
        m_remoteImageIndexes.clear();

        // Append remote indices.
        for( int i = 0; i < KMaxNumberOfImageIndexes; i++ )
        {
            QString string = indexString.at(i);
            m_remoteImageIndexes.append( string.toInt() );
        }
        // Update remote images on the UI.
        emit showRemoteImages();
    }
}

void P2PEngine::setImageForExchange(int exchangeImageIndex)
{
   // Set the image for exchange.
   m_indexOfImageForExchange = m_localImageIndexes.at(exchangeImageIndex);

   // Update flag.
   m_exchangeImageSet = true;

   // Set the image exchange index.
   m_placeOfImageForExchange = exchangeImageIndex;
}

QString P2PEngine::getLocalIndexString() const
{
    QString indexString;
    for( int i = 0; i < m_localImageIndexes.size(); i++ )
    {
       indexString.append( QString::number( m_localImageIndexes.at(i)) );
    }
    return indexString;
}

QString P2PEngine::getExchangeIndexString() const
{
    return QString::number( m_indexOfImageForExchange );
}

bool P2PEngine::isExchangeImageSet()
{
    return m_exchangeImageSet;
}

bool P2PEngine::isWinner()
{
    bool ret(true);
    for ( int i = 1; i<KMaxNumberOfImageIndexes && ret; i++ )
    {
        if( getLocalImageFile(0) != getLocalImageFile(i) )
        {
            ret = false;
        }
    }
    return ret;
}

void P2PEngine::doReset()
{
    // Clear lists of remote and local images.
    m_remoteImageIndexes.clear();
    m_localImageIndexes.clear();

    // Initialize local image indices to random numbers.
    initLocalImageIndexes();

    // Initialize image exchange.
    m_indexOfImageForExchange = KImageNotSelected;
    m_placeOfImageForExchange = KImageNotSelected;
    m_exchangeImageSet = false;
    emit updateView();
}
