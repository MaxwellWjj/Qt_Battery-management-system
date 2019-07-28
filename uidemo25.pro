#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T18:38:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts serialport

TARGET      = uidemo25
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/../bin

INCLUDEPATH += $$PWD
RESOURCES   += other/main.qrc
RESOURCES   += other/qss.qrc
CONFIG      += warn_off

SOURCES     += main.cpp \
    plotmanager.cpp \
    chartview.cpp \
    pointposition.cpp \
    tcpserver.cpp
HEADERS     += head.h \
    plotmanager.h \
    chartview.h \
    pointposition.h \
    tcpserver.h

include     ($$PWD/api/api.pri)
include     ($$PWD/form/form.pri)

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/api
INCLUDEPATH += $$PWD/form

INCLUDEPATH += $$PWD/sdk

CONFIG(release, debug|release){
LIBS        += -L$$PWD/sdk/ -lquc
} else {
unix {LIBS  += -L$$PWD/sdk/ -lquc}
else {LIBS  += -L$$PWD/sdk/ -lqucd}
}
