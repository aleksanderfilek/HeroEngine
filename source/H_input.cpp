#include"H_input.hpp"

namespace Hero
{
InputSystem* InputSystem::instance = nullptr;

InputSystem::InputSystem()
{
    instance = this;

    this->current_keyboard_state = SDL_GetKeyboardState(&this->keyboard_state_number);
    this->previous_keyboard_state = new uint8_t[this->keyboard_state_number];
}

InputSystem::~InputSystem()
{
    delete this->previous_keyboard_state;
}

void InputSystem::Update()
{
    //update mouse
    this->previous_mouse_state = this->current_mouse_state;
    this->current_mouse_state = SDL_GetMouseState(&this->mouse_position_X, &this->mouse_position_Y);
    //update keyboard
    SDL_memcpy(this->previous_keyboard_state, this->current_keyboard_state, this->keyboard_state_number * sizeof(uint8_t));
}
    

bool InputSystem::keyPressed(Input::KeyCode key){
    return instance->current_keyboard_state[key] && instance->previous_keyboard_state[key];
}

bool InputSystem::keyDown(Input::KeyCode key){
    return instance->current_keyboard_state[key] && !instance->previous_keyboard_state[key];
}

bool InputSystem::keyUp(Input::KeyCode key){
    return !instance->current_keyboard_state[key] && instance->previous_keyboard_state[key];
}

bool InputSystem::mouseButtonPressed(Input::Mouse button){
    return instance->current_mouse_state&SDL_BUTTON(button) && instance->previous_mouse_state&SDL_BUTTON(button);
}

bool InputSystem::mouseButtonDown(Input::Mouse button){
    return instance->current_mouse_state&SDL_BUTTON(button) && !instance->previous_mouse_state&SDL_BUTTON(button);
}

bool InputSystem::mouseButtonUp(Input::Mouse button){
    return !instance->current_mouse_state&SDL_BUTTON(button) && instance->previous_mouse_state&SDL_BUTTON(button);
}

void InputSystem::getMousePosition(int *x,int *y){
    if(x != NULL) *x = instance->mouse_position_X;
    if(y != NULL) *y = instance->mouse_position_Y;
}

void InputSystem::setMousePosition(int x, int y){
    instance->mouse_position_X = x;
    instance->mouse_position_Y = y;
}

}