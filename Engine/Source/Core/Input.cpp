#include "Input.h"
#include <unordered_map>

namespace Core
{
    struct InputState
    {
        bool init;
        std::unordered_map<Keys, bool> keys;
        std::unordered_map<Buttons, bool> buttons;
    };

    static InputState state;

    void Input::Init()
    {
        if (state.init)
            return;

        state.init = true;
    }

    void Input::Shutdown()
    {
        if (!state.init)
            return;

        state.init = false;
    }

    bool Input::GetKey(Keys key)
    {
        if (!state.init)
            return false;

        return state.keys[key] != false;
    }

    bool Input::GetButton(Buttons button)
    {
        if (!state.init)
            return false;

        return state.buttons[button] != false;
    }

    void InputUpdateKey(Keys key, bool pressed)
    {
        if (!state.init)
            return;

        state.keys[key] = pressed;
    }

    void InputUpdateButton(Buttons button, bool pressed)
    {
        if (!state.init)
            return;

        state.buttons[button] = pressed;
    }
}