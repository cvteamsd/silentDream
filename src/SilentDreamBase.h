#ifndef SILENTDREAMBASE_H
#define SILENTDREAMBASE_H

#include <SilentDream/Global.h>
#include "SignalHandler.h"

class Loop;

class SilentDreamBase
{
public:
    explicit SilentDreamBase();
    virtual ~SilentDreamBase();

    virtual int init();
    virtual int destroy();
    virtual int exec() = 0;

protected:
    Loop* mLoop;

private:
    DISALLOW_EVIL_CONSTRUCTORS(SilentDreamBase);
};

#endif // SILENTDREAMBASE_H
