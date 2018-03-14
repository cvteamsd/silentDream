#include "SilentDreamWorker.h"

SilentDreamWorker::SilentDreamWorker(Loop *loop, Socket *socket)
 : mLoop(loop)
 , mSocket(socket)
{
}

SilentDreamWorker::~SilentDreamWorker()
{
    if (mSocket != nullptr) {
        delete mSocket;
        mSocket = nullptr;
    }
}

void SilentDreamWorker::onData(const void *buf, size_t len)
{
    LOGI("%s", (const char*)buf);

    mSocket->write(buf, len);

}

void SilentDreamWorker::onError(Socket::ErrorCode err)
{

}
