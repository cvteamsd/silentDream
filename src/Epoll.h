#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <mutex>
#include <functional>

#include <SilentDream/Log.h>

class Timer;
class Poll;
class Async;

using Callback = void(*)(Poll*, int, int);

struct Timepoint {
    std::function<void(Timer *)> cb;
    Timer *timer;
    std::chrono::system_clock::time_point timepoint;
    int nextDelay;
};

class Loop
{
public:
    Loop();
    virtual ~Loop();

    virtual void run();

    void addTimer(Timepoint t) {
        mTimers.insert(
            std::upper_bound(mTimers.begin(), mTimers.end(), t, [](const Timepoint&a, const Timepoint&b) {
                return a.timepoint < b.timepoint;
            }),
            t
        );

        updateNextDelay();
    }

    void removeTimer(Timer* timer) {
        auto pos = mTimers.begin();
        for (Timepoint &t : mTimers) {
            if (t.timer == timer) {
                mTimers.erase(pos);
                break;
            }
            ++pos;
        }

        mCancelledLastTimer = true;
        updateNextDelay();
    }

    std::chrono::system_clock::time_point now() {
        return mTimePoint = std::chrono::system_clock::now();
    }

    int add(int fd, epoll_event *event) {
        ++mNumPolls;
        return epoll_ctl(mFd, EPOLL_CTL_ADD, fd, event);
    }

    int remove(int fd) {
        epoll_event e;

        --mNumPolls;
        return epoll_ctl(mFd, EPOLL_CTL_DEL, fd, &e);
    }

    int change(int fd, epoll_event *newEvent) {
        return epoll_ctl(mFd, EPOLL_CTL_MOD, fd, newEvent);
    }

    void setCb(int fd, Callback cb) {
        mCallbacks[fd] = cb;
    }

    void sendRequest(std::function<bool(void*)> cb, void *data);



private:
    void updateNextDelay() {
        mDelay = -1;
        if (mTimers.size()) {
            mDelay = std::max<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                       mTimers[0].timepoint - mTimePoint).count(), -1);
        }
    }

private:
    int mFd = -1;
    epoll_event mReadyEvents[1024];
    std::chrono::system_clock::time_point mTimePoint;
    int mDelay = -1;
    std::vector<Timepoint> mTimers;
    bool mCancelledLastTimer = false;

    int mNumPolls = 0;
    std::map<int,Callback> mCallbacks;

    std::recursive_mutex mRequestLock;
    std::list<std::pair<std::function<bool(void*)>,void*>> mRequests;
    Async* mHandler;
};

class Timer {
public:
    Timer(Loop* loop)
        : mLoop(loop) {
    }

    virtual ~Timer() {
    }

    void start(std::function<void(Timer*)> cb, int timeout, int repeat = 0) {
        std::chrono::system_clock::time_point timepoint = mLoop->now() +
                std::chrono::milliseconds(timeout);
        Timepoint t = {cb, this, timepoint, repeat};
        mLoop->addTimer(t);
    }

    //stop() doesn't delete Timer object, we should do it ourself
    void stop() {
        mLoop->removeTimer(this);
    }

private:
    Loop* mLoop;
};


class Poll
{
public:
    Poll(Loop *loop, int fd)
        : mLoop(loop)
        , mFd(fd) {
    }

    //caller should close fd himself
    virtual ~Poll() {
        if (mTimer) {
            cancelTimeout();
        }
    }

    virtual void start(int events) {
        epoll_event event;
        event.events = events;
        event.data.ptr = this;
        mLoop->add(mFd, &event);
    }

    virtual void stop() {
        mLoop->remove(mFd);
    }

    virtual void change(int events) {
        epoll_event event;
        event.events = events;
        event.data.ptr = this;
        mLoop->change(mFd, &event);
    }

    virtual void setCb(Callback cb) {
        mLoop->setCb(mFd, cb);
    }

    virtual void startTimeout(void (*cb)(Timer*), int timeout) {
       mTimer = new Timer(mLoop);
       mTimer->start(cb, timeout);
    }

    virtual void cancelTimeout() {
        mTimer->stop();
        delete mTimer;
        mTimer = nullptr;
    }

    int fd() const {
        return mFd;
    }

protected:
    Loop *mLoop;
    int mFd = -1;
    Timer* mTimer = nullptr;
};

class Async : public Poll {
public:
    Async(Loop* loop)
        : Poll(loop, ::eventfd(0, EFD_CLOEXEC)) {
    }

    ~Async() {
        ::close(mFd);
    }

    void start(std::function<void(Async*)> cb) {
        this->cb = cb;
        Poll::setCb([](Poll* p, int, int) {
            uint64_t val;
            if (::read(p->fd(), &val, 8) == 8) {
               ((Async*)p)->cb((Async*)p);
            }
        });
        Poll::start(EPOLLIN);
    }

    void notify() {
        int64_t one = 1;
        if (::write(mFd, &one, 8) != 8) {
            return;
        }
    }

    void setData(void *data) {
        mData = data;
    }

    void* getData() const {
        return mData;
    }

private:
    std::function<void(Async*)> cb;
    void* mData;
};


#endif // EPOLL_H
