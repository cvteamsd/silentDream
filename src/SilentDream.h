#ifndef _SILENT_DREAM_H
#define _SILENT_DREAM_H

#include "SilentDreamBase.h"

class Socket;

class SilentDream  : public SilentDreamBase
{
public:
    SilentDream();
    virtual ~SilentDream();

    virtual int init();
    virtual int destroy();
    virtual int exec();

private:
    SilentDream(const SilentDream&);
    SilentDream& operator=(const SilentDream&);

private:
    int daemonize();
    int checkRunning(); 


    Socket* mSocket = nullptr;
};


#endif
