QT += quick quickcontrols2 websockets network widgets

CONFIG += c++11

#DESTDIR = build

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
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DESTDIR = dest
#OBJECTS_DIR = dest/obj
#MOC_DIR = dest/.MOC_DIR
#RCC_DIR = dest/.rcc
#UI_DIR = dest/.ui

HEADERS += \
    headers/agent.h \
    headers/agents.h \
    headers/city.h \
    headers/linesegment.h \
    headers/mapproperties.h \
    headers/point.h \
    headers/remoteconnector.h
