#include "log.h"
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

int gLogLevel = LOG_LEVEL_INFO;

int initLog()
{
    FILE* fp_log = freopen("/var/log/silentdream.log", "w", stdout);
    if (fp_log == NULL) {
        LOGE("open log file failed!\n");
        return -1;
    }

    return 0;
}

void getCurrentTime(char* timebuf)
{
    struct timeval tv;
    struct tm t;

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &t);
    sprintf(timebuf, "%04d-%02d-%02d %02d:%02d:%02d.%3lld", t.tm_year+1900, t.tm_mon+1, t.tm_mday,
            t.tm_hour, t.tm_min, t.tm_sec, tv.tv_usec/1000ll);
}

void doLog(int level, const char* format, ...)
{
    if (level < gLogLevel) {
        return;
    }

    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}
