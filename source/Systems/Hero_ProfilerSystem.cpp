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
        this->heapMemoryBuffer = new uint64_t[BufferSize];
    }

    if(this->flags & Profiler_FPS)
    {
        this->fpsBuffer = new uint16_t[BufferSize];
    }

    AddMemory(0);
}

void Profiler::Update()
{
    if(this->flags & Profiler_Memory)
    {
        this->heapMemoryBuffer[this->bufferCount] = this->heapMemoryUsage;
    }

    if(this->flags & Profiler_FPS)
    {
        double fps = 1.0 / Time::GetDeltaTime();
        this->fpsBuffer[this->bufferCount] = (uint16_t)fps;
    }

    this->bufferCount++;

    if(this->bufferCount == BufferSize)
    {
        this->SaveBuffer();
    }

    this->frame++;
}

void Profiler::Close()
{
    ISystem::Close();

    SaveLog();

    if(this->flags & Profiler_Memory)
    {
        delete[] this->heapMemoryBuffer;
    }

    if(this->flags & Profiler_FPS)
    {
        delete[] this->fpsBuffer;
    }
}

void Profiler::AddMemory(int size)
{
    instance->heapMemoryUsage += size;
}

void Profiler::SaveBuffer()
{
    std::string name = std::to_string(this->buffersNumber) + "profiler.temp";

    std::ofstream file;
    file.open(name, std::ios::out | std::ios::binary);
    if(!file.is_open())
    {
        std::cout<<"["<<Profiler::name<<"] - Could not create buffer file: "<<name<<std::endl;
        return;
    }

    if(this->flags & Profiler_Memory)
    {
        file.write((const char*)this->heapMemoryBuffer, BufferSize * sizeof(uint32_t));
    }

    if(this->flags & Profiler_FPS)
    {
        file.write((const char*)this->fpsBuffer, BufferSize * sizeof(uint16_t));
    }

    file.close();

    this->buffersNumber++;
    this->bufferCount = 0;
}

void Profiler::SaveLog(){
    std::ofstream file;
    file.open("profiler.csv");

    if(file.fail())
    {
        std::cout<<"["<<Profiler::name<<"] - Could not create profiler file"<<std::endl;
        return;
    }

    file<<"frame";
    if(this->flags & Profiler_Memory)
        file<<", memory";
    if(this->flags & Profiler_FPS)
        file<<", fps";
    file<<std::endl;

    uint32_t tempHeapMemoryBuffer[BufferSize];
    uint16_t tempfpsBuffer[BufferSize];

    uint32_t frameCounter = 0;

    for(int i = 0; i < this->buffersNumber; i++)
    {
        std::string name = std::to_string(i) + "profiler.temp";
        std::ifstream tempFile;
        tempFile.open(name, std::ios::in | std::ios::binary);
        if(this->flags & Profiler_Memory)
            tempFile.read((char*)tempHeapMemoryBuffer, BufferSize * sizeof(uint32_t));
        if(this->flags & Profiler_FPS)
            tempFile.read((char*)tempfpsBuffer, BufferSize * sizeof(uint16_t));
        tempFile.close();

        for(int j = 0; j < BufferSize; j++)
        {
            file<<frameCounter;
            frameCounter++;
            if(this->flags & Profiler_Memory)
                file<<", "<<tempHeapMemoryBuffer[j];
            if(this->flags & Profiler_FPS)
                file<<", "<<tempfpsBuffer[j];
            file<<std::endl;
        }
    }

    for(int i = 0; i < this->bufferCount; i++)
    {
        file<<frameCounter;
        frameCounter++;
        if(this->flags & Profiler_Memory)
            file<<", "<<heapMemoryBuffer[i];
        if(this->flags & Profiler_FPS)
            file<<", "<<fpsBuffer[i];
        file<<std::endl;
    }

    file.close();
    
    this->buffersNumber++;
    this->bufferCount = 0;
}

}
