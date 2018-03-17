#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <sstream>
#include <map>
#include <SilentDream/Global.h>
#include <SilentDream/Log.h>
#include <SilentDream/FactoryBase.h>
#include <SilentDream/PluginBase.h>

class PluginManager : public Singleton<PluginManager>
{
public:
    using Singleton<PluginManager>::instance;
    friend class Singleton<PluginManager>;

    void loadPlugins();

    bool registerFactory(std::string interfaceName, void* interfaceFactory) {
        auto it = mFactories.insert({interfaceName, interfaceFactory});
        return it.second;
    }

    template <typename T>
    T* create(std::string pluginName) {
        T* plugin = nullptr;

        std::stringstream ss( pluginName);
        std::string interfaceName;
        std::string name;
        std::getline(ss, interfaceName, '.');
        std::getline(ss, name);

        void* factory = findFactory(interfaceName);
        if (factory != nullptr) {
            FactoryBase<T>* factoryBase = static_cast<FactoryBase<T>*>(factory);
            plugin = factoryBase->create(pluginName);
        }
        return plugin;
    }

    void* findFactory(std::string interfaceName);

private:
    PluginManager() {}
    ~PluginManager() {}

    std::map<std::string, void*> mFactories;
};


#endif // PLUGINMANAGER_H
