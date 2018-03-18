#ifndef SILENTDREAMWORKER_H
#define SILENTDREAMWORKER_H

#include "Socket.h"
#include "ArgumentParser.h"

class SilentDreamWorker : public SocketServerHandler
{
public:
    SilentDreamWorker(Loop* loop, Socket* socket);
    ~SilentDreamWorker();

    virtual void onData(const void *buf, size_t len);
    virtual void onError(Socket::ErrorCode);

private:
    int handleRequest(const json &request, json &response);

    Loop* mLoop;
    Socket* mSocket;

    DISALLOW_EVIL_CONSTRUCTORS(SilentDreamWorker);
};

#endif // SILENTDREAMWORKER_H
