#include "GameObject.h"

#include "Component.h"

Hudson::Core::Entity::GameObject::GameObject()
{
    _id = rand();
}

Hudson::Core::Entity::GameObject::~GameObject()
{
    // Delete all 
    for (auto it = _components.begin(); it < _components.end(); ++it)
    {
        auto toDelete = *it;
        // Check we didn't somehow end up holding another object's component
        if (toDelete->_parent != this)
        {
            // TODO: log
        }
        else
        {
            delete toDelete;
        }
    }

    _components.clear();
}

std::vector<Hudson::Core::Entity::Component*> Hudson::Core::Entity::GameObject::GetAllComponents()
{
    return _components;
}

Hudson::Core::Entity::Component* Hudson::Core::Entity::GameObject::AddComponent(Component* component)
{
    // Check that the component is not owned by another object
    if (component->_parent != nullptr)
    {
        // TODO: log an error here!
        return component;
    }

    // Set component's owner to this object
    component->_parent = this;

    // Add component to this object's list of components
    _components.push_back(component);

    return component;
}

Hudson::Core::Entity::Component* Hudson::Core::Entity::GameObject::RemoveComponent(Component* component)
{
    // TODO: consider whether we want to delete components here?

    // Check that we own the component
    if (component->_parent != this)
    {
        // TODO: log an error here!
        return component;
    }

    // Clear the component's owner
    component->_parent = nullptr;

    // Remove component from this object's list of components
    auto shouldRemove = [&](auto const& val) { return val == component; };
    erase_if(_components, shouldRemove);

    return component;
}
