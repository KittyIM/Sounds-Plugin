TARGET    = Sounds
TEMPLATE  = lib
QT       += core gui

SOURCES  += SoundsPlugin.cpp \
    SettingWidget.cpp

HEADERS  += SoundsPlugin.h \
    SDK/SettingPage.h \
    SDK/PluginCore.h \
    SDK/Plugin.h \
    SDK/constants.h \
    SDK/Message.h \
    SDK/SoundsConstants.h \
    SettingWidget.h

FORMS += \
    SettingWidget.ui

RESOURCES += \
    res/res.qrc
