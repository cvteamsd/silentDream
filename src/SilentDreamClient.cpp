#include "SilentDreamClient.h"
#include "Epoll.h"
#include "Socket.h"

SilentDreamClient::SilentDreamClient(ArgumentParser &argParser)
        : mArgParser(argParser)
{

}

SilentDreamClient::~SilentDreamClient()
{
    if (mSocket != nullptr) {
        delete mSocket;
        mSocket = nullptr;
    }
}

int SilentDreamClient::init()
{
    SilentDreamBase::init();

    mSocket = new Socket(mLoop);
    mSocket->setClientHandler(this);
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

int SilentDreamClient::destroy()
{
    return 0;
}


//////////////////////////////////////////////////
void SilentDreamClient::onConnected()
{
//    char data[] = "hello";
    const char *data = "hello";

    mSocket->write(data, 5);

}

void SilentDreamClient::onData(const void *buf, size_t len)
{
    LOGI("client received:%s", (const char*)buf);

    mLoop->requestExit();
}

void SilentDreamClient::onError(Socket::ErrorCode err)
{

}








