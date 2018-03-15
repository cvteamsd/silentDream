#ifndef HELLOAPP_H
#define HELLOAPP_H

#include "AppInterface.h"

class HelloApp : public AppInterface
{
public:
    int start();
    int stop();
    static std::string name() {
        return "app.hello";
    }

    static AppInterface* creator() {
        LOGI("new HelloApp");
        return new HelloApp();
    }

private:
    HelloApp();
    ~HelloApp();
};

#endif // HELLOAPP_H
