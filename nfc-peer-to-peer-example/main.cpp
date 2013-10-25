/*
============================================================================
 Name        : P2Pexample.cpp
 Author      :
 Copyright   : Your copyright notice
 Description : Main GUI Application
============================================================================
*/

#include <QtGui/QApplication>
#include <QtDeclarative>

#include "main.h"
#include "qmlapplicationviewer.h"
#include "p2pengine.h"


//! The main function.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<P2PEngine>("P2PEngine", 1, 0, "P2PEngine");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    viewer.setMainQmlFile(QLatin1String("qml/P2Pexample/main.qml"));
    viewer.showFullScreen();
    return app.exec();
}
