# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xE1A4EB42

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
maemo5 {
#install debian packages libqtm-11-location_1.1.2, libqtm-11-location-dbg and libqtm-11-dev (Fremantle Extras free armel) on Nokia n900
    CONFIG += mobility11
#install debian packages libqtm-12-location_1.2.0, libqtm-12-location-dbg and libqtm-12-dev in sysroots/fremantle folder
    #CONFIG += mobility12
    MOBILITY += location
}
else {
    CONFIG += mobility
    MOBILITY += location
}

#Windows
INCLUDEPATH += "C:\QtSDK\Maemo\4.6.2\sysroots\fremantle-arm-sysroot-20.2010.36-2-slim\opt\qtm11\include\QtLocation"
#Linux
#INCLUDEPATH += "/opt/QtSDK/Desktop/Qt/474/gcc/include/QtMobility/"

#INCLUDEPATH += /opt/QtSDK/Maemo/4.6.2/sysroots/fremantle-arm-sysroot-20.2010.36-2-slim/usr/include/QtMobility/QtLocation
#LIBS += /opt/QtSDK/Maemo/4.6.2/sysroots/fremantle-arm-sysroot-20.2010.36-2-slim/opt -L
QT += network

SOURCES += main.cpp \
    geomap.cpp \
    mappingwidget.cpp \
    zoombuttonitem.cpp \
    mapmarker.cpp \
    mapoverlay.cpp \
    wedge.cpp \
    utilities.cpp \
    networkclient.cpp \
    peerstate.cpp \
    zoomslideritem.cpp
HEADERS += \
    geomap.h \
    mappingwidget.h \
    zoombuttonitem.h \
    mapmarker.h \
    mapoverlay.h \
    wedge.h \
    global.h \
    utilities.h \
    networkclient.h \
    peerstate.h \
    zoomslideritem.h
FORMS +=

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

RESOURCES += \
    Icons.qrc
















