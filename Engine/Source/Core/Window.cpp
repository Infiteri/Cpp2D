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
        // TODO: Size modes.

        handle = glfwCreateWindow(state.Width, state.Height, state.Title, NULL, NULL); // TODO: Sizes modes
        glfwMakeContextCurrent(handle);
        glfwShowWindow(handle);

        if (state.VSync)
            glfwSwapInterval(1);

        glfwSetWindowSizeCallback(handle, WindowOnResize);
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
    }

    bool Window::ShouldRun() const
    {
        return !glfwWindowShouldClose(handle);
    }
}