TARGET     = Sounds
TEMPLATE   = lib
QT        += core gui

SOURCES   += SoundsPlugin.cpp \
             SoundsSettingsPage.cpp

HEADERS   += SoundsPlugin.h \
             SoundsSettingsPage.h

FORMS     += SoundsSettingsPage.ui

RESOURCES += res/res.qrc

isEmpty(SDK_PATH):error(Set the SDK_PATH variable!)
include($$SDK_PATH/KittySDK.pri)
