TARGET = bodydata

QT += network
QT -= gui

SOURCES = bodydata.cpp
HEADERS = bodydata.h

unix: LIBS += -L$$OUT_PWD/../qhttpserver/lib/ -lqhttpserver

INCLUDEPATH += $$PWD/../qhttpserver/src
DEPENDPATH += $$PWD/../qhttpserver/src