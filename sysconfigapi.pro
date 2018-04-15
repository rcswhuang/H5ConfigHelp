#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T22:54:45
#
#-------------------------------------------------

QT  += xml
QT       -= gui

TARGET = sysconfigapi
TEMPLATE = lib
DESTDIR = ../lib

INCLUDEPATH += \
            ../include

DEFINES += SYSCONFIG_EXPORT

SOURCES += hxml.cpp \
    hsysconfighandle.cpp \
    hsysconfig.cpp

HEADERS += hxml.h \
    hsysconfighandle.h \
    hsysconfig.h

LIBS += -L../lib/lib64_linux_xerces

unix {
    LIBS += -lxerces-c
    target.path = /usr/lib
    INSTALLS += target
}
