#pragma once
#include "Common.h"

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
        
    protected:
        GameObject* _parent = nullptr;
        const char* _name;
        
    public:
        Component(const char* name);
        virtual ~Component() = default;

        [[nodiscard]] GameObject* GetParent() const;

        const char* GetName() const;
    };
}
