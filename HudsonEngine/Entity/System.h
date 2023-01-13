#pragma once
#include <vector>

#include "Common.h"
#include "GameObject.h"
#include "../World/Scene.h"
#include "../World/SceneManager.h"

// forward declare
namespace Hudson::World
{
    class Scene;
}

namespace Hudson::Entity
{
    /**
     * \brief A system acts on a series of components.
     * \tparam T The type of component this system acts on.
     */
    template<is_component T>
    class System
    {
    private:
        World::SceneManager* _sceneManager = nullptr;

    protected:
        System(World::SceneManager* sceneManager);
        virtual ~System();
        
    public:
        /**
         * \brief Get all relevant components in the active scenes.
         * \return A vector of all the relevant components in the active scenes.
         */
        std::vector<T*> GetComponents() const;

        /**
         * \brief Get all relevant components in the given scene.
         * \param scene The scene in which to search for components.
         * \return A vector of all the relevant components in the scene.
         */
        std::vector<T*> GetComponentsInScene(World::Scene* scene) const;
    };
}

template <Hudson::Entity::is_component T>
Hudson::Entity::System<T>::System(World::SceneManager* sceneManager)
{
}

template <Hudson::Entity::is_component T>
Hudson::Entity::System<T>::System::~System()
{
}

template <Hudson::Entity::is_component T>
std::vector<T*> Hudson::Entity::System<T>::GetComponents() const
{
    std::vector<T*> foundComponents;
    
    /*
    foreach _sceneManager->GetScenes() // TODO
    {
        auto sceneComponents = GetComponentsInScene(scene);
        for (auto sceneComponent : sceneComponents)
        {
            foundComponents.push_back(sceneComponent);
        }
    }
    */

    return foundComponents;
}

template <Hudson::Entity::is_component T>
std::vector<T*> Hudson::Entity::System<T>::GetComponentsInScene(World::Scene* scene) const
{
    std::vector<T*> foundComponents;
    
    for (auto object : scene->GetObjects())
    {
        auto objComponents = object->GetComponents<T>();
        for (auto objComponent : objComponents)
        {
            foundComponents.push_back(objComponent);
        }
    }

    return foundComponents;
}
