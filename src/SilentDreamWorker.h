#ifndef SILENTDREAMWORKER_H
#define SILENTDREAMWORKER_H

#include "Socket.h"
#include "ArgumentParser.h"

class SilentDream;
class SilentDreamWorker : public SocketServerHandler
{
public:
    SilentDreamWorker(Loop* loop, Socket* socket, SilentDream*);
    ~SilentDreamWorker();

    virtual void onData(const void *buf, size_t len);
    virtual void onError(Socket::ErrorCode);
    virtual void onDisConnected();

private:
    int handleRequest(const json &request, json &response);

    Loop* mLoop;
    Socket* mSocket;
    SilentDream* mManager;

    DISALLOW_EVIL_CONSTRUCTORS(SilentDreamWorker);
};

#endif // SILENTDREAMWORKER_H
