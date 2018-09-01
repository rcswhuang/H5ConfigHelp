#-------------------------------------------------
#
# Project created by huangw 2017-03-01T22:54:45
#
#-------------------------------------------------

QT += xml
QT -= gui

TARGET = H5ConfigHelp
TEMPLATE = lib
DESTDIR = ../lib

INCLUDEPATH += \
            ../include

DEFINES += SYSCONIFG_DLL

SOURCES += \
    hsysconfighandle.cpp \
    hsysconfig.cpp \
    #hxercesxml.cpp \
    hqtxml.cpp

HEADERS += \
    hsysconfighandle.h \
    hsysconfig.h \
    #hxercesxml.h \
    hqtxml.h

#LIBS += -L../lib/lib64-xerces-vc12

win32{
#debug:{LIBS += ../lib/lib64-xerces-vc12/x64debug/xerces-c_3D.lib}
#release:{LIBS += ../lib/lib64-xerces-vc12/x64release/xerces-c_3.lib}
}
unix {
    #LIBS += -L../lib/lib64_linux_xercesc -lxerces-c
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj
}
