#ifndef HERO_PROFILER_SYSTEM_HPP
#define HERO_PROFILER_SYSTEM_HPP

#include<fstream>
#include<string>

#include"Core/Hero_System.hpp"
#include"Core/Hero_Time.hpp"

#define BufferSize 1024

#define Profiler_Memory 1
#define Profiler_FPS 2

namespace Hero
{

class Profiler : public ISystem
{
private:
    static Profiler* instance;

    uint32_t flags;
    uint32_t frame = 0;
    uint32_t buffersNumber = 0;
    uint32_t bufferCount = 0;

    size_t heapMemoryUsage = 0;
    uint64_t* heapMemoryBuffer;

    double* fpsBuffer;

    void SaveBuffer();
    void SaveLog();

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