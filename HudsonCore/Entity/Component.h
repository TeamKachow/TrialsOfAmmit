#pragma once

namespace Hudson::Core::Entity
{
    class GameObject;

    class Component
    {
        friend GameObject;
        
    protected:
        GameObject* _parent = nullptr;
        
    public:
        Component() = default;
        virtual ~Component() = default;
    };
}
