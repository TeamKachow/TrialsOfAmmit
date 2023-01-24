#include "Component.h"

Hudson::Entity::Component::Component(const char* name) : _name(name)
{
}

Hudson::Entity::GameObject* Hudson::Entity::Component::GetParent() const
{
    return _parent;
}

const char* Hudson::Entity::Component::GetName() const
{
    return _name;
}
