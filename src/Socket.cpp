#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Socket.h"

Socket::Socket(int domain, int type, int protocol)
    : mDomain(domain)
    , mType(type)
{
//    mFd = ::socket(domain, type, protocol);

}

int Socket::initServer(sockaddr *addr, socklen_t len)
{
    struct sockaddr_in addrv4;

    addrv4.sin_family = AF_INET;
//    addrv4.sin_addr
}
