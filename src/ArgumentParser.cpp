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
        return CLIENT;
    } else {
        return DAEMON;
    }
}
