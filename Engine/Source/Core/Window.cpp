#include "Window.h"

#include <GLFW/glfw3.h>

namespace Core
{
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
    }

    bool Window::ShouldRun() const
    {
        return !glfwWindowShouldClose(handle);
    }
}