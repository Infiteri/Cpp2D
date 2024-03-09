#include "Actor.h"
#include "Renderer/Shader/ShaderSystem.h"
#include "Renderer/Object/Mesh.h"

namespace Core
{
    Actor::Actor()
    {
        state = Uninitialized;
        Init();
    }

    Actor::~Actor()
    {
        if (state == Running)
            Stop();

        for (auto c : components)
            delete c;

        components.clear();
    }

    void Actor::Init()
    {
        if (state != Uninitialized && state != Stopped)
            return;

        state = Initialized;
    }

    void Actor::Start()
    {
        if (state != Uninitialized)
            Init();

        state = Started;

        for (auto c : components)
        {
            c->Start();
        }
    }

    void Actor::Update()
    {
        if (!(state == Started || state == Running))
            return;

        state = Running;

        for (auto c : components)
        {
            c->Update();
        }
    }

    void Actor::Render()
    {
        if (!(state == Started || state == Running))
            return;

        state = Running;

        Shader *objectShader = ShaderSystem::Get("EngineResources/Shaders/Object");
        objectShader->Mat4(transform.GetTransformMatrix(), "uTransform");

        for (auto c : components)
        {
            c->Render();
        }
    }

    void Actor::Stop()
    {
        if (state == Uninitialized)
            return;

        state = Stopped;

        for (auto c : components)
        {
            c->Stop();
        }
    }

    void Actor::SetName(const std::string &_name)
    {
        name = _name;
    }
}