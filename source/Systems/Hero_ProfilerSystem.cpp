#include"Systems/Hero_ProfilerSystem.hpp"

namespace Hero
{

void ProfilerAddMemory(int size)
{
    Profiler::AddMemory(size);
}

const char* Profiler::name = "Profiler System";
Profiler* Profiler::instance = nullptr;

Profiler::Profiler(uint32_t _flags) : flags(_flags)
{
    Profiler::instance = this;
}

Profiler::~Profiler()
{

}

void Profiler::Init()
{
    ISystem::Init();

    if(this->flags & Profiler_Memory)
    {
        this->usedMemoryLog = new std::pair<uint32_t, size_t>[MEMORYSTACK];
    }

    AddMemory(0);
}

void Profiler::Update()
{
    if(this->flags & Profiler_Memory && this->memoryLogged == MEMORYSTACK)
    {
        SaveMemoryLog();
    }

    this->frame++;
}

void Profiler::Close()
{
    ISystem::Close();

    if(this->flags & Profiler_Memory)
    {
        SaveMemoryLog();

        delete[] this->usedMemoryLog;
    }
}

void Profiler::AddMemory(int size)
{
    if(instance->flags & Profiler_Memory == 0)
        return;

    instance->usedMemory += size;
    if(instance->memoryLogged > 0 && 
        instance->usedMemoryLog[instance->memoryLogged - 1].first == instance->frame)
    {
        instance->usedMemoryLog[instance->memoryLogged - 1].second = instance->usedMemory;
        return;
    }

    instance->usedMemoryLog[instance->memoryLogged].first = instance->frame;
    instance->usedMemoryLog[instance->memoryLogged].second = instance->usedMemory;
    instance->memoryLogged++;
}

void Profiler::SaveMemoryLog(){
    std::ofstream file;
    file.open("memoryLog.csv");

    if(file.fail())
    {
        std::cout<<"["<<Profiler::name<<"] - Could not create memory log file"<<std::endl;
        return;
    }

    for(int i = 0; i < this->memoryLogged; i++)
    {
        file<<this->usedMemoryLog[i].first<<", "<<usedMemoryLog[i].second<<std::endl;
    }

    file.close();

    this->memoryLogged = 0;
}

}
