#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

#include <SilentDream/Log.h>
#include <string>
#include "Epoll.h"

enum {
    CLIENT,
    SERVER
};

class SocketClientHandler
{
public:
    virtual ~SocketClientHandler() {}
    virtual void onConnected() = 0;
    virtual void onData(const void* buf, size_t len) = 0;
};

class SocketServerHandler
{
public:
    virtual ~SocketServerHandler() {}
    virtual void onAccepted() = 0;
    virtual void onData(const void* buf, size_t len) = 0;
};


class Socket
{
public:
    Socket(Loop* loop);
    ~Socket();

    int createSocket();
    int initServer();
    int initAddress(std::string address);
    int connect();

    int start();
    int stop();

    template <bool isServer = true>
    ssize_t write(const void* buf, size_t len);
    void setClientHandler(SocketClientHandler* clientHandler);
    void setServerHandler(SocketServerHandler* serverHandler);

    static void cbAccept(Poll* p, int status, int event);
    static void cbServer(Poll* p, int status, int event);
    static void cbConnect(Poll* p, int status, int event);
    static void cbClient(Poll* p, int status, int event);

    static void ioHandler(Poll* p, int status, int event);

private:
    int onAccept();


    int mDomain;
    int mType;
    int mProtocol;
    int mSockFd;
    bool mIsServer;
    struct sockaddr_in mServerAddr = {0};
    socklen_t mServerAddrLen;
    Poll* mPoll;
    Loop* mLoop;

    SocketClientHandler* mClientHandler = nullptr;

    std::set<Poll*> mClients;
};


#endif // SOCKET_H
