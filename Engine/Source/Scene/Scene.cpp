#include "Scene.h"

namespace Core
{
    Scene::Scene()
    {
        state = Uninitialized;
        Init();
    }

    Scene::~Scene()
    {
        if (state == Running)
            Stop();
    }

    void Scene::Init()
    {
        if (state != Uninitialized && state != Stopped)
            return;

        for (auto a : actors)
        {
            a->Init();
        }

        state = Initialized;
    }

    void Scene::Start()
    {
        if (state != Uninitialized)
            Init();

        state = Started;

        for (auto a : actors)
        {
            a->Start();
        }
    }

    void Scene::Update()
    {
        if (!(state == Started || state == Running))
            return;

        state = Running;

        for (auto a : actors)
        {
            a->Update();
        }
    }

    void Scene::Render()
    {
        if (!(state == Started || state == Running))
            return;

        state = Running;

        for (auto a : actors)
        {
            a->Render();
        }
    }

    void Scene::Stop()
    {
        if (state == Uninitialized)
            return;

        state = Stopped;

        for (auto a : actors)
        {
            a->Stop();
        }
    }

    void Scene::SetName(const std::string &_name)
    {
        name = _name;
    }

    void Scene::AddActor(Actor *actor)
    {
        actors.push_back(actor);

        if (state == Uninitialized)
            return;

        if (state == Initialized)
        {
            actor->Init();
            return;
        }

        if (state == Running || state == Started)
        {
            actor->Start();
            return;
        }

        if (state == Stopped)
        {
            actor->Stop();
            return;
        }
    }

    Actor *Scene::AddActor()
    {
        Actor *a = new Actor();
        AddActor(a);
        return a;
    }

    void Scene::ClearActorSet()
    {
        if (!(state == Stopped || state == Initialized))
            return;

        for (auto a : actors)
            delete a;
        actors.clear();
    }
}