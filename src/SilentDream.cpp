#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <execinfo.h>
#include <assert.h>

#include <SilentDream/Log.h>
#include "SilentDream.h"
#include "ArgumentParser.h"
#include "Epoll.h"


SilentDream::SilentDream()
{

}

SilentDream::~SilentDream()
{

}

int SilentDream::exec()
{
    if (daemonize() < 0) {
        return -1;
    }

    if (checkRunning() != 0) {
        return -1;
    }

    LOGV("daemon ready to run...");
    for (;;) {

        sleep(1);
    }

}

//////////////////////////////////////////////
int SilentDream::daemonize()
{
    umask(0);
    
    int pid;
    if ((pid = fork()) < 0) {
        LOGE("fork:%s", strerror(errno));
        return -1;
    } else if (pid != 0) {
        exit(0);
    }

    setsid();
    if ((pid = fork()) < 0) {
        LOGE("fork:%s", strerror(errno));
        return -1;
    } else if (pid != 0) {
        exit(0);
    }

    if (chdir("/") < 0) {
        LOGE("chdir:%s", strerror(errno));
        return -1;
    }

    return 0;
}

int SilentDream::checkRunning()
{
    int fd;

    if ((fd = open("/var/run/silentdream.pid", O_RDWR|O_CREAT, 0644)) < 0) {
        LOGE("create pid file failed:%s", strerror(errno));
        return -1;
    }

    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    if (fcntl(fd, F_SETLK, &fl) < 0) {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            LOGW("already running!");
            return 1;
        }

        LOGE("lockfile failed:%s", strerror(errno));
        return -1;
    }

    ftruncate(fd, 0);

    char buf[16];
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf)+1);

    return 0;
}





