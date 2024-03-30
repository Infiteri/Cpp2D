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

### 0.0.3 - 03.03.2024

- Added Layers
- Added ImGui
- Added EditorLayer class
- Updated Core.h to include files
- Removed Render function on class (didn't function properly / !API CHANGE)
- Added Engine::Configuration concept along side it's usage, will have a "LoadFromFile" flag later on
- Added Window size modes with Normal, Windowed and Fullscreen
- Added better getters for Window class with Width and Height
- Added Input class functions for mouse position and delta
- Exported the Color class and Renderer class to the DLL
- Added Renderer custom BG color support
- Added temporary color background change with ImGui in editor layer
- Added Material and MaterialSystem
- Added YAML
- Added Material from file

### 0.0.3 - 08.03.2024

- Added Texture support
- Added TextureSystem
- Added Texture material file support
- Sorry for inactivity to all women out there happy women's day

### 0.0.4 - 09.03.2024

- Added Scene
- Added Actor
- Added World
- Added Components
- Added Scene Serializer
- Updated Core.h
- Fixed the Material and Texture system initialization bug
- Removed default mesh
- Added Transform
- Other fixes

### 0.0.5 - 12.03.2024

- Started work on the editor
- Made editor viewport and scene result gets rendered to the editor viewport
- Added Scene Hierarchy
- Added UUID along side its serialization and other needed stuff
- Removed old material API
- Fixed old material API
- Added color tinting
- Added Fonts to styling the editor
- A lot of API changes

### 0.0.6 - 14.03.2024

- Default Actor name
- Added scene saving
- Started actor parenting
- Added scene hierarchy right click
- Added actor parenting serialization / deserialization
- Added actor parenting editor functionality

### 0.0.7 - 16.03.2024

- Updated Core.h
- Added right-click component adding
- API Change -> components get properly removed now with no more memory leaks
- API Change -> Actor API for actor parenting and stuff
- Added Input API for changing mouse mode
- Added camera movement with mouse
- Added camera zoom with mouse plus left control
- Other stuff

### 0.0.8 - 17.03.2024

- Updated Core.h
- Added editor settings along side (de)serialization
- Added style color edits
- Fixed Component deletion problem
- Added ability to change texture image
- Added basic geometry types
- Geometry editing in editor
- Added geometry serialization

### 0.0.9 - 18.03.2024

- Added Start/Stop editor logic
- Added Start/Stop scene logic
- Scene camera gets activated on runtime start
- Fixed deserialization scope errors
- Added sprite concept for future
- Added primitive concept for animation

### 0.1.0 - 19.03.2024

- Updated Core.h
- Added basic library loading
- Added basic dll function loading
- Added ScriptEngine and ActorScript
- Added ActorScriptComponent +(de)serialization and in-editor editing
- QoL changes in code
- Fixed texture config copying when starting scenes
- Hooked up script logic with scene
- Test scripting example

### 0.1.1 - 26.03.2024

- Bugs and fixes
- Started physics

### 0.1.2 - 30.03.2024

- Work
- Safe net
