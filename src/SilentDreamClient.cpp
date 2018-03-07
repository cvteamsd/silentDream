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
//    sleep(1);
    kill(getpid(), SIGINT);
    usleep(10000);

    Timer* timer = new Timer(mLoop);
    int count = 0;
    bool quit = false;
    timer->start([&count, &quit](Timer* timer) {
        ++count;
        LOGI("hello count: %d", count);
        if (count == 10) {
           quit = true;
            timer->stop();
        *((int*)10) = 1;
        }
    }, 1000, 1000);

    for (;;) {
        mLoop->run();
        if (quit)
            break;

        usleep(1000);
    }

    return 0;

}
