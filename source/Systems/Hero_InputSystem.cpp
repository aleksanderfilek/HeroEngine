#include"Systems/Hero_InputSystem.hpp"

#include<cstring>

namespace Hero
{

const char* Input::name = "Input System";


Input::Input()
{
    this->current_keyboard_state = SDL_GetKeyboardState(&this->keyboard_state_number);
    this->previous_keyboard_state = new std::uint8_t[this->keyboard_state_number];
    std::memset(this->previous_keyboard_state, 0, this->keyboard_state_number * sizeof(std::uint8_t));
}

Input::~Input()
{
    //delete this->current_keyboard_state;
    delete[] this->previous_keyboard_state;
}

void Input::Init()
{
    ISystem::Init();
}

void Input::Update()
{
    //update mouse
    this->previous_mouse_state = this->current_mouse_state;
    this->current_mouse_state = SDL_GetMouseState(&this->mouse_position_X, &this->mouse_position_Y);
    //update keyboard
    SDL_memcpy(this->previous_keyboard_state, this->current_keyboard_state, this->keyboard_state_number * sizeof(std::uint8_t));
}

void Input::Close()
{
    ISystem::Close();
}

bool Input::keyPressed(Input::KeyCode key){
    return current_keyboard_state[key] && previous_keyboard_state[key];
}

bool Input::keyDown(Input::KeyCode key){
    return current_keyboard_state[key] && !previous_keyboard_state[key];
}

bool Input::keyUp(Input::KeyCode key){
    return !current_keyboard_state[key] && previous_keyboard_state[key];
}

bool Input::mouseButtonPressed(Input::Mouse button){
    return current_mouse_state&SDL_BUTTON(button) && previous_mouse_state&SDL_BUTTON(button);
}

bool Input::mouseButtonDown(Input::Mouse button){
    return current_mouse_state&SDL_BUTTON(button) && !previous_mouse_state&SDL_BUTTON(button);
}

bool Input::mouseButtonUp(Input::Mouse button){
    return !current_mouse_state&SDL_BUTTON(button) && previous_mouse_state&SDL_BUTTON(button);
}

void Input::getMousePosition(int *x,int *y){
    if(x != NULL) *x = mouse_position_X;
    if(y != NULL) *y = mouse_position_Y;
}

void Input::setMousePosition(int x, int y){
    mouse_position_X = x;
    mouse_position_Y = y;
}

}