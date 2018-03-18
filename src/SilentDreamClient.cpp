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

    if (mArgParser.parse(mArgs) < 0) {
        return -1;
    }

    if (connectServer() < 0) {
        return -1;
    }

    return 0;
}

int SilentDreamClient::destroy()
{
    return 0;
}

//////////////////////////////////////////////////
int SilentDreamClient::connectServer()
{
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

void SilentDreamClient::onConnected()
{
    if (!mArgs.empty()) {
        std::string data = std::move(mArgs.dump());
        mSocket->write(data.c_str(), strlen(data.c_str())+1);
    }
}

void SilentDreamClient::onData(const void *buf, size_t len)
{
    PRINT("Server response:\n\t%s", (const char*)buf);
    mLoop->requestExit();

}

void SilentDreamClient::onError(Socket::ErrorCode err)
{
//    LOGE("onError:%#x", err);
    mLoop->requestExit();
}








