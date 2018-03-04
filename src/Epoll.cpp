#include "Epoll.h"

void Loop::run()
{
    mTimePoint = std::chrono::system_clock::now();

    for (;;) {
        if (mNumPolls==0 && mTimers.size()==0) {
            break;
        }

        int numFdReady = epoll_wait(mFd, mReadyEvents, 1024, mDelay);
        mTimePoint = std::chrono::system_clock::now();

        for (int i = 0; i < numFdReady; ++i) {
            Poll* poll = (Poll*)mReadyEvents[i].data.ptr;
            int status = -bool(mReadyEvents[i].events & EPOLLERR);
            auto it = mCallbacks.find(poll->fd());
            if (it != mCallbacks.end()) {
                it->second(poll, status, mReadyEvents[i].events);
            } else {
                LOGE("no callback!");
            }
        }

        while (mTimers.size() && mTimers[0].timepoint < mTimePoint) {
            Timer* timer = mTimers[0].timer;
            mCancelledLastTimer = false;
            mTimers[0].cb(mTimers[0].timer);

            //timer stoped in callback function
            if (mCancelledLastTimer)
                continue;

            int repeat = mTimers[0].nextDelay;
            auto cb = mTimers[0].cb;
            mTimers.erase(mTimers.begin());
            if (repeat) {
                timer->start(cb, repeat, repeat);
            }
        }
    }
}
