#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

enum RunMode {
    DAEMON,
    CLIENT,
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

#define DISALLOW_EVIL_CONSTRUCTORS(name) \
    name(const name &); \
    name &operator=(const name &)

#endif // GLOBAL_H
