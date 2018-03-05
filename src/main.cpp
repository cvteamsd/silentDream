#include <SilentDream/Global.h>
#include <SilentDream/Log.h>
#include "ArgumentParser.h"
#include "SilentDreamBase.h"
#include "SilentDream.h"
#include "SilentDreamClient.h"


int main(int argc, char **argv)
{
    ArgumentParser argParser(argc, argv);
    if (argParser.initCheck() < 0) {
        return -1;
    }

    RunMode runMode = argParser.getRunMode();
    Log::initLogMode(runMode);

    SilentDreamBase* s = nullptr;
    if (runMode == CLIENT) {
        s = new SilentDreamClient(argParser);
    } else {
        s = new SilentDream();
    }

    s->init();
    int ret = s->exec();
    s->destroy();

    delete s;

    return ret;
}
