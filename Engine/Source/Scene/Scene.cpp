#include "Scene.h"
#include "Core/Logger.h"
#include "Script/ScriptEngine.h"
#include "Physics/PhysicsEngine.h"
#include "Components/Components.h"

#include <algorithm>

namespace Core
{
    static int SearchConductIndex = -1;

    Scene::Scene()
    {
        state = Uninitialized;
        Init();
    }

    Scene::~Scene()
    {
        if (state == Running)
            Stop();

        ClearActorSet();
    }

    Scene *Scene::From(Scene *o)
    {
        Scene *scene = new Scene();

        scene->SetName(o->GetName());

        for (auto a : o->GetActors())
        {
            auto act = Actor::From(a);
            scene->AddActor(act);
        }

        return scene;
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

        CameraComponent *cameraComponent = nullptr;
        for (auto a : actors)
        {
            a->Start();

            auto rigidComponents = a->GetComponents<RigidBodyComponent>();
            for (auto sc : rigidComponents)
            {
                sc->Owner = a;
                sc->Configuration.Owner = a;
                sc->Body = PhysicsEngine::RegisterFromConfig(&sc->Configuration);
            }

            // Script setup
            auto scriptComponents = a->GetComponents<ActorScriptComponent>();
            for (auto sc : scriptComponents)
                ScriptEngine::RegisterActorScript(sc->ClassName, a, a->GetName());

            // Camera setup
            if (cameraComponent == nullptr)
                cameraComponent = a->GetComponentInHierarchy<CameraComponent>();
        }

        if (cameraComponent)
            CameraSystem::Activate(cameraComponent->camera);
        else
            CameraSystem::Activate(nullptr);

        ScriptEngine::StartRuntime();
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

        ScriptEngine::UpdateRuntime();
        PhysicsEngine::UpdateRuntime();
    }

    void Scene::Render()
    {
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

        ScriptEngine::StopRuntime();
        PhysicsEngine::StopRuntime();
    }

    void Scene::SetName(const std::string &_name)
    {
        name = _name;
    }

    void Scene::AddActor(Actor *actor)
    {
        actors.push_back(actor);
        actor->SetUUID({}); // I dunno

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

    Scene::DetailedActorSearch Scene::FindActorByUUIDInHierarchyDetailed(const UUID &uuid)
    {
        SearchConductIndex = -1;
        DetailedActorSearch res;
        res.UUIDSearchBy = uuid;
        res.Index = 0;
        res.Result = nullptr;

        bool returned = false;

        for (auto it : actors)
        {
            if (it->GetUUID()->Get() == uuid.Get())
            {
                SearchConductIndex++;
                returned = true;
                res.Result = it;
                res.Index = SearchConductIndex;
                return res;
            }
        }

        if (!returned)
        {
            for (auto it : actors)
            {
                auto child = it->FindChildInHierarchyByUUID(uuid);
                if (child != nullptr)
                {
                    SearchConductIndex++;
                    returned = true;
                    res.Result = it;
                    res.Index = SearchConductIndex;
                    return res;
                }
            }
        }

        return res;
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
    void Scene::RemoveActorByUUID(const UUID &id)
    {
        std::vector<int> indicesToDelete;
        for (int index = 0; index < actors.size(); ++index)
        {
            auto it = actors[index];
            if (*it->GetUUID() == id)
            {
                // Mark for deletion
                delete it;
                indicesToDelete.push_back(index);
            }
        }
        for (int i = indicesToDelete.size() - 1; i >= 0; --i)
            actors.erase(actors.begin() + indicesToDelete[i]);
        for (auto it : actors)
            it->RemoveChildByUUIDInHierarchy(id);
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