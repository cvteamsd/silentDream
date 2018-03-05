#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(int argc, char **argv)
{

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
//    return DAEMON;
    return CLIENT;
}
