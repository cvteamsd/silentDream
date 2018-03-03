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

class Poll;

using Callback = void(*)(Poll*, int, int);

class Loop
{
public:
    Loop() {
        mFd = epoll_create(1);
        mTimePoint = std::chrono::system_clock::now();
    }

    virtual ~Loop() {
        ::close(mFd);
    }

    virtual void run();

    int add(int fd, epoll_event *event) {
        return epoll_ctl(mFd, EPOLL_CTL_ADD, fd, event);
    }

    int del(int fd) {
        epoll_event e;
        return epoll_ctl(mFd, EPOLL_CTL_DEL, fd, &e);
    }

    int change(int fd, epoll_event *newEvent) {
        return epoll_ctl(mFd, EPOLL_CTL_MOD, fd, newEvent);
    }

    void setCb(int fd, Callback cb) {
        mCallbacks[fd] = cb;
    }

private:
    int mFd;
    std::chrono::system_clock::time_point mTimePoint;
    std::map<int,Callback> mCallbacks;
};

class Poll
{
public:
    Poll(Loop *loop, int fd)
        : mLoop(loop)
        , mFd(fd) {
    }

    void start(int events) {
        epoll_event event;
        event.events = events;
        event.data.ptr = this;
        mLoop->add(mFd, &event);
    }

    void stop() {
        mLoop->del(mFd);
    }

    void change(int events) {
        epoll_event event;
        event.events = events;
        event.data.ptr = this;
        mLoop->change(mFd, &event);
    }

    void setCb(Callback cb) {
        mLoop->setCb(mFd, cb);
    }

    void close(void(*cb)(Poll*)) {
        mFd = -1;
    }

    bool isClosed() {
        return mFd == -1;
    }

private:
    Loop *mLoop;
    int mFd;
};

#endif // EPOLL_H
