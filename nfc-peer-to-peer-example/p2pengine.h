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

#ifndef P2PENGINE_H
#define P2PENGINE_H

/*!
 * \file
 * \brief Implements game logic.
 */

#include <QWidget>
#include <QStringList>
#include <QVector>

class NfcConnection;

//! Implements game logic.
/*!
  This class creates the game logic engine. It is contains images used in a game,
  lists of local and the remote player's images, and the image selected for exchange.
  Game state is updated based on signals from the NfcConnection class.
*/

class P2PEngine : public QObject
{
    Q_OBJECT

public:
    //! Class Constructor.
    /*!
     *  \param parent Parent for the object.
     */
    explicit P2PEngine(QObject *parent = 0);

    //! Destructor.
    virtual ~P2PEngine();

    //! Returns a string that contains the name of the image file referenced from localImageIndexes.at(index).
    /*!
      \param index The index of the local image, 0 <= index < KMaxNumberOfImageIndexes.
      \return QString containing image filename.
    */
    Q_INVOKABLE QString getLocalImageFile(int index) const;

    //! Returns a string that contains the name of the image file referenced from remoteImageIndexes.at(index).
    /*!
      \param index The index of the remote image, 0 <= index < KMaxNumberOfImageIndexes.
      \return QString containing image filename.
    */
    Q_INVOKABLE QString getRemoteImageFile(int index) const;

    //! Set the local image index that will be used for next exchange between players localImageIndexes.at(exchangeImageIndex).
    /*!
      \param exchangeImageIndex The index of the local image, 0 <= index < KMaxNumberOfImageIndexes, that the player wants to exchange.
    */
    Q_INVOKABLE void setImageForExchange(int exchangeImageIndex);

    //! Returns a string containing local image indices converted to a string that can be transmitted via an NFC connection.
    /*!
      \return A string containing local image indices.
    */
    QString getLocalIndexString() const;

    //! Returns a string containing the index of the image to exchange converted to a string that can be transmitted via an NFC connection.
    /*!
      \return A string containing the index of the local image to exchange.
    */
    QString getExchangeIndexString() const;

    //! Checks if an image has been selected for exchange.
    /*!
      \return false if not selected, true otherwise.
    */
    bool isExchangeImageSet();

    //! Passes the string received via an NFC connection to the engine. The sting is parsed inside this function.
    /*!
      \param indexString A string containing a message received from the remote player. Contains either the remote index list or the remote image index for exchange.
    */
    void setRemoteIndexes(QString indexString);

    //! Resets the game engine state to initial condition. Called after the winning condition is met.
    Q_INVOKABLE void doReset();

signals:
    //! Signal emmited when the list of remote images is updated.
    void showRemoteImages();

    //! Signal emmited when the winning condition is met.
    void showWinnerMessage();

    //! Signal emmited when image exchange is done, or a new game is started.
    void updateView();

private:
     //! Initialize local image indices to random numbers.
    void  initLocalImageIndexes();

    //! Returns a string that contains the name of the image file referenced from arrayOfImageNames.at(index).
    /*!
      \param index The index of the image, 0 <= index < KMaxNumberOfImageIndexes.
      \return QString containing image filename.
    */
    QString getImageFileNameByIndex(int index) const;

    //! Checks if winning condition are met.
    /*!
      \return true if this player has won the game, false otherwise.
    */
    bool isWinner();

private:
    QStringList m_arrayOfImageNames;    //! Array of names of image files
    QVector<int> m_localImageIndexes;   //! Array of indices of local images
    QVector<int> m_remoteImageIndexes;  //! Array of indices of remote images

    NfcConnection *m_nfcConnection;     //! Reference to NfcConnection class
    int m_indexOfImageForExchange;      //! Index of image for exchange
    int m_placeOfImageForExchange;      //! Exchange image place on pane
    bool m_exchangeImageSet;            //! Flag denoting whether an image has been selected for exchange.
};

#endif // P2PENGINE_H
