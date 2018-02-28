#ifndef _LOG_H_
#define _LOG_H_

#define LOG(format, ...) \
    do {
        fprintf(stderr, format, ##__VA_ARGS__);
    } while (0);

#endif
