QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_pathtests.cpp \
            ../../source/point.cpp \
            ../../source/path.cpp


HEADERS += ../../headers/point.h \
           ../../headers/path.h
