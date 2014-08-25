TARGET = greeting

QT += network
QT -= gui

CONFIG += release

INCLUDEPATH += ../../src
LIBS += -L../../lib

win32 {
    debug: LIBS += -lqhttpserver
    else: LIBS += -lqhttpserver
} else {
    LIBS += -lqhttpserver
}

SOURCES = greeting.cpp
HEADERS = greeting.h
