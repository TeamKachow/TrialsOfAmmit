#pragma once
#include <vector>
#include "Common.h"

namespace Hudson::Entity
{
    /**
     * \brief A game object that exists within a scene.
     */
    class GameObject final
    {
    private:
        // TODO: _name
        // TODO: _scene
        uint32_t _id;
        std::vector<Component*> _components;

    public:
        GameObject();
        ~GameObject();

        /**
         * \brief Get a list of all the components of this object to search for.
         * \tparam T The type of the components to search for.
         * \return A vector of components that match the given type.
         */
        template<is_component T>
        std::vector<T*> GetComponents();

        /**
         * \brief Get all the components on this object.
         * \return A vector of components on this object.
         */
        std::vector<Component*> GetAllComponents();

        /**
         * \brief Add a new component to this object.
         * \remark This component should be unique and should *not* be shared with other objects!
         * \param component The component to add to this object.
         * \return The newly-added component.
         */
        Component* AddComponent(Component* component);

        /**
         * \brief Remove a component from this object.
         * \remark The component will *not* be deleted - this should be done manually! (This will probably change later on?)
         * \param component The component to remove from this object.
         * \return The removed component.
         */
        Component* RemoveComponent(Component* component);
    };

    template <is_component T>
    std::vector<T*> GameObject::GetComponents()
    {
        std::vector<T*> foundComponents;

        for (auto component : _components)
        {
            auto castPtr = dynamic_cast<T*>(component);
            // if this component is the type we want, add to the list
            if (castPtr != nullptr)
            {
                foundComponents.push_back(castPtr);
            }
        }

        return foundComponents;
    }
}
