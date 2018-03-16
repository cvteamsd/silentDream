#ifndef _PLUGIN_BASE_H
#define _PLUGIN_BASE_H

#include <SilentDream/Global.h>

template <typename Factory, typename Interface>
class PluginBase
{
public:
    static bool registerPlugin(std::string name, Interface*(*creator)()) {
        return Factory::instance()->registerPlugin(name, creator);
    }

protected:
    PluginBase() {}
    virtual ~PluginBase() {}

private:
    DISALLOW_EVIL_CONSTRUCTORS(PluginBase);
};

static std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); }
                  );
    return s;
}

#define PLUGIN_META(Type, Name) \
static std::string name() {  \
    std::string s = #Type "." #Name;  \
    return str_tolower(s);            \
}							 \
                             \
static Type##Interface* creator() { \
    return new Name##Type(); 		\
}


#endif
