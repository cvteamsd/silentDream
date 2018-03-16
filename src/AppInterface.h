#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include "PluginBase.h"
#include "FactoryBase.h"


DECLARE_FACTORY(App);

class AppInterface : public PluginBase<AppFactory, AppInterface>
{
public:
    virtual int start() = 0;
    virtual int stop() = 0;

protected:
    AppInterface() {}
    ~AppInterface() {}

private:
    DISALLOW_EVIL_CONSTRUCTORS(AppInterface);
};

DEFINE_FACTORY(App);



#endif // APPINTERFACE_H
