# Add files and directories to ship with the application
# by adapting the examples below.
files.source = loc/*.qm
# dir1.source = mydir
DEPLOYMENTFOLDERS = files #dir1

symbian:TARGET.UID3 = 0xE3FFD442

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the
# MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

SOURCES += main.cpp mainwindow.cpp widget.cpp
HEADERS += main.h mainwindow.h widget.h
FORMS += mainwindow.ui widget.ui

# Localisation support.
CODECFORTR = UTF-8
TRANSLATIONS += loc/$${TARGET}_en.ts \
                loc/$${TARGET}_ar.ts \
                loc/$${TARGET}_zh_HK.ts \
                loc/$${TARGET}_zh_CN.ts \
                loc/$${TARGET}_zh_TW.ts \
                loc/$${TARGET}_cs.ts \
                loc/$${TARGET}_da.ts \
                loc/$${TARGET}_nl.ts \
                loc/$${TARGET}_en_US.ts \
                loc/$${TARGET}_fi.ts \
                loc/$${TARGET}_fr.ts \
                loc/$${TARGET}_fr_CA.ts \
                loc/$${TARGET}_de.ts \
                loc/$${TARGET}_el.ts \
                loc/$${TARGET}_he.ts \
                loc/$${TARGET}_hi.ts \
                loc/$${TARGET}_hu.ts \
                loc/$${TARGET}_id.ts \
                loc/$${TARGET}_it.ts \
                loc/$${TARGET}_ms.ts \
                loc/$${TARGET}_no.ts \
                loc/$${TARGET}_pl.ts \
                loc/$${TARGET}_pt.ts \
                loc/$${TARGET}_pt_BR.ts \
                loc/$${TARGET}_ro.ts \
                loc/$${TARGET}_ru.ts \
                loc/$${TARGET}_sk.ts \
                loc/$${TARGET}_es.ts \
                loc/$${TARGET}_es_419.ts \
                loc/$${TARGET}_sv.ts \
                loc/$${TARGET}_th.ts \
                loc/$${TARGET}_tr.ts \
                loc/$${TARGET}_uk.ts \
                loc/$${TARGET}_vi.ts

# add NfcSettings support
include(nfcsettings/nfcsettings.pri)

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()
