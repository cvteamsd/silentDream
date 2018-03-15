#ifndef _PLUGIN_BASE_H
#define _PLUGIN_BASE_H

#include <SilentDream/Global.h>

template <typename T, typename Interface>
class PluginBase
{
public:
    static bool registerPlugin(std::string name, Interface*(*creator)()) {
        return T::instance()->registerPlugin(name, creator);
    }

protected:
    PluginBase() {}
    virtual ~PluginBase() {}
};


#endif
