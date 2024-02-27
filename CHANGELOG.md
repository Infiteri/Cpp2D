# OFFICIAL CORE CHANGELOG

### 0.0.0 - 25.02.2024

- Logger setup and project start-up
- Platform specific code abstraction

### 0.0.0 - 26.02.2024

- Small structure, project setup, window with GLFW
- Entry point engine side handled
- EngineLoop and Engine concept were added
- Application concept

### 0.0.1 - 27.02.2024 (1)

- Input feature, not complete, fully bare-bones
- Added changelog along side the old changes that happened

### 0.0.1 - 27.02.2024 (2)

- Added license
- Removed Bin / Bin-Obj

### 0.0.2 - 27.02.2024

- Fixed Input functions, no longer works if the input system is not initialized, tied up Input::Init in Engine class
- Setup Renderer class, tied up with Engine class
- Added GLAD for OpenGL
- Added FileSystem file reading (Will add other functionality soon (hopefully))
- Removed confusion to GLFW and GLAD headers. It used to include the same file
- Added CopyAssets and engine resources concept
- Added Shader and Shader functions
- Added Buffer
