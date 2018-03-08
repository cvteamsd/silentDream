#include "SilentDreamClient.h"
#include "Epoll.h"

SilentDreamClient::SilentDreamClient(ArgumentParser &argParser)
        : mArgParser(argParser)
{

}

SilentDreamClient::~SilentDreamClient()
{

}

int SilentDreamClient::exec()
{
    Timer* timer = new Timer(mLoop, this);

    timer->start([](Timer* timer) {
        static int count = 0;

        ++count;
        LOGI("hello count: %d", count);
        if (count == 10) {
            timer->stop();
            timer->loop()->requestExit();
//            *((int*)10) = 1;
        }
    }, 1000, 1000);

    mLoop->run();

    return 0;
}
