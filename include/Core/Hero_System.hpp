#ifndef HERO_SYSTEM_H
#define HERO_SYSTEM_H

#include<cstdint>
#include<iostream>

#include"Hero_Utilities.hpp"

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

    virtual const char* GetName() = 0;

    virtual void Init()
    {   this->_inited = true;
        DEBUG_CODE( std::cout<<"["<<this->GetName()<<"] - Initializing"<<std::endl; ) 
    }

    virtual void Update(double  deltaTime) = 0;

    virtual void Close()
    { DEBUG_CODE( std::cout<<"["<<this->GetName()<<"] - Closing"<<std::endl; ) }
    
    virtual std::uint8_t priority(){ return 127; }
};

}

#endif