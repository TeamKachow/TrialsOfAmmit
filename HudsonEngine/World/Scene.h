#pragma once
#include "../Util/stdafx.h"
#include "./Common.h"

namespace Hudson
{
    namespace Common
    {
        class ResourceManager;
    }
}

// forward declare
namespace Hudson
{
    namespace Entity
    {
        class GameObject;
    }
}

namespace Hudson::World
{    
    /**
     * \brief A scene is a collection of grouped objects in the game.
     * \details Scenes can be loaded (and saved in the editor). Multiple scenes can run at once; this is managed by the SceneManager.
     */
    class Scene
    {        
    private:
        /**
         * \brief The vector of objects in this scene.
         */
        std::set<Entity::GameObject*> _objects; // TODO: ReferencePtr? or maybe not here
        /**
         * \brief The name of this scene.
         */
        std::string _name = "Untitled";
        /**
         * \brief Whether or not the scene is currently actively ticking.
         */
        bool _active = true;
        /**
         * \brief Whether or not the scene is currently visible.
         */
        bool _rendering = true;

        // TODO Common::ResourceManager* _resManager;
        
    public:
        /**
         * \brief Get the objects currently in the scene.
         * \return The objects currently in the scene.
         */
        [[nodiscard]] const std::set<Entity::GameObject*>& GetObjects() const;

        /**
         * \brief Get the name of this scene.
         * \return The name of this scene.
         */
        [[nodiscard]] const std::string& GetName() const;

        /**
         * \brief Set the scene's name.
         * \param name The new name for the scene
         */
        void SetName(const std::string& name);

        /**
         * \brief Get the scene's active ticking state.
         * \return Whether or not this scene should be ticked
         */
        [[nodiscard]] bool IsActive() const;

        /**
         * \brief Set the scene's active ticking state.
         * \param active The new active state value
         */
        void SetActive(bool active);

        /**
         * \brief Gets the scene's rendering state.
         * \return Whether or not this scene is being rendered
         */
        [[nodiscard]] bool IsRendering() const;

        /**
         * \brief Set the scene's rendering state.
         * \param rendering The new rendering state value
         */
        void SetRendering(bool rendering);

        /**
         * \brief Tick the objects in this scene if active.
         * \param dt The time since the last tick (should be fixed rate!)
         */
        void Tick(const double dt) const;

        /**
         * \brief Add an object to the scene.
         * \param object The object to add to the scene.
         */
        Entity::GameObject* AddObject(Entity::GameObject* object);

        /**
         * \brief Remove an object from the scene.
         * \param object The object to remove from the scene
         */
        Entity::GameObject* RemoveObject(Entity::GameObject* object);
    };
}
