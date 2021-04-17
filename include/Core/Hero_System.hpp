#ifndef HERO_SYSTEM_H
#define HERO_SYSTEM_H

#include<cstdint>

namespace Hero
{
class Core;

class ISystem
{
friend class Core;

private:
    bool _inited = false;

public:
    ISystem(){}
    virtual ~ISystem(){};

    virtual void Init()
    {   this->_inited = true;
        DEBUG_CODE( std::cout<<"["<<this->GetName()<<"] - Initializing"<<std::endl; ) }

    virtual void Update(double  deltaTime) = 0;

    virtual void Close()
    { DEBUG_CODE( std::cout<<"["<<this->GetName()<<"] - Closing"<<std::endl; ) }

    virtual const char* GetName() = 0;
    static std::uint8_t priority(){ return 127; }
};

}

#endif