#ifndef SILENTDREAMCLIENT_H
#define SILENTDREAMCLIENT_H

#include "SilentDreamBase.h"

class ArgumentParser;

class SilentDreamClient : public SilentDreamBase
{
public:
    SilentDreamClient(ArgumentParser& argParser);
    virtual ~SilentDreamClient();

    int exec();

private:
    ArgumentParser& mArgParser;

    DISALLOW_EVIL_CONSTRUCTORS(SilentDreamClient);
};

#endif // SILENTDREAMCLIENT_H
