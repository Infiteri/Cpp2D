#pragma once

#include "Base.h"
#include "Components/Components.h"
#include "Math/Transform.h"
#include <vector>

namespace Core
{
    class CE_API Actor
    {
    public:
        /// @brief Represents all possible states for a actor.
        enum StateType
        {
            /// @brief Just created, can only call Init (witch is done automatically), and can be deleted.
            Uninitialized,

            /// @brief Init is called, can Render and Stop but cannot Update.
            Initialized,

            /// @brief Can perform Update routine, can call Stop.
            Started,

            /// @brief Either Rendering or Updating.
            Running,

            /// @brief Stopped, can call Init again and can Render but cannot Update.
            Stopped,
        };

    private:
        StateType state;
        std::vector<Component *> components;
        std::string name;
        Transform transform;

    public:
        Actor();
        ~Actor();

        /// @brief Called when the actor is just created, called automatically so no need to manually call it.
        void Init();

        /// @brief Called when starting the actor, can call stop afterwards, also allows for Updating.
        void Start();

        /// @brief Performs runtime Update Routine.
        void Update();

        /// @brief Renders the actor.
        void Render();

        /// @brief Called when stopping the actor, can call Start afterwards.
        void Stop();

        inline StateType GetState() { return state; };

        inline Transform* GetTransform() { return &transform; };
        inline std::string GetName() { return name; };
        void SetName(const std::string &name);

        // -- Components --

        template <typename T, typename... Args>
        T *AddComponent(Args... args)
        {
            T *c = new T(args...);
            c->owner = this;

            if (state == Stopped)
                c->Stop();

            if (state == Started || state == Running)
                c->Start();

            components.push_back(c);
            return c;
        };

        template <typename T>
        T *GetComponent()
        {
            for (Component *c : components)
            {
                T *typedComponent = dynamic_cast<T *>(c);
                if (typedComponent)
                {
                    return typedComponent;
                }
            }

            return nullptr;
        };

        template <typename T>
        bool HasComponent()
        {
            return GetComponent<T>() != nullptr;
        };

        template <typename T>
        std::vector<T *> GetComponents()
        {
            std::vector<T *> ts;
            for (Component *c : components)
            {
                T *typedComponent = dynamic_cast<T *>(c);
                if (typedComponent)
                    ts.push_back(typedComponent);
            }

            return ts;
        };

        template <typename T>
        void RemoveComponent()
        {
            for (auto it = components.begin(); it != components.end(); ++it)
            {
                T *typedComponent = dynamic_cast<T *>(*it);
                if (typedComponent)
                {
                    components.erase(it);
                    typedComponent->Destroy();
                    delete typedComponent;
                    break;
                }
            }
        };

        template <typename T>
        void RemoveComponents()
        {
            for (auto it = components.begin(); it != components.end(); ++it)
            {
                T *typedComponent = dynamic_cast<T *>(*it);
                if (typedComponent)
                {
                    components.erase(it);
                    typedComponent->Destroy();
                    delete typedComponent;
                }
            }
        };

        inline std::vector<Component *> GetAllComponents() { return components; };

        // -- Components end --
    };
}