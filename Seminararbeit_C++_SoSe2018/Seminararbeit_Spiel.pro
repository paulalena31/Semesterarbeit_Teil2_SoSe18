QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Paulas_Play
TEMPLATE = app
 

SOURCES += main.cpp \
        meinWidget.cpp \
        zeichenFeld.cpp

HEADERS  += meinWidget.h \
            zeichenFeld.h

CONFIG += c++11
