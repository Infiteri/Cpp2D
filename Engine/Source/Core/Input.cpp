#include "Input.h"
#include <unordered_map>

namespace Core
{
    struct InputState
    {
        bool init;
        std::unordered_map<Keys, bool> keys;
        std::unordered_map<Buttons, bool> buttons;

        Vector2 mousePos;
        Vector2 deltaPos;
        Vector2 lastPos;
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
    
    Vector2 Input::GetMousePosition()
    {
        return state.mousePos;
    }
    
    Vector2 Input::GetMouseDelta()
    {
        return state.deltaPos;
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

    void InputUpdateMouse(int x, int y)
    {
        if (!state.init)
            return;

        state.deltaPos.Set(x - state.lastPos.x, y - state.lastPos.y);
        state.mousePos.Set(x, y);
        state.lastPos.Set(x, y);
    }
}