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
#include <iostream>
#include <sstream>
#include <string>

#include "Util.h"

enum RunMode {
    RUN_MODE_DAEMON,
    RUN_MODE_CLIENT,
};

#ifndef MAX_PATH
#define MAX_PATH  260
#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

#define DISALLOW_EVIL_CONSTRUCTORS(name) \
    name(const name &); \
    name &operator=(const name &)

#endif // GLOBAL_H
