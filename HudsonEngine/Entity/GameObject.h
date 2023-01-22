#pragma once
#include "../Util/stdafx.h"
#include "Common.h"
#include "../Common/IEditable.h"

// forward declare
namespace Hudson::World
{
    class Scene;
}

namespace Hudson::Entity
{
    /**
     * \brief A game object that exists within a scene.
     */
    class GameObject final : public Common::IEditable
    {
        friend World::Scene;

    public:
        struct Transform
        {
            // TODO: replace with vec2f
            glm::vec2 pos = {0,0};
            glm::vec2 scale = {64, 64};
            float rotateZ = 0;
        };
        
    private:
        std::string _name;
        World::Scene* _scene;
        uint32_t _id;
        std::vector<Component*> _components;
        Transform _transform;

        void DrawPropertyUI() override;
    
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
         * \remark The component will *not* be deleted - this should be done manually! (Subject to change?)
         * \param component The component to remove from this object.
         * \return The removed component.
         */
        Component* RemoveComponent(Component* component);

        /**
         * \brief Get the name of this object instance.
         * \return The object's name
         */
        [[nodiscard]] std::string GetName() const;

        /**
         * \brief Set the name of this object instance.
         * \param name The object's new name
         */
        void SetName(const std::string& name);

        /**
         * \brief Get this object's transform.
         * \return This object's transform
         */
        Transform& GetTransform();
        void SetTransform(Transform& tsm) { _transform = tsm; }
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
