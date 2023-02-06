#pragma once
#include "../Util/stdafx.h"
#include "../Entity/Common.h"
#include "../Common/IEditable.h"
#include "../Common/ISerialisable.h"
#include "../Common/DeferredObjectSet.h"

namespace Hudson
{
    namespace Editor
    {
        class Editor;
    }
}

namespace Hudson
{
    namespace Editor
    {
        class Editor;
    }
}

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
    class GameObject final : public Common::IEditable, public Common::ISerialisable
    {
        friend World::Scene;
        friend Editor::Editor;

    public:
        struct Transform
        {
            glm::vec2 pos = { 0,0 };
            glm::vec2 scale = { 64, 64 };
            float rotateZ = 0;

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Transform, pos, scale, rotateZ)
        };

    private:
        uint32_t _serialId = rand();
        std::string _name = "Object";
        Transform _transform;
        Common::DeferredObjectSet<Component*> _components;

        World::Scene* _scene;
        /**
         * \brief Whether or not the object is currently being ticked.
         */
        bool _isCurrentlyTicking = false;

        void DrawPropertyUI() override;
        void UpdateDeferredComponents();
        void OnQueueUpdate(Common::DeferredObjectSet<Component*>::Action action);

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
         * \brief Get a list of all the components of this object to search for.
         * \tparam T The type of the components to search for.
         * \return A vector of components that match the given type.
         */
        template<is_component T>
        T* GetComponent();

        /**
         * \brief Get all the components on this object.
         * \return A vector of components on this object.
         */
        std::set<Component*> GetAllComponents();

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
        [[nodiscard]] std::string& GetName();

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

        /**
         * \brief Set the object's transform.
         * \param tsm The new object's transform
         */
        void SetTransform(Transform& tsm) { _transform = tsm; }

        /**
         * \brief Handle when the object gets added to the scene.
         */
        void OnSceneAdd();

        /**
         * \brief Handle when the scene is ticked.
         */
        void OnSceneTick(const double dt);

        /**
         * \brief Handle when the object gets removed from the scene.
         */
        void OnSceneRemove();

        /**
         * \brief Get the scene this object is currently in.
         * \return The scene this object currently is in, or null if none.
         */
        [[nodiscard]] World::Scene* GetScene() const;
        
        uint32_t GetSerialID() override;

        void FromJson(const nlohmann::json& j);
        void ToJson(nlohmann::json& j) const;

        friend void to_json(nlohmann::json& j, const GameObject& gameObject);

        friend void from_json(const nlohmann::json& j, GameObject& gameObject);
    };

    template <is_component T>
    std::vector<T*> GameObject::GetComponents()
    {
        std::vector<T*> foundComponents;

        for (auto component : GetAllComponents())
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

    template <is_component T>
    T* GameObject::GetComponent()
    {
        for (auto component : GetAllComponents())
        {
            auto castPtr = dynamic_cast<T*>(component);
            // if this component is the type we want, return it
            if (castPtr != nullptr)
            {
                return castPtr;
            }
        }
        return nullptr;
    }
}
