QT += quick quickcontrols2 websockets widgets

CONFIG += c++11

LIBS -= Qt/5.15.2/wasm_32/qml/Qt/WebSockets/libdeclarative_qmlwebsockets.a

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/agent.cpp \
        source/agents.cpp \
        source/city.cpp \
        source/linesegment.cpp \
        source/main.cpp \
        source/mapproperties.cpp \
        source/point.cpp \
        source/remoteconnector.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =


HEADERS += \
    headers/agent.h \
    headers/agents.h \
    headers/city.h \
    headers/linesegment.h \
    headers/mapproperties.h \
    headers/point.h \
    headers/remoteconnector.h
