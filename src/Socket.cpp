#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "Socket.h"

#define SERV_PORT  28979

Socket::Socket(Loop* loop)
    : mLoop(loop)
{
}

Socket::~Socket()
{

}

void Socket::setClientHandler(SocketClientHandler *clientHandler)
{
    mClientHandler = clientHandler;
}

template <bool isServer = SERVER>
ssize_t Socket::read(uint8_t* buf, size_t len)
{
    ssize_t err = 0;

    if (isServer) {

    } else {
        ::read(mSockFd, buf, len);

    }

    return err;
}

template <bool isServer = SERVER>
ssize_t Socket::write(const void *buf, size_t len)
{
    ssize_t err = 0;

    if (isServer) {

    } else {
        err = ::write(mSockFd, buf, len);
    }

    return err;
}


int Socket::initAddress(std::string serverAddr)
{
    struct addrinfo *addr;
    struct addrinfo hint;

    memset(&hint, 0, sizeof(hint));

    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    int ret = getaddrinfo(serverAddr.c_str(), nullptr, &hint, &addr);
    if (ret != 0) {
        LOGE("serverAddr:%s, getaddrinfo failed:%s",serverAddr.c_str(), gai_strerror(ret));
        return -1 ;
    }

    std::shared_ptr<addrinfo> _(addr, [](struct addrinfo* p) {
        ::freeaddrinfo(p);
    });

    struct sockaddr_in* addr_in = (struct sockaddr_in*)addr->ai_addr;
    addr_in->sin_port = htons(SERV_PORT);
    mServerAddr = *addr_in;
    mServerAddrLen = addr->ai_addrlen;
    mDomain = AF_INET;
    mType = SOCK_STREAM;
    mProtocol = IPPROTO_TCP;

    return 0;
}

int Socket::createSocket()
{
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
    LOGI("server:%s:%d", inet_ntoa(mServerAddr.sin_addr), ntohs(mServerAddr.sin_port));

    int err = ::bind(mSockFd, (struct sockaddr*)&mServerAddr, sizeof(struct sockaddr));
    if (err < 0) {
        LOGE("bind:%s", strerror(errno));
        return -1;
    }

    err = ::listen(mSockFd, 10);
    if (err < 0) {
        LOGE("listen:%s", strerror(errno));
        return -1;
    }

    mPoll->start(EPOLLIN, cbAccept);

    return 0;
}

int Socket::connect()
{
    LOGI("connect:%s:%d", inet_ntoa(mServerAddr.sin_addr), ntohs(mServerAddr.sin_port));

    int err = ::connect(mSockFd, (struct sockaddr*)&mServerAddr, mServerAddrLen);
    if (err == 0) {
        LOGI("connect success!");
    } else {
        if (errno != EINPROGRESS) {
            LOGI("connect failed:%s", strerror(errno));
            return -1;
        }
        mPoll->start(EPOLLOUT, cbConnect);
    }

    return 0;
}

////////////////////////////////////////////////////////
void Socket::cbAccept(Poll *p, int status, int event)
{
    if (status < 0) {
        LOGE("accept error!");
        return;
    }

    Socket* s = static_cast<Socket*>(p->userData());

    if (event & EPOLLIN) {
        s->onAccept();
    }
}

int Socket::onAccept()
{
    int clientSock;
    struct sockaddr client;
    socklen_t sockLen = sizeof(struct sockaddr);
    clientSock = ::accept(mSockFd, &client, &sockLen);
    if (clientSock < 0) {
        assert (errno!=EAGAIN && errno!=EWOULDBLOCK);
        LOGE("accept failed:%s", strerror(errno));
        return -1;
    }

    struct sockaddr_in* client_in = (struct sockaddr_in*)&client;
    LOGI("client:%s:%d", inet_ntoa(client_in->sin_addr), ntohs(client_in->sin_port));

    Poll* poll = new Poll(mLoop, clientSock, this);
    poll->start(EPOLLIN, cbServer);
    mClients.insert(poll);

    return 0;
}


void Socket::cbConnect(Poll *p, int status, int event)
{
    if (status < 0) {
        LOGE("cbConnect error:%s %s", event&EPOLLERR?"EPOLLERR":"", event&EPOLLHUP?"EPOLLHUP":"");
        p->stop();
        return;
    }

    Socket* s = static_cast<Socket*>(p->userData());
    int ret;
    int err;
    socklen_t len = sizeof(err);

    if (event & EPOLLOUT) {
        ret = getsockopt(p->fd(), SOL_SOCKET, SO_ERROR, &err, &len);
        assert(ret == 0);
        if (err == 0) {
            LOGI("cbConnect success!");
            if (s->mClientHandler) {
                s->mClientHandler->onConnected();
            }
        } else {
            LOGE("cbConnect failed:%s", strerror(err));
        }

        p->change(EPOLLIN, cbClient);
    }
}

void Socket::cbServer(Poll *p, int status, int event)
{
    Socket* s = static_cast<Socket*>(p->userData());
    int err;
    uint8_t recvBuf[1024];

    if (status < 0) {
        event |= EPOLLIN|EPOLLOUT;
    }

    if (event & EPOLLIN) {
        memset(recvBuf, 0, sizeof(recvBuf));
        err = ::recv(p->fd(), recvBuf, sizeof(recvBuf), 0);
        if (err <= 0) {
            if (err < 0)
                LOGE("cbServer error:%s", strerror(errno));

            p->stop();
            s->mClients.erase(p);
            ::close(p->fd());
            delete p;

            return;
        }
        LOGI("%s", recvBuf);
    }
}

void Socket::cbClient(Poll *p, int status, int event)
{
    Socket* s = static_cast<Socket*>(p->userData());
    int err;
    uint8_t recvBuf[1024];

    if (status < 0) {
        event |= EPOLLIN|EPOLLOUT;
    }

    if (event & EPOLLIN) {
        memset(recvBuf, 0, sizeof(recvBuf));
        err = ::recv(p->fd(), recvBuf, sizeof(recvBuf), 0);
        if (err <= 0) {
            LOGE("cbServer error:%s", strerror(errno));

            p->stop();
            ::close(p->fd());
            delete p;
        }
        LOGI("%s", recvBuf);
    }

}

void Socket::ioHandler(Poll *p, int status, int event)
{

}



template ssize_t Socket::write<CLIENT>(const void*, size_t);

