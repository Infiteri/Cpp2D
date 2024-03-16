#include "Window.h"
#include "Renderer/Renderer.h"
#include "Input.h"

#include <GLFW/glfw3.h>

namespace Core
{
    double accumulatedScrollX = 0.0;
    double accumulatedScrollY = 0.0;

    static void WindowOnResize(GLFWwindow *w, int x, int y)
    {
        Renderer::Viewport(x, y);
    };

    static void WindowOnScroll(GLFWwindow *w, double x, double y)
    {

        accumulatedScrollX += x;
        accumulatedScrollY += y;
    };

    Window::Window(const Configuration &config)
    {
        state = config;

        // Setup glfw.
        glfwInit();
        glfwWindowHint(GLFW_VISIBLE, false);

        GLFWmonitor *monitor = NULL;
        if (config.Mode == Fullscreen)
        {
            monitor = glfwGetPrimaryMonitor();
            //! UPDATE SIZES
            state.Width = glfwGetVideoMode(monitor)->width;
            state.Height = glfwGetVideoMode(monitor)->height;
        }

        handle = glfwCreateWindow(state.Width, state.Height, state.Title, monitor, NULL);
        glfwMakeContextCurrent(handle);
        glfwShowWindow(handle);
        glfwSetWindowPos(handle, state.X, state.Y);
        glfwSetScrollCallback(handle, WindowOnScroll);

        if (config.Mode == Windowed)
        {
            glfwMaximizeWindow(handle);
            glfwGetWindowSize(handle, &state.Width, &state.Height);
        }

        if (state.VSync)
            glfwSwapInterval(1);

        if (state.BindDefaultWindowSizeCallback)
            glfwSetWindowSizeCallback(handle, WindowOnResize);

        glfwGetWindowSize(handle, &state.Width, &state.Height);
        glfwGetWindowPos(handle, &state.X, &state.Y);
    }

    Window::~Window()
    {
        glfwDestroyWindow(handle);
        glfwTerminate();
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(handle);

        glfwGetWindowSize(handle, &state.Width, &state.Height);
        glfwGetWindowPos(handle, &state.X, &state.Y);

        for (int i = 0; i < (int)Keys::Menu; i++)
            InputUpdateKey((Keys)i, glfwGetKey(handle, i) != 0);

        for (int i = 0; i < (int)Buttons::Middle; i++)
            InputUpdateButton((Buttons)i, glfwGetMouseButton(handle, i) != 0);

        {
            double MouseX, MouseY;
            glfwGetCursorPos(handle, &MouseX, &MouseY);
            InputUpdateMouse((int)MouseX, (int)MouseY);
        }

        InputUpdateScroll(accumulatedScrollX, accumulatedScrollY);
        accumulatedScrollX = accumulatedScrollY = 0;
    }

    bool Window::ShouldRun() const
    {
        return !glfwWindowShouldClose(handle);
    }
}