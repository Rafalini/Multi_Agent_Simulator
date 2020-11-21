QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_pointtests.cpp \
            ../../source/point.cpp

HEADERS += ../../headers/point.h
