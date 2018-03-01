TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH +=
DEFINES +=
LIBS += -pthread

SOURCES += \
    src/main.cpp \
    src/SilentDream.cpp \
    src/ArgumentParser.cpp \
    src/Log.cpp

HEADERS += \
    src/SilentDream.h \
    src/ArgumentParser.h \
    src/Log.h
