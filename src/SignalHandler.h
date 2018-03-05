#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <pthread.h>
#include <setjmp.h>
#include <signal.h>

class SignalHandler
{
public:
    static SignalHandler& instace();
    ~SignalHandler();

    int install();

    void setMonitorSignals(sigset_t signals);
    int setCustomSigHandler(int signo, void(*)(int));

    sigjmp_buf mSigJmpBuf;

private:
    SignalHandler();
    static SignalHandler* self;

    int initSignalMonitor();

    int setHardwareSigHandler();
    static void hardwareSigHander(int signo);
    static void dumpstack();

    void (*mCustomHandlers[32])(int);



    sigset_t mSignalMask;
    sigset_t mOldSignalMask;
    pthread_t mSignalTid;
    static void* customSignalThreadFn(void *arg);
};

#endif // SIGNALHANDLER_H
