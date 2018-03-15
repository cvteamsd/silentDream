#ifndef FACTORYBASE_H
#define FACTORYBASE_H

#include <string>
#include <map>
#include <algorithm>

template <typename T>
class FactoryBase
{
public:
    FactoryBase() {}
    typedef T* (*Creator)();

    bool registerPlugin(std::string name, Creator c) {
        LOGI("register name:%s", name.c_str());
        auto it = mCreators.insert({name, c});
        return it.second;
    }

    T* create(std::string name) {
        auto it = mCreators.find(name);
        if (it != mCreators.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::map<std::string, Creator> mCreators;
};

#endif // FACTORYBASE_H
