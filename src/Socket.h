#ifndef SOCKET_H
#define SOCKET_H

#include <SilentDream/Log.h>
#include "Epoll.h"

class Socket
{
public:
    Socket(int domain, int type, int protocol);
    ~Socket();

    int initServer(struct sockaddr* addr, socklen_t len);
    int initClient();

    int start();
    int stop();

    static void cbAccept(Poll* p, int status, int event);
    static void cbServer(Poll* p, int status, int event);
    static void cbConnect(Poll* p, int status, int event);
    static void cbClient(Poll* p, int status, int event);


private:
    int mDomain;
    int mType;
    int mSockFd;
    Poll* mPoll;

    std::vector<Poll*> mClients;
};

#endif // SOCKET_H
