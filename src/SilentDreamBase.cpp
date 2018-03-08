#include "SilentDreamBase.h"
#include "Epoll.h"

SilentDreamBase::SilentDreamBase()
    : mLoop(new Loop)
{

}

SilentDreamBase::~SilentDreamBase()
{
    if (mLoop != nullptr) {
        delete mLoop;
        mLoop = nullptr;
    }
}

int SilentDreamBase::init()
{
    SignalHandler::instace().install(mLoop);

    return 0;
}

int SilentDreamBase::destroy()
{
    return 0;
}
