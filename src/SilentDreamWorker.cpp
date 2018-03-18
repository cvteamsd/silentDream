#include <SilentDream/PluginManager.h>
#include <SilentDream/App.h>
#include "SilentDreamWorker.h"

SilentDreamWorker::SilentDreamWorker(Loop *loop, Socket *socket)
 : mLoop(loop)
 , mSocket(socket)
{
}

SilentDreamWorker::~SilentDreamWorker()
{
    if (mSocket != nullptr) {
        delete mSocket;
        mSocket = nullptr;
    }
}

void SilentDreamWorker::onData(const void *buf, size_t len)
{
    LOGI("recv len:%d %s", len, (const char*)buf);

    std::string bufString((const char*)buf);
    json request = json::parse(bufString);
    json response;
    handleRequest(request, response);

    if (!response.empty()) {
        std::string result = response.dump();
        mSocket->write(result.c_str(), result.size());
    }
}

void SilentDreamWorker::onError(Socket::ErrorCode err)
{
//    LOGE("onError:%#x", err);

}

////////////////////////////////////////////////////
int SilentDreamWorker::handleRequest(const json& request, json& response)
{
    std::string what = request.at("what").get<std::string>();
    CMD cmd = request.at("cmd").get<CMD>();
    int argNum = request.at("arg-num").get<int>();
    std::string argBaseName = "arg-";
    std::string argName;
    std::string argValue;
    std::map<std::string, std::string> args;
    for (size_t i = 0; i < argNum; ++i) {
        argName = argBaseName + std::to_string(i+1);
        argValue = request.at(argName).get<std::string>();
        args.emplace(argName, argValue);
    }

    json result;
    result["what"] = what;

    auto pluginManager = PluginManager::instance();
    static App* app;

    switch (cmd) {
    case VERSION: {
        result["version"] = "0.1";
    }
    break;

    case HELP: {
        std::vector<std::string> helps = {
            "version",
            "help",
            "ls",
            "status",
            "start",
            "stop",
        };

        result["commands"] = helps;
    }
    break;

    case LS: {
        auto interfaces = pluginManager->interfaces();
        result["interface total"] = interfaces.size();
        result["interface"] = interfaces;
    }
    break;

    case STATUS: {

    }
    break;

    case START: {
        app = pluginManager->create<App>(args["arg-1"]);
        if (app) {
            int ret = app->start();
            result["status"] = ret==0?"success":"failure";
        } else {
            result["status"] = "failure";
        }
    }
    break;

    case STOP: {
        if (app != nullptr) {
            int ret = app->stop();
            result["status"] = ret==0?"success":"failure";

            delete app;
            app = nullptr;
        } else {
            result["status"] = "failure";
        }
    }
    break;

    default:
        break;
    }

    response = std::move(result);

    return 0;
}








