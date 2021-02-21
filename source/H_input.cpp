#include"H_input.hpp"

struct InputData
{
    int keyboard_state_number = 0;
    const uint8_t *current_keyboard_state = NULL;
    uint8_t *previous_keyboard_state = NULL;
    int32_t current_mouse_state, previous_mouse_state;
    int mouse_position_X = 0;
    int mouse_position_Y = 0;
};

InputData* inputData;


namespace Hero
{
namespace Input
{
    void Init()
    {
        inputData = new InputData();

        inputData->current_keyboard_state = SDL_GetKeyboardState(&inputData->keyboard_state_number);
        inputData->previous_keyboard_state = (uint8_t *)calloc(inputData->keyboard_state_number, sizeof(uint8_t));
    }

    void Delete()
    {
        delete inputData->previous_keyboard_state;

        delete inputData;
    }

    void Update()
    {
        //update mouse
        inputData->previous_mouse_state = inputData->current_mouse_state;
        inputData->current_mouse_state = SDL_GetMouseState(&inputData->mouse_position_X, &inputData->mouse_position_Y);
        //update keyboard
        SDL_memcpy(inputData->previous_keyboard_state, inputData->current_keyboard_state, inputData->keyboard_state_number * sizeof(uint8_t));
    }

    bool keyPressed(KeyCode key){
        return inputData->current_keyboard_state[key] && inputData->previous_keyboard_state[key];
    }

    bool keyDown(KeyCode key){
        return inputData->current_keyboard_state[key] && !inputData->previous_keyboard_state[key];
    }

    bool keyUp(KeyCode key){
        return !inputData->current_keyboard_state[key] && inputData->previous_keyboard_state[key];
    }

    bool mouseButtonPressed(Mouse button){
        return inputData->current_mouse_state&SDL_BUTTON(button) && inputData->previous_mouse_state&SDL_BUTTON(button);
    }

    bool mouseButtonDown(Mouse button){
        return inputData->current_mouse_state&SDL_BUTTON(button) && !inputData->previous_mouse_state&SDL_BUTTON(button);
    }

    bool mouseButtonUp(Mouse button){
        return !inputData->current_mouse_state&SDL_BUTTON(button) && inputData->previous_mouse_state&SDL_BUTTON(button);
    }

    void getMousePosition(int *x,int *y){
        if(x != NULL) *x = inputData->mouse_position_X;
        if(y != NULL) *y = inputData->mouse_position_Y;
    }

    void setMousePosition(int x, int y){
        //SDL_WarpMouseInWindow(Hero::Core::Get()->window, x, y);
        inputData->mouse_position_X = x;
        inputData->mouse_position_Y = y;
    }
}
}