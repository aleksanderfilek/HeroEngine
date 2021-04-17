#ifndef HERO_CORE_H
#define HERO_CORE_H

#include<iostream>
#include<vector>
#include<cstdint>
#include<typeinfo>

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
            DEBUG_CODE( std::cout<<"[Core] - "<<newSystem->GetName()<<" already exists"<<std::endl; )
            return true;
        }
    }
    
    int index;
    for(index = 0; index < this->_systems.size(); index++)
    {
        if(newSystem->priority() <= this->_systems[index]->priority())
        {
            break;
        }
    }

    if(this->_running){
        ((ISystem*)newSystem)->Init();
    }

    this->_systems.insert(this->_systems.begin() + index, newSystem);

    DEBUG_CODE( std::cout<<"[Core] - "<<newSystem->GetName()<<" successfully added"<<std::endl; )

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
        DEBUG_CODE( std::cout<<"[Core] - "<<T::name<<" does not exist and could not be removed"<<std::endl; )
        return false;
    }
    
    ISystem*& system = this->_systems[index];

    if(system->_inited)
    {
        system->Close();
    }

    delete system;
    this->_systems.erase(this->_systems.begin() + index);

    DEBUG_CODE( std::cout<<"[Core] - "<<T::name<<" successfully removed"<<std::endl; )

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