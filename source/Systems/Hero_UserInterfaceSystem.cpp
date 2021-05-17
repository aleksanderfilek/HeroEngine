#include"Systems/Hero_UserInterfaceSystem.hpp"

namespace Hero
{

const char* UserInterface::name = "UserInterface System"; 

UserInterface::UserInterface()
{

}

UserInterface::~UserInterface()
{

}

void UserInterface::Init()
{
    ISystem::Init();
}

void UserInterface::Update()
{

}

void UserInterface::Close()
{
    ISystem::Close();
}

}