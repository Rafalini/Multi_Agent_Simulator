QT += websockets quick widgets
Qt -= declarative

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/agent.cpp \
        source/agents.cpp \
        source/city.cpp \
        source/main.cpp \
        source/mapproperties.cpp \
        source/path.cpp \
        source/point.cpp \
        source/remoteconnector.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


HEADERS += \
    headers/agent.h \
    headers/agents.h \
    headers/city.h \
    headers/mapproperties.h \
    headers/path.h \
    headers/point.h \
    headers/remoteconnector.h
