#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T22:54:45
#
#-------------------------------------------------

QT       += xml

QT       -= gui

TARGET = sysconfigapi
TEMPLATE = lib

DEFINES += SYSCONFIGAPI_LIBRARY

SOURCES += hxml.cpp \
    hsysconfigapi.cpp \
    hsysconfighandle.cpp

HEADERS += hxml.h \
        hsysconfigapi.h\
        sysconfigapi_global.h \
    sysconfigapi.h \
    hsysconfighandle.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
