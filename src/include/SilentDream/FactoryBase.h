#ifndef FACTORYBASE_H
#define FACTORYBASE_H

#include <string>
#include <map>
#include <algorithm>
#include <SilentDream/Global.h>
#include <SilentDream/Log.h>

template <typename Interface>
class FactoryBase
{
public:
    typedef typename Interface::Creator Creator;

    bool registerPlugin(std::string name, Creator c) {
//        LOGV("register plugin:%s", name.c_str());
        auto it = mCreators.insert({name, c});
        return it.second;
    }

    Interface* create(std::string name) {
        auto it = mCreators.find(name);
        if (it != mCreators.end()) {
            return it->second();
        }
        return nullptr;
    }

protected:
    FactoryBase() {}
    virtual ~FactoryBase() {}

private:
    std::map<std::string, Creator> mCreators;

    DISALLOW_EVIL_CONSTRUCTORS(FactoryBase);
};

#include "PluginManager.h"


#define DECLARE_FACTORY(Interface) class Interface##Factory

#define DEFINE_FACTORY(Interface) \
class Interface##Factory : public FactoryBase<Interface>, public Singleton<Interface##Factory> \
{ \
    using Singleton<Interface##Factory>::instance; \
    friend Singleton<Interface##Factory>; \
    friend class PluginBase<Interface, Interface##Factory>; \
                            \
    Interface##Factory() {  \
        void* pFactoryBase = static_cast<FactoryBase<Interface>*>(this); \
        PluginManager::instance()->registerFactory(Interface::interfaceName(), pFactoryBase); \
    }; \
    ~Interface##Factory() {} \
}

/////////////////////////////
struct PluginDesc {
    int (*init)();
    int version;
    void* handler;
};

#define PLUGIN_DEFINE(_init, _version) \
    struct PluginDesc silent_dream_plugin_desc = { \
    .init 		= _init,    \
    .version 	= _version, \
    }


#endif // FACTORYBASE_H
