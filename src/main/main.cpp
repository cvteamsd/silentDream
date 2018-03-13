#include <memory>
#include <SilentDream/Global.h>
#include <SilentDream/Log.h>
#include "../ArgumentParser.h"
#include "../SilentDreamBase.h"
#include "../SilentDream.h"
#include "../SilentDreamClient.h"


int main(int argc, char **argv)
{
    int ret;

    ret = initRootDir();
    if (ret < 0)
        return -1;

    ArgumentParser argParser(argc, argv);
    if (argParser.initCheck() < 0) {
        return -1;
    }

    RunMode runMode = argParser.getRunMode();
    if (runMode == RUN_MODE_DAEMON && isDaemonRunning()) {
        PRINT("already running, exit!");
        return -1;
    }

    Log::initLogMode(runMode);

    std::shared_ptr<SilentDreamBase> s;
    if (runMode == RUN_MODE_CLIENT) {
        s.reset(new SilentDreamClient(argParser));
    } else {
        s.reset(new SilentDream());
    }

    if (s->init() < 0) {
        LOGI("exit");
        return -1;
    }

    ret = s->exec();
    s->destroy();

    return ret;
}
