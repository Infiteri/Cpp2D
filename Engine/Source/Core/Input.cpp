#include "Input.h"
#include "Logger.h"
#include "Engine.h"
#include "Math/Math.h"

#include <unordered_map>
#include <GLFW/glfw3.h>

namespace Core
{
    struct InputState
    {
        bool init;
        std::unordered_map<Keys, bool> keys;
        std::unordered_map<Buttons, bool> buttons;
        std::unordered_map<Keys, bool> justKeys;
        std::unordered_map<Keys, bool> lastKeys;

        Vector2 mousePos;
        Vector2 deltaPos;
        Vector2 lastPos;

        MouseMode lastMode;
        MouseMode mode;

        float lastScroll;
        float deltaScroll;
        bool negativeDelta = false;
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

    void Input::SetMouseMode(MouseMode mode)
    {
        if (state.mode == mode)
            return;
        state.mode = mode;
        if (state.lastMode != state.mode)
        {
            state.lastMode = state.mode;
            Window *window = Engine::GetWindow();
            if (!window)
                return;

            switch (state.mode)
            {
            case MouseMode::Visible:
                glfwSetInputMode(window->GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                break;

            case MouseMode::Hidden:
                glfwSetInputMode(window->GetHandle(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                break;

            case MouseMode::Locked:
                glfwSetInputMode(window->GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                break;

            default:
                break;
            }
        }
    }

    Vector2 Input::GetMousePosition()
    {
        return state.mousePos;
    }

    Vector2 Input::GetMouseDelta()
    {
        return state.deltaPos;
    }

    void Input::SetMousePosition(const Vector2 &vector)
    {
        Window *win = Engine::GetWindow();
        if (!win)
            return;

        glfwSetCursorPos(win->GetHandle(), vector.x, vector.y);
        state.mousePos = vector;
    }

    bool Input::GetKeyJustNow(Keys key)
    {
        if (!state.init)
            return false;

        return state.justKeys[key];
    }

    float Input::GetMouseWheelDelta()
    {
        return state.deltaScroll;
    }

    void Input::InternalUpdate()
    {
    }

    void InputUpdateKey(Keys key, bool pressed)
    {
        if (!state.init)
            return;

        state.lastKeys[key] = state.keys[key];
        state.keys[key] = pressed;
        state.justKeys[key] = (state.keys[key] && !state.lastKeys[key]);
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

    void InputUpdateScroll(int x, int y)
    {
        if (y == 0)
        {
            state.deltaScroll = 0;
            state.lastScroll = 0;
            return;
        }

        state.deltaScroll = 0;

        if (y < 0)
        {
            state.deltaScroll = y - Math::Positive(state.lastScroll);
            state.lastScroll = Math::Positive(y);
            state.negativeDelta = -1;
        }
        else
        {
            state.deltaScroll = y + Math::Positive(state.lastScroll);
            state.lastScroll = Math::Positive(y);
            state.negativeDelta = 1;
        }
    }
}