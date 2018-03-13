#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(int argc, char **argv)
{
    this->argc = argc;
    this->argv = argv;
}

int ArgumentParser::initCheck()
{
    return 0;
}

int ArgumentParser::parse()
{
    return 0;
}

RunMode ArgumentParser::getRunMode() const
{
    if (argc > 1) {
        return RUN_MODE_CLIENT;
    } else {
        return RUN_MODE_DAEMON;
    }
}
