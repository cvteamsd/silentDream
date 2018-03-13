#ifndef SILENTDREAMCLIENT_H
#define SILENTDREAMCLIENT_H

#include "SilentDreamBase.h"

class ArgumentParser;
class Socket;

class SilentDreamClient : public SilentDreamBase
{
public:
    SilentDreamClient(ArgumentParser& argParser);
    virtual ~SilentDreamClient();

    virtual int init();
    virtual int exec();
    virtual int destroy();

private:
    ArgumentParser& mArgParser;


    Socket* mSocket = nullptr;



    DISALLOW_EVIL_CONSTRUCTORS(SilentDreamClient);
};

#endif // SILENTDREAMCLIENT_H
