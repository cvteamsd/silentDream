#ifndef FACTORYBASE_H
#define FACTORYBASE_H

#include <string>
#include <map>
#include <algorithm>
#include <SilentDream/Global.h>

template <typename InterfaceFactory, typename Interface>
class FactoryBase : public Singleton<InterfaceFactory>
{
public:
    FactoryBase() {}
    typedef Interface* (*Creator)();

    bool registerPlugin(std::string name, Creator c) {
        LOGI("register name:%s", name.c_str());
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

private:
    std::map<std::string, Creator> mCreators;
};

#define DECLARE_FACTORY(Type) class Type##Factory

#define DEFINE_FACTORY(Type) \
class Type##Factory : public FactoryBase<Type##Factory, Type##Interface> \
{}

#endif // FACTORYBASE_H
