#include "Component.h"

Hudson::Entity::GameObject* Hudson::Entity::Component::GetParent() const
{
    return _parent;
}
