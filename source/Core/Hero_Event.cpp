#include"Core/Hero_Event.hpp"

namespace Hero
{

EventHandler::EventHandler()
{
    this->functions = nullptr;
    this->count = 0;
}

EventHandler::~EventHandler()
{
    this->Clear();
}

void EventHandler::Add(EventFunction function)
{
    this->count++;
    this->functions = (EventFunction*)std::realloc(this->functions, this->count * sizeof(EventFunction*));
    this->functions[this->count-1] = function;
}

void EventHandler::Clear()
{
    delete[] this->functions;
    this->functions = nullptr;
    this->count = 0;
}

void EventHandler::Invoke(void* object, void *args, int argc)
{
    for(int i = 0; i < this->count; i++)
    {
        this->functions[i](object, args, argc);
    }
}

}