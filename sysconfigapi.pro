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

SOURCES += \
    hsysconfighandle.cpp \
    hsysconfig.cpp \
    hxercesxml.cpp \
    hqtxml.cpp

HEADERS += \
    hsysconfighandle.h \
    hsysconfig.h \
    hxercesxml.h \
    hqtxml.h

LIBS += -L../lib/lib64_linux_xerces

unix {
    LIBS += -lxerces-c
    target.path = /usr/lib
    INSTALLS += target
}
