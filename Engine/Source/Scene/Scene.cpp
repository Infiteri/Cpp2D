#include "Scene.h"
#include "Core/Logger.h"
#include "Script/ScriptEngine.h"
#include "Components/Components.h"

#include "Core/Engine.h"

#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"

#include <algorithm>

namespace Core
{
    static int SearchConductIndex = -1;

    Scene::Scene()
    {
        physicsWorld = nullptr;
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

        physicsWorld = new b2World({0.0, 9.81f * 250});

        CameraComponent *cameraComponent = nullptr;
        for (auto a : actors)
        {
            a->Start();

            // Script setup
            {
                auto scriptComponents = a->GetComponents<ActorScriptComponent>();
                for (auto sc : scriptComponents)
                    ScriptEngine::RegisterActorScript(sc->ClassName, a, a->GetName());
            }

            // Physics setup
            {
                auto rigidComponents = a->GetComponents<RigidBody2DComponent>();
                for (auto r : rigidComponents)
                {
                    b2BodyDef def;
                    def.type = (b2BodyType)r->Type;
                    Vector3 wPos = a->GetWorldPosition();
                    def.position.Set(wPos.x, wPos.y);
                    def.angle = a->GetTransform()->Rotation.z;
                    b2Body *body = physicsWorld->CreateBody(&def);
                    body->SetFixedRotation(r->FixedRotation);
                    r->RuntimeBody = body;

                    auto boxComponents = a->GetComponents<BoxCollider2DComponent>();
                    for (auto b : boxComponents)
                    {
                        b2PolygonShape shape;
                        shape.SetAsBox((b->Size.x) * a->GetTransform()->Scale.x, (b->Size.y) * a->GetTransform()->Scale.y);

                        b2FixtureDef fixDef;
                        fixDef.shape = &shape;
                        fixDef.density = b->Density;
                        fixDef.friction = b->Friction;
                        fixDef.restitution = b->Restitution;
                        fixDef.restitutionThreshold = b->RestitutionThreshold;

                        body->CreateFixture(&fixDef);
                    }
                }
            }

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

        {
            const int32_t velocityIterations = 6;
            const int32_t positionIterations = 2;
            physicsWorld->Step(0.016f, velocityIterations, positionIterations);
        }

        for (auto a : actors)
        {
            a->Update();

            auto rigidComps = a->GetComponents<RigidBody2DComponent>();
            for (auto rb : rigidComps)
            {
                b2Body *body = (b2Body *)rb->RuntimeBody;

                auto pos = body->GetPosition();

                a->GetTransform()->Position.x = body->GetPosition().x;
                a->GetTransform()->Position.y = body->GetPosition().y;
                a->GetTransform()->Rotation.z = body->GetAngle();
            }
        }

        ScriptEngine::UpdateRuntime();
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

        if (physicsWorld)
        {
            delete physicsWorld;
            physicsWorld = nullptr;
        }

        ScriptEngine::StopRuntime();
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