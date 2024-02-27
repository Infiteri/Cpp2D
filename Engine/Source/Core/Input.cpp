#include "Input.h"
#include <unordered_map>

namespace Core
{
    struct InputState
    {
        bool initialized;
        std::unordered_map<Keys, bool> keys;
        std::unordered_map<Buttons, bool> buttons;
    };

    static InputState state;

    void Input::Init()
    {
        if (state.initialized)
            return;

        state.initialized = true;
    }

    void Input::Shutdown()
    {
        if (!state.initialized)
            return;

        state.initialized = false;
    }

    bool Input::GetKey(Keys key)
    {
        return state.keys[key] != false;
    }

    bool Input::GetButton(Buttons button)
    {
        return state.buttons[button] != false;
    }

    void InputUpdateKey(Keys key, bool pressed)
    {
        state.keys[key] = pressed;
    }

    void InputUpdateButton(Buttons button, bool pressed)
    {
        state.buttons[button] = pressed;
    }
}