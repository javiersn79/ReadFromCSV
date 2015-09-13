QT += core
QT -= gui

INCLUDEPATH += /usr/local/boost_1_59_0

CONFIG += c++11

TARGET = ReadFromCSV
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

