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
* Description:  Part of Qt NFC Setting sample application.
*/

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_nfcSettings(new NfcSettings(this))
{
    ui->setupUi(this);

    connect(m_nfcSettings, SIGNAL(nfcModeChanged(NfcSettings::NfcMode)), SLOT(displayNfcMode(NfcSettings::NfcMode)));
    connect(m_nfcSettings, SIGNAL(nfcErrorOccurred(NfcSettings::NfcError, int)), SLOT(displayNfcError(NfcSettings::NfcError, int)));
    connect(ui->m_resetPushButton, SIGNAL(clicked()), m_nfcSettings, SLOT(reset()));
    connect(ui->m_exitPushButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    displayNfcFeature(m_nfcSettings->nfcFeature());
    displayNfcMode(m_nfcSettings->nfcMode());
    displayNfcError(m_nfcSettings->nfcError(), 0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::displayNfcFeature(NfcSettings::NfcFeature nfcFeature)
{
    switch (nfcFeature)
    {
    case NfcSettings::NfcFeatureNotSupported:
        ui->m_nfcFeatureLabel->setText(tr("Not Supported"));
        break;
    case NfcSettings::NfcFeatureSupportedViaFirmwareUpdate:
        ui->m_nfcFeatureLabel->setText(tr("Update Firmware"));
        break;
    case NfcSettings::NfcFeatureSupported:
        ui->m_nfcFeatureLabel->setText(tr("Supported"));
        break;
    default:
        break;
    }
}

void Widget::displayNfcMode(NfcSettings::NfcMode nfcMode)
{
    switch (nfcMode)
    {
    case NfcSettings::NfcModeNotSupported:
        ui->m_nfcModeLabel->setText(tr("Not Supported"));
        break;
    case NfcSettings::NfcModeUnknown:
        ui->m_nfcModeLabel->setText(tr("Unknown"));
        break;
    case NfcSettings::NfcModeOn:
        ui->m_nfcModeLabel->setText(tr("On"));
        break;
    case NfcSettings::NfcModeCardOnly:
        ui->m_nfcModeLabel->setText(tr("Card Only"));
        break;
    case NfcSettings::NfcModeOff:
        ui->m_nfcModeLabel->setText(tr("Off"));
        break;
    default:
        break;
    }
}

void Widget::displayNfcError(NfcSettings::NfcError nfcError, int error)
{
    switch (nfcError)
    {
    case NfcSettings::NfcErrorNone:
        ui->m_nfcStatusLabel->setText(tr("NFC settings retrieved successfully."));
        break;
    case NfcSettings::NfcErrorFeatureSupportQuery:
        ui->m_nfcStatusLabel->setText(tr("Error %1: Unable to query NFC feature support.").arg(error));
        break;
    case NfcSettings::NfcErrorSoftwareVersionQuery:
        ui->m_nfcStatusLabel->setText(tr("Error %1: Unable to query device software version.").arg(error));
        break;
    case NfcSettings::NfcErrorModeChangeNotificationRequest:
        ui->m_nfcStatusLabel->setText(tr("Error %1: Unable to request NFC mode change notifications.").arg(error));
        break;
    case NfcSettings::NfcErrorModeChangeNotification:
        ui->m_nfcStatusLabel->setText(tr("Error %1: NFC mode change notification failed.").arg(error));
        break;
    case NfcSettings::NfcErrorModeRetrieval:
        ui->m_nfcStatusLabel->setText(tr("Error %1: Unable to retrieve current NFC mode.").arg(error));
        break;
    default:
        break;
    }
}
