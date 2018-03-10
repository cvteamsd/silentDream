#include <memory>
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

    std::shared_ptr<SilentDreamBase> s;
    if (runMode == CLIENT) {
        s.reset(new SilentDreamClient(argParser));
    } else {
        s.reset(new SilentDream());
    }

    int ret;

    s->init();
    ret = s->exec();
    s->destroy();

    return ret;
}
