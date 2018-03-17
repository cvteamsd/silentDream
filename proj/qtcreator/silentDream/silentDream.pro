TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += link_pkgconfig
PKGCONFIG += libunwind

INCLUDEPATH += src/include src/modules
DEFINES +=
LIBS += -pthread -ldl

SOURCES += \
    src/main/main.cpp \
    src/SilentDream.cpp \
    src/ArgumentParser.cpp \
    src/Log.cpp \
    src/Epoll.cpp \
    src/Socket.cpp \
    src/SilentDreamClient.cpp \
    src/SilentDreamWorker.cpp \
    src/SignalHandler.cpp \
    src/SilentDreamBase.cpp \
    src/CallStack.cpp \
    src/Util.cpp \
    src/PluginManager.cpp

HEADERS += \
    src/include/SilentDream/Log.h \
    src/include/SilentDream/Global.h \
    src/include/SilentDream/Util.h \
    src/include/SilentDream/PluginManager.h \
    src/include/SilentDream/App.h \
    src/include/SilentDream/PluginBase.h \
    src/include/SilentDream/FactoryBase.h \
    src/ArgumentParser.h \
    src/Epoll.h \
    src/Socket.h \
    src/SilentDreamClient.h \
    src/SilentDreamWorker.h \
    src/SignalHandler.h \
    src/SilentDreamBase.h \
    src/SilentDream.h \
    src/CallStack.h
