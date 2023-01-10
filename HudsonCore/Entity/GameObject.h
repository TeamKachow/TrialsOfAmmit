#pragma once
#include <vector>

namespace Hudson::Entity
{
    class Component;
}

namespace Hudson::Entity
{
    /**
     * Concepts let you limit what types can be passed in as template parameters.
     * This one ensures that a type is a component.
     */
    template<typename T>
    concept is_component = std::is_base_of_v<Component, T>;

    /**
     * \brief A game object that exists within a scene.
     */
    class GameObject
    {
    private:
        // TODO: _name
        // TODO: _scene
        uint32_t _id;
        std::vector<Component*> _components;

    public:
        GameObject();
        virtual ~GameObject();

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
