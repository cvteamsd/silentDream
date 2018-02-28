#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static int init_log()
{
    int log_fd = open("/var/log/silentdream.log", O_CREAT|O_TRUNC, 0644);
    if (log_fd < 0) {
        fprintf(stderr, "open log file failed!\n");
        return -1;
    } 

    int ret = dup2(log_fd, 2);
    if (ret < 0) {
        fprintf(stderr, "dup2:%s\n", strerror(errno));
        return -1;
    }
    close(log_fd);
    stderr = fdopen(ret, "w");    

    return 0;
}

int main(int argc, char **argv)
{
    init_log();

    fprintf(stderr, "starting silentdream main process...\n");
    fflush(stderr);

    return 0;
}
