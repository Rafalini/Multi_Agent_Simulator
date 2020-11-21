QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_agenttest.cpp \
            ../../source/agent.cpp


HEADERS += ../../headers/agent.h
