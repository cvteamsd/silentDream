#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "Socket.h"

Socket::Socket(Loop* loop)
{
}

Socket::~Socket()
{

}

int Socket::initSocket(std::string serverAddr)
{
    struct addrinfo *addr;
    int ret = getaddrinfo(serverAddr.c_str(), nullptr, nullptr, &addr);
    if (ret != 0) {
        LOGE("serverAddr:%s, getaddrinfo failed:%s",serverAddr.c_str(), gai_strerror(ret));
        return -1 ;
    }
    std::shared_ptr<addrinfo>(addr, [](struct addrinfo* p) {
        LOGV("freeaddrinfo");
        ::freeaddrinfo(p);
    });

   mServerAddr = *addr->ai_addr;
   mServerAddrLen = addr->ai_addrlen;
   mDomain = addr->ai_family;
   mType = addr->ai_socktype;
   mProtocol = addr->ai_protocol;

    mSockFd = ::socket(mDomain, mType|SOCK_NONBLOCK, mProtocol);
    if (mSockFd < 0) {
        LOGE("create socket failed:%s", strerror(errno));
        return -1;
    }

    int reuse = 1;
    if (setsockopt(mSockFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
        LOGE("setsockopt failed!");
        return -1;
    }

    mPoll = new Poll(mLoop, mSockFd, this);

    return 0;
}

int Socket::initServer()
{
    int err = ::bind(mSockFd, &mServerAddr, sizeof(struct sockaddr));
    if (err < 0) {
        LOGE("bind:%s", strerror(errno));
        return -1;
    }

    err = ::listen(mSockFd, 10);
    if (err < 0) {
        LOGE("listen:%s", strerror(errno));
        return -1;
    }

    mPoll->start(cbAccept, EPOLLIN);

    return 0;
}


void Socket::cbAccept(Poll *p, int status, int event)
{

}

void Socket::cbConnect(Poll *p, int status, int event)
{

}

void Socket::ioHandler(Poll *p, int status, int event)
{

}




