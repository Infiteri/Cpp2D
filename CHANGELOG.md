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

### 0.0.2 - 29.02.2024

- Added TODO.md (will be filled later on)
- Added Buffer layouts
- Removed Editor input checks
- Added Vertex Array along side Buffer internal binding
- Made renderer example to square
- Added resize callback in window
- Added VSync to window options
- Added FrameBuffer screen texture
- Fixed Buffer bugs

### 0.0.2 - 02.03.2024

- Added Color class
- Added GPUScreen concept
- Added Mesh object
- Added Math library
- Added Shader upload functions for math
- Added Camera class
- Orthographic camera works
- Added CameraSystem class along side documentation for it