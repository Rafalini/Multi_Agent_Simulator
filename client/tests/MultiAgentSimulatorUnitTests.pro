QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    main.cpp \
    ../source/agent.cpp \
    ../source/agents.cpp \
    ../source/city.cpp \
    ../source/point.cpp \
    ../source/path.cpp


INCLUDEPATH += ../headers

HEADERS += tst_agentstests.hpp \
        tst_pathtests.hpp \
        tst_agenttest.hpp   \
        tst_pointtests.hpp \
        tst_citytests.hpp \
        ../headers/agent.h \
        ../headers/agents.h \
        ../headers/city.h \
        ../headers/point.h \
        ../headers/path.h
