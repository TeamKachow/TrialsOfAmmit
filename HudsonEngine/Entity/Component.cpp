#include "../Entity/Component.h"

Hudson::Entity::Component::Component(const char* name) : _typeName(name)
{
    _id = rand();
}

Hudson::Entity::GameObject* Hudson::Entity::Component::GetParent() const
{
    return _parent;
}

const char* Hudson::Entity::Component::GetTypeName() const
{
    return _typeName;
}
