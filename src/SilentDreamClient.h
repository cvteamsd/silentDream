#ifndef SILENTDREAMCLIENT_H
#define SILENTDREAMCLIENT_H

#include "SilentDreamBase.h"
#include "Socket.h"
#include "ArgumentParser.h"

class ArgumentParser;
class Socket;

class SilentDreamClient : public SilentDreamBase, public SocketClientHandler
{
public:
    SilentDreamClient(ArgumentParser& argParser);
    virtual ~SilentDreamClient();

    virtual int init();
    virtual int destroy();

    virtual void onConnected();
    virtual void onData(const void* buf, size_t len);
    virtual void onError(Socket::ErrorCode);

private:
    int connectServer();

    ArgumentParser& mArgParser;
    Socket* mSocket = nullptr;
    json mArgs;

    DISALLOW_EVIL_CONSTRUCTORS(SilentDreamClient);
};

#endif // SILENTDREAMCLIENT_H
