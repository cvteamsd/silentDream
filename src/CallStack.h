#ifndef CALLSTACK_H
#define CALLSTACK_H

#include <cxxabi.h>
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <sys/mman.h>
#include <string>
#include <deque>

class CallStack
{
public:
    CallStack();

private:
   void unwind();

    struct MapEntry {
        uintptr_t start;
        uintptr_t end;
        int flags;
        std::string name;
    };

    void buildMap();
    bool ParseLine(const char* line, MapEntry *entry);
    const MapEntry* findMapEntry(uintptr_t addr) const;


    std::deque<MapEntry> mMaps;
};

#endif // CALLSTACK_H
