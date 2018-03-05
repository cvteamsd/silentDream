#ifndef _SILENT_DREAM_H
#define _SILENT_DREAM_H

#include "SilentDreamBase.h"

class SilentDream  : public SilentDreamBase
{
public:
    SilentDream();
    virtual ~SilentDream();

    int exec();

private:
    SilentDream(const SilentDream&);
    SilentDream& operator=(const SilentDream&);

private:
    int daemonize();
    int checkRunning(); 



};


#endif
