#-------------------------------------------------
#
# Project created by QtCreator 2013-03-03T17:08:25
#
#-------------------------------------------------

QT       += core gui network

TARGET = UDP_multicast
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    cmulticast.cpp

HEADERS  += dialog.h \
    cmulticast.h

FORMS    += dialog.ui

RESOURCES += \
    resource.qrc

win32: RC_FILE += resource.rc
