QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_citytests.cpp \
            ../../source/point.cpp \
            ../../source/city.cpp \
            ../../source/path.cpp

HEADERS += ../../headers/point.h \
            ../../headers/city.h \
            ../../headers/path.h
