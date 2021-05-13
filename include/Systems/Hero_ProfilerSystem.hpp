#ifndef HERO_PROFILER_SYSTEM_HPP
#define HERO_PROFILER_SYSTEM_HPP

#include<fstream>

#include"Core/Hero_System.hpp"

#define MEMORYSTACK 1024

#define Profiler_Memory 1
#define Profiler_FPS 2

namespace Hero
{

class Profiler : public ISystem
{
private:
    static Profiler* instance;

    std::pair<uint32_t, size_t>* usedMemoryLog;
    uint32_t memoryLogged = 0;
    size_t usedMemory = 0;

    uint32_t frame = 0;

    uint32_t flags;

    void SaveMemoryLog();

public:
    Profiler(uint32_t _flags);
    ~Profiler();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    std::uint8_t priority(){ return 1; }

    static void AddMemory(int size);
};

}

#endif