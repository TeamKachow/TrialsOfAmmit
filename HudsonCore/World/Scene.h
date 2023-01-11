#pragma once
#include <string>
#include <vector>

// forward declare
namespace Hudson
{
    namespace Entity
    {
        class GameObject;
    }

    namespace World
    {
        class SceneManager;
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
        std::vector<Entity::GameObject*> _objects; // TODO: consider making a map of ID to ptr?
        /**
         * \brief The name of this scene.
         */
        std::string _name;
        /**
         * \brief Whether or not the scene is currently active
         */
        bool _active;
        
    public:
        /**
         * \brief Get the objects currently in the scene.
         * \return The objects currently in the scene.
         */
        [[nodiscard]] const std::vector<Entity::GameObject*>& GetObjects() const;

        /**
         * \brief Get the name of this scene.
         * \return The name of this scene.
         */
        [[nodiscard]] const std::string& GetName() const;
    };
}
