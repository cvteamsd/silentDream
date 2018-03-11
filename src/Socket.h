#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

#include <SilentDream/Log.h>
#include <string>
#include "Epoll.h"

class Socket
{
public:
    Socket(Loop* loop);
    ~Socket();

    int initSocket(std::string address);
    int initServer();
    int connect();

    int start();
    int stop();

    static void cbAccept(Poll* p, int status, int event);
    static void cbConnect(Poll* p, int status, int event);
    static void ioHandler(Poll* p, int status, int event);

private:
    int mDomain;
    int mType;
    int mProtocol;
    int mSockFd;
    bool mIsServer;
    struct sockaddr mServerAddr;
    socklen_t mServerAddrLen;
    Poll* mPoll;
    Loop* mLoop;

    std::vector<Poll*> mClients;
};

#endif // SOCKET_H
