#pragma once

#include "Base.h"

#include "Core/Logger.h"
#include "Core/Engine.h"
#include "Core/Input.h"
#include "Core/Application.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/ImGuiLayer.h"
#include "Core/Layer/LayerStack.h"

#include "Math/Math.h"
#include "Math/Vectors.h"
#include "Math/Matrix4.h"
#include "Math/Transform.h"

#include "Platform/FileSystem.h"
#include "Platform/Platform.h"

#include "Renderer/Renderer.h"
#include "Renderer/Color.h"
#include "Renderer/Object/Mesh.h"
#include "Renderer/Object/Sprite.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/MaterialSystem.h"
#include "Renderer/Texture/TextureSystem.h"
#include "Renderer/Camera/CameraSystem.h"
#include "Renderer/Geometry/Geometry.h"

#include "Resources/Loader/MaterialLoader.h"

#include "Scene/Actor.h"
#include "Scene/Scene.h"
#include "Scene/World.h"
#include "Scene/SceneSerializer.h"
#include "Scene/Components/Components.h"

#include "Script/ActorScript.h"
#include "Script/ScriptEngine.h"