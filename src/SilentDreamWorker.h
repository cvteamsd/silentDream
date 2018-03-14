#ifndef SILENTDREAMWORKER_H
#define SILENTDREAMWORKER_H

#include "Socket.h"

class SilentDreamWorker : public SocketServerHandler
{
public:
    SilentDreamWorker(Loop* loop, Socket* socket);
    ~SilentDreamWorker();

    virtual void onData(const void *buf, size_t len);
    virtual void onError(Socket::ErrorCode);

private:
    Loop* mLoop;
    Socket* mSocket;
};

#endif // SILENTDREAMWORKER_H
