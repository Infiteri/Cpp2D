#include "Actor.h"
#include "Renderer/Shader/ShaderSystem.h"
#include "Renderer/Object/Mesh.h"

#include <algorithm>

namespace Core
{

    Actor::Actor()
    {
        state = Uninitialized;
        name = "Actor";
        parent = nullptr;
        Init();
    }

    Actor::~Actor()
    {
        if (state == Running)
            Stop();

        for (auto c : components)
            delete c;

        for (auto c : children)
            delete c;

        components.clear();
        children.clear();
    }

    void Actor::CalculateTransforms()
    {
        localMatrix = transform.GetTransformMatrix();

        if (parent)
            worldMatrix = Matrix4::Multiply(parent->GetWorldMatrix(), &localMatrix);
        else
            worldMatrix = localMatrix;
    }

    void Actor::Init()
    {
        if (state != Uninitialized && state != Stopped)
            return;

        state = Initialized;

        for (auto actor : children)
            actor->Init();
    }

    void Actor::Start()
    {
        if (state != Uninitialized)
            Init();

        state = Started;

        for (auto c : components)
            c->Start();

        for (auto actor : children)
            actor->Start();
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

        for (auto actor : children)
            actor->Update();
    }

    void Actor::Render()
    {
        if (!(state == Started || state == Running))
            return;

        state = Running;

        Shader *objectShader = ShaderSystem::Get("EngineResources/Shaders/Object");

        CalculateTransforms();
        objectShader->Mat4(worldMatrix, "uTransform");

        for (auto c : components)
        {
            c->Render();
        }

        for (auto actor : children)
            actor->Render();
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

        for (auto actor : children)
            actor->Stop();
    }

    void Actor::SetName(const std::string &_name)
    {
        name = _name;
    }

    void Actor::AddChild(Actor *actor)
    {
        actor->parent = this;
        children.push_back(actor);
    }

    Actor *Actor::FindChildInHierarchyByUUID(const UUID &uuid)
    {
        // Check if the current actor's UUID matches the one we are looking for
        if (this->uuid == uuid)
        {
            return this;
        }

        // First, search the immediate children
        for (Actor *child : children)
        {
            if (child->GetUUID()->Get() == uuid.Get())
            {
                return child;
            }
        }

        // If not found in immediate children, recursively search through their children
        for (Actor *child : children)
        {
            Actor *result = child->FindChildInHierarchyByUUID(uuid);
            if (result != nullptr)
            {
                // If we found the actor in a child's hierarchy, return it
                return result;
            }
        }

        // If not found in children or their children, return nullptr
        return nullptr;
    }

    Actor* Actor::GetChildByUUID(const UUID &uuid) {

        if(this->uuid == uuid)
            return this;

        for(auto child : children)
        {
            if(child->uuid == uuid)
                return child;
        }

        return nullptr;
    }


    void Actor::MoveActorInHierarchy(const UUID &uid, int newIndex)
    {
        if (newIndex < 0 || newIndex >= children.size())
            return;

        Actor *actorToMove = GetChildByUUID(uid);
        if (!actorToMove)
            return;

        // Find the current index of the actor
        auto actorIterator = std::find(children.begin(), children.end(), actorToMove);

        if (actorIterator != children.end())
        {
            size_t currentIndex = std::distance(children.begin(), actorIterator);

            // Remove the actor from the current position
            children.erase(actorIterator);

            // Insert the actor at the new index
            children.insert(children.begin() + newIndex, actorToMove);
        }
    }

    void Actor::EraseChildByUUID(const UUID &uuid)
    {
        int index = -1;
        for (auto it : children)
        {
            index++;
            if (it->GetUUID()->Get() == uuid.Get())
                children.erase(children.begin() + index);
        }
    }

}