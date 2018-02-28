#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "log.h"


int main(int argc, char **argv)
{
    initLog();

    LOGI("starting silentdream main process...");
    LOGV("hello 123")

    int ret = fork();
    if (ret < 0) {
        LOGE("fork:%s", strerror(errno));
    } else if (ret == 0) {
        sleep(3);
        LOGI("I'am here!");
        for (;;) {
            sleep(1);
        }
        LOGI("exit!");
    } else {
        _exit(0);
    }

    return 0;
}
