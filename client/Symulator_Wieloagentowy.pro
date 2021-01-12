QT += websockets quick widgets quickcontrols2

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/Agent.cpp \
        source/Agents.cpp \
        source/City.cpp \
        source/Main.cpp \
        source/MapProperties.cpp \
        source/Path.cpp \
        source/Point.cpp \
        source/RemoteConnector.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

INCLUDEPATH += headers

HEADERS += \
    headers/Agent.h \
    headers/Agents.h \
    headers/City.h \
    headers/Mapproperties.h \
    headers/Path.h \
    headers/Point.h \
    headers/RemoteConnector.h
