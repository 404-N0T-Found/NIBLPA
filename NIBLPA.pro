QT += core
QT -= gui

TARGET = test0
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    node.cpp \
    network.cpp

HEADERS += \
    node.h \
    network.h

