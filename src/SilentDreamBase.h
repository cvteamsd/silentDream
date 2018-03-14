#ifndef SILENTDREAMBASE_H
#define SILENTDREAMBASE_H

#include <SilentDream/Global.h>
#include "SignalHandler.h"

class Loop;

class SilentDreamBase
{
public:
    explicit SilentDreamBase();
    virtual ~SilentDreamBase() = 0;

    virtual int init();
    virtual int destroy();
    virtual int exec();


protected:
    Loop* mLoop;

private:
    DISALLOW_EVIL_CONSTRUCTORS(SilentDreamBase);
};

#endif // SILENTDREAMBASE_H
