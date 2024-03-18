#pragma once

#include "Base.h"
#include "Camera.h"
#include "OrthographicCamera.h"
#include <string>

namespace Core
{
    /// @brief The CameraSystem class manages cameras in the application.
    ///
    /// This class provides functionality to create, access, and manipulate cameras.
    class CE_API CameraSystem
    {
    public:
        /// @brief Initializes the camera system.
        ///
        /// This function is called by the Renderer to initialize the camera system.
        static void Init();

        /// @brief Shuts down the camera system.
        ///
        /// This function is called by the Renderer to shut down the camera system.
        static void Shutdown();

        /// @brief Updates the camera system's viewport and projection for all cameras.
        ///
        /// This function is called by the Renderer to update the viewport and projection
        /// for all registered cameras.
        ///
        /// @param width The new width of the viewport.
        /// @param height The new height of the viewport.
        static void Viewport(int width, int height);

        /// @brief Creates a new Orthographic Camera.
        ///
        /// This function creates a new Orthographic Camera with the given name and returns a pointer to it.
        ///
        /// @param name The name of the camera.
        /// @return A pointer to the created OrthographicCamera.
        static OrthographicCamera *CreateOrtho(const std::string &name);

        /// @brief Retrieves a camera by its name.
        ///
        /// This function retrieves a camera by the specified name.
        ///
        /// @param name The name of the camera to retrieve.
        /// @return A pointer to the Camera with the specified name, or nullptr if not found.
        static Camera *Get(const std::string &name);

        /// @brief Retrieves the currently active camera.
        ///
        /// This function retrieves a pointer to the currently active Camera.
        ///
        /// @return A pointer to the active Camera, or nullptr if no camera is active.
        static Camera *GetActive();

        /// @brief Activates a camera by its name.
        ///
        /// This function activates a camera with the specified name.
        ///
        /// @param name The name of the camera to activate.
        /// @return True if activation was successful, false otherwise.
        static bool Activate(const std::string &name);

        /// @brief Will activate a camera based on its instance.
        /// @param camera The camera to use
        static void Activate(OrthographicCamera *camera);

        /// @brief Updates the active camera.
        ///
        /// This function updates the state of the active camera.
        ///
        /// This should be called every frame to update the active camera's state.
        static void UpdateActive();

        /// @brief Removes a camera by its name.
        ///
        /// This function removes a camera with the specified name.
        ///
        /// @param name The name of the camera to remove.
        static void Remove(const std::string &name);
    };
}
