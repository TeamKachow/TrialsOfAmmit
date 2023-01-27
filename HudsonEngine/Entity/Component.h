#pragma once
#include "../Entity/Common.h"

namespace Hudson
{
    namespace Editor
    {
        class Editor;
    }
}

namespace Hudson::Entity
{
    /**
     * \brief A component which makes up part of the functionality of an object.
     * \note This represents pure data to be acted upon; for a functional component, see Behaviour.h
     * \note This can only be added to one game object at a time.
     */
    class Component
    {
        friend GameObject;
        friend Editor::Editor;
        
    protected:
        GameObject* _parent = nullptr;
        const char* _typeName;
        uint32_t _id;
        
    public:
        /**
         * \brief Create a component with the given type name
         * \param name The name of this type of component
         */
        Component(const char* name);
        virtual ~Component() = default;

        /**
         * \brief Get the object that this component belongs to.
         * \return The object that this component belongs to, or null if it doesn't belong to an object.
         */
        [[nodiscard]] GameObject* GetParent() const;

        /**
         * \brief Get the name of this *type* of component (NOT this specific instance).
         * \return The name identifying this type of component.
         */
        [[nodiscard]] const char* GetTypeName() const;
    };
}
