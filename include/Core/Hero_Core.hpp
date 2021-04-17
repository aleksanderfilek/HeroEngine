#ifndef HERO_CORE_H
#define HERO_CORE_H

#include<iostream>
#include<vector>
#include<typeinfo>
#include<cstdint>

#include"Hero_Config.hpp"
#include"Hero_Utilities.hpp"
#include"Hero_System.hpp"

namespace Hero
{

class Core
{
private:
    std::vector<ISystem*> _systems;
    bool _running = false;

public:
    Core();
    ~Core();

    void Start();
    void Close();

template<class T> 
bool AddSystem(T* newSystem)
{
    for(ISystem* sys: this->_systems)
    {
        if(typeid(*newSystem) == typeid(*sys))
        {
            DEBUG_CODE( std::cout<<"[Core] - "<<((ISystem*)newSystem)->name()<<" already exists"<<std::endl; )
            return true;
        }
    }

    DEBUG_CODE( std::cout<<"[Core] - "<<((ISystem*)newSystem)->name()<<" successfully added"<<std::endl; )
    
    if(this->_running){
        ((ISystem*)newSystem)->Init();
    }

    this->_systems.push_back(newSystem);

    return true;
}

template<class T> 
bool RemoveSystem()
{
    int index; 
    for(index = 0; index < this->_systems.size(); index++)
    {
        if(typeid(T) == typeid(*this->_systems[index]))
        {
            break;
        }
    }

    if(index == this->_systems.size())
    {
        DEBUG_CODE( std::cout<<"[Core] - System "<<typeid(T).name()<<" does not exist and could not be deleted"<<std::endl; )
        return false;
    }
    
    DEBUG_CODE( std::cout<<"[Core] - System "<<typeid(T).name()<<" successfully removed"<<std::endl; )

    this->_systems[index]->Close();
    this->_systems.erase(this->_systems.begin() + index);

    return true;
}

template<class T>
T* GetSystem()
{
    for(ISystem* sys: this->_systems)
    {
        if(typeid(T) == typeid(*sys))
        {
            return static_cast<T*>(sys);
        }
    }

    return nullptr;
}
};

}

#endif