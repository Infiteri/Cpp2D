#pragma once

#include "Base.h"
#include "Actor.h"
#include <vector>

namespace Core
{
    class CE_API Scene
    {
    public:
        /// @brief Represents all possible states for a scene.
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
        std::vector<Actor *> actors;
        std::string name;

    public:
        Scene();
        ~Scene();

        /// @brief Called when the scene is just created, called automatically so no need to manually call it.
        void Init();

        /// @brief Called when starting the scene, can call stop afterwards, also allows for Updating.
        void Start();

        /// @brief Performs runtime Update Routine.
        void Update();

        /// @brief Renders the scene.
        void Render();

        /// @brief Called when stopping the scene, can call Start afterwards.
        void Stop();

        inline std::string GetName() { return name; };
        void SetName(const std::string &name);

        /// @brief Will ad an actor to the scene, also it keeps the reference, use "new Actor()" as argument for best result as the scene keeps the reference and uses it.
        /// @param actor The actor to spawn.
        void AddActor(Actor *actor);

        /// @brief Will spawn, create and add a new actor. Keeps the reference, better then the other method.
        /// @return A pointer to an actor class.
        Actor *AddActor();

        template <typename T>
        T *SpawnActor()
        {
            T *t = new T();
            AddActor(t);
            return t;
        };

        /// @brief Will clear all the actors and fresh the whole thing out.
        /// Must be stopped.
        void ClearActorSet();

        inline std::vector<Actor *> GetActors() { return actors; };
        Actor *GetActorByUUID(const UUID &uuid);
        Actor *FindActorByUUIDInHierarchy(const UUID &uuid);

        inline StateType GetState() { return state; };

        bool ChildActor(const UUID &parentUUID, const UUID &childUUID);

        /// @brief Will erase the child without deleting the actual address value.
        /// @param id The actor UUID.
        void EraseActorByUUID(const UUID &id);

        void MoveActorInHierarchy(const UUID &uid, int index);
    };
}