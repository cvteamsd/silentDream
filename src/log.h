#ifndef _LOG_H_
#define _LOG_H_

enum {
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERR,
};


int initLog();


#ifndef LOG_TAG
#define LOG_TAG ""
#endif

#define LOG(level, format, ...) \
    do { \
        char timebuf[30]; \
        getCurrentTime(timebuf); \
        doLog(level, "%s %s " format "\n", timebuf, LOG_TAG, ##__VA_ARGS__); \
    } while (0);


#define LOGV(format,...) LOG(LOG_LEVEL_VERBOSE, format, ##__VA_ARGS__)
#define LOGI(format,...) LOG(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOGW(format,...) LOG(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define LOGE(format,...) LOG(LOG_LEVEL_ERR, format, ##__VA_ARGS__)

void getCurrentTime(char *timebuf);
void doLog(int level, const char* format,...);


#endif
