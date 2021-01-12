QT += testlib
QT -= gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    Main.cpp \
    ../source/Agent.cpp \
    ../source/Agents.cpp \
    ../source/City.cpp \
    ../source/Point.cpp \
    ../source/Path.cpp \
    ../source/MapProperties.cpp


INCLUDEPATH += ../headers

HEADERS += tst_agentstests.hpp \
        tst_pathtests.hpp \
        tst_agenttest.hpp   \
        tst_pointtests.hpp \
        tst_citytests.hpp \
        ../headers/Agent.h \
        ../headers/Agents.h \
        ../headers/City.h \
        ../headers/Point.h \
        ../headers/Path.h \
        ../headers/MapProperties.h
