# Add more folders to ship with the application, here
folder_01.source = qml/P2Pexample
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE217013B

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices LocalServices

# Icon for symbian application
symbian:ICON = qml/P2Pexample/p2p_icon.svg


# Define QMLJSDEBUGGER to allow debugging of QML in debug builds
# (This might significantly increase build time)
# DEFINES += QMLJSDEBUGGER

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
CONFIG += mobility
MOBILITY += connectivity

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    nfcconnection.cpp \
    p2pengine.cpp \


# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += main.h \
    nfcconnection.h \
    p2pengine.h
