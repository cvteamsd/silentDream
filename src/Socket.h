#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

#include <SilentDream/Log.h>
#include <string>
#include "Epoll.h"

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

    static void cbAccept(Poll* p, int status, int event);
    static void cbConnect(Poll* p, int status, int event);
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

    std::vector<Poll*> mClients;
};

#endif // SOCKET_H
