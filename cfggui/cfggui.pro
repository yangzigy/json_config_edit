
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR += ../bin
OBJECTS_DIR = ../bin/obj
TARGET = cfggui
TEMPLATE = app
DEFINES -= UNICODE

CONFIG += c++11
CONFIG += warn_off  #不要啥都提示

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ./src

win32 {
	LIBS += -lwsock32
	DEFINES += WIN32
}

SOURCES += \
        cfgwindow.cpp \
    ./src/common.cpp \
    ./src/jsoncpp.cpp \
    cfgmain.cpp \ 
    qthttp.cpp

HEADERS += \
        cfgwindow.h \
    ./src/common.h \
    ./src/json.h \
    ./src/main.h \
    dictdis.h \
    qthttp.h

FORMS += \
        cfgwindow.ui \

