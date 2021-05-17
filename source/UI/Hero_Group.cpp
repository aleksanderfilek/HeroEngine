#include"UI/Hero_Group.hpp"

namespace Hero
{

Group::Group()
{

}

Group::~Group()
{
    this->Clear();
}

void Group::SetAbsolutePosition(const int2& absolutePosition)
{
    this->_absolutPosition = absolutePosition + this->_relativePosition;
    for(UIElement* i : this->elements)
    {
        i->SetAbsolutePosition(this->_absolutPosition);
    }
}

void Group::Update()
{
    for(UIElement* i : this->elements)
    {
        i->Update();
    }
}

void Group::Draw()
{
    for(UIElement* i : this->elements)
    {
        i->Draw();
    }
}

unsigned int Group::Add(UIElement* element)
{
    element->SetAbsolutePosition(this->GetAbsolutePosition());
    this->elements.push_back(element);
    return this->elements.size()-1;
}

void Group::Remove(unsigned int index)
{
    delete this->elements[index];
    this->elements[index] = nullptr;
    this->elements.erase(this->elements.begin() + index);
}

void Group::Clear()
{
    for(UIElement* i : this->elements)
    {
        delete i;
        i = nullptr;
    }
    this->elements.clear();
}

}