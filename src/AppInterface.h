#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include "PluginBase.h"
#include "FactoryBase.h"

class AppFactory;
class AppInterface : public PluginBase<AppFactory, AppInterface>
{
public:
    virtual int start() = 0;
    virtual int stop() = 0;

protected:
    AppInterface() {}
    ~AppInterface() {}
};

class AppFactory : public FactoryBase<AppInterface>, public Singleton<AppFactory>
{

};



#endif // APPINTERFACE_H
