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

#include "main.h"
#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name();

    QTranslator translator;
    translator.load(QString("nfcsettingsapplication_") + locale);
    app.installTranslator(&translator);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow.showExpanded();

    return app.exec();
}
