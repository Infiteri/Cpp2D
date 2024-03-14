#include "Scene.h"

#include <algorithm>

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

    Actor *Scene::GetActorByUUID(const UUID &uuid)
    {
        for (auto it : actors)
        {
            if (it->GetUUID()->Get() == uuid.Get())
                return it;
        }

        return nullptr;
    }

    Actor *Scene::FindActorByUUIDInHierarchy(const UUID &uuid)
    {
        bool returned = false;
        for (auto it : actors)
        {
            if (it->GetUUID()->Get() == uuid.Get())
            {
                returned = true;
                return it;
            }
        }

        if (!returned)
        {
            for (auto it : actors)
            {
                auto child = it->FindChildInHierarchyByUUID(uuid);
                if (child != nullptr)
                    return child;
            }
        }

        return nullptr;
    }

    bool Scene::ChildActor(const UUID &parentUUID, const UUID &childUUID)
    {
        auto parent = FindActorByUUIDInHierarchy(parentUUID);
        auto child = FindActorByUUIDInHierarchy(childUUID);
        if (!parent || !child)
            return false;

        if (child->GetParent() == nullptr)
            EraseActorByUUID(childUUID);
        else
            child->GetParent()->EraseChildByUUID(*child->GetUUID());

        parent->AddChild(child);

        return true;
    }

    void Scene::EraseActorByUUID(const UUID &id)
    {
        int index = -1;
        for (auto it : actors)
        {
            index++;
            if (*it->GetUUID() == id)
                actors.erase(actors.begin() + index);
        }
    }

    void Scene::MoveActorInHierarchy(const UUID &uid, int newIndex)
    {
        if (newIndex < 0 || newIndex >= actors.size())
            return;
        
        Actor *actorToMove = FindActorByUUIDInHierarchy(uid);

        if (!actorToMove)
            return;


        // Find the current index of the actor
        auto actorIterator = std::find(actors.begin(), actors.end(), actorToMove);

        if (actorIterator != actors.end())
        {
            size_t currentIndex = std::distance(actors.begin(), actorIterator);

            // Remove the actor from the current position
            actors.erase(actorIterator);

            // Insert the actor at the new index
            actors.insert(actors.begin() + newIndex, actorToMove);
        }
    }
}