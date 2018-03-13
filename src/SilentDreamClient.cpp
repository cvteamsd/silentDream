#include "SilentDreamClient.h"
#include "Epoll.h"
#include "Socket.h"

SilentDreamClient::SilentDreamClient(ArgumentParser &argParser)
        : mArgParser(argParser)
{

}

SilentDreamClient::~SilentDreamClient()
{

}

int SilentDreamClient::init()
{
    SilentDreamBase::init();

    mSocket = new Socket(mLoop);
    if (mSocket->initAddress("localhost") < 0) {
        return -1;
    }

    if (mSocket->createSocket() < 0) {
        return -1;
    }

    if (mSocket->connect() < 0) {
        return -1;
    }

    return 0;
}

int SilentDreamClient::exec()
{
    std::shared_ptr<Timer> timer(new Timer(mLoop, this));
    timer->start([](Timer* timer) {
        static int count = 0;

        ++count;
        LOGI("hello count: %d", count);
        if (count == 10) {
            timer->loop()->requestExit();
        }
    }, 1000, 1000);

    mLoop->run();

    return 0;
}

int SilentDreamClient::destroy()
{
    return 0;
}
