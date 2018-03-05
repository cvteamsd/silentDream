#ifndef _ARGUMENT_PARSER_H
#define _ARGUMENT_PARSER_H

#include <SilentDream/Global.h>

class ArgumentParser {
public:
    ArgumentParser(int argc, char **argv);
    int initCheck();

    RunMode getRunMode() const;


private:
    int parse();

};



#endif
