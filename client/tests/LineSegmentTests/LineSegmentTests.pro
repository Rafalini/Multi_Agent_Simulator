QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_linesegmenttests.cpp \
            ../../source/point.cpp \
            ../../source/linesegment.cpp


HEADERS += ../../headers/point.h \
           ../../headers/linesegment.h
