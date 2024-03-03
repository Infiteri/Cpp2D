#include "Window.h"
#include "Renderer/Renderer.h"
#include "Input.h"

#include <GLFW/glfw3.h>

namespace Core
{
    static void WindowOnResize(GLFWwindow *w, int x, int y)
    {
        Renderer::Viewport(x, y);
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

        if (config.Mode == Windowed)
            glfwMaximizeWindow(handle);

        if (state.VSync)
            glfwSwapInterval(1);

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
            InputUpdateKey((Keys)i, glfwGetKey(handle, i) == GLFW_PRESS);

        for (int i = 0; i < (int)Buttons::Middle; i++)
            InputUpdateButton((Buttons)i, glfwGetMouseButton(handle, i) == GLFW_PRESS);

        {
            double MouseX, MouseY;
            glfwGetCursorPos(handle, &MouseX, &MouseY);
            InputUpdateMouse(MouseX, MouseY);
        }
    }

    bool Window::ShouldRun() const
    {
        return !glfwWindowShouldClose(handle);
    }
}