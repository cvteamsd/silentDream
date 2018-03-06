TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += link_pkgconfig
PKGCONFIG += libunwind

INCLUDEPATH += src/include src/modules
DEFINES +=
LIBS += -pthread

SOURCES += \
    src/main.cpp \
    src/SilentDream.cpp \
    src/ArgumentParser.cpp \
    src/Log.cpp \
    src/Epoll.cpp \
    src/Socket.cpp \
    src/SilentDreamClient.cpp \
    src/SilentDreamWorker.cpp \
    src/SignalHandler.cpp \
    src/SilentDreamBase.cpp

HEADERS += \
    src/ArgumentParser.h \
    src/Epoll.h \
    src/Socket.h \
    src/SilentDreamClient.h \
    src/SilentDreamWorker.h \
    src/SignalHandler.h \
    src/include/SilentDream/Log.h \
    src/include/SilentDream/Global.h \
    src/SilentDreamBase.h \
    src/SilentDream.h
