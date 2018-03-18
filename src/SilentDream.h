#ifndef _SILENT_DREAM_H
#define _SILENT_DREAM_H

#include <set>
#include "SilentDreamBase.h"
#include "Socket.h"

class SilentDreamWorker;

class SilentDream  : public SilentDreamBase, public SocketServerHandler
{
public:
    SilentDream();
    virtual ~SilentDream();

    virtual int init();
    virtual int destroy();

    virtual void onAccepted(int sockFd, struct sockaddr_in* addr, socklen_t addrLen);
    virtual void onError(Socket::ErrorCode);

private:
    int daemonize();
    int checkRunning(); 
    int initServer();

    Socket* mSocket = nullptr;
    std::set<SilentDreamWorker*> mWorkers;
    DISALLOW_EVIL_CONSTRUCTORS(SilentDream);
};


#endif
