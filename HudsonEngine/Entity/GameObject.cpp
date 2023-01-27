#include "../Entity/GameObject.h"

#include "../Entity/Component.h"
#include "../Util/Debug.h"

void Hudson::Entity::GameObject::DrawPropertyUI()
{
    for (auto component : _components)
    {
        IEditable* editableComponent = dynamic_cast<IEditable*>(component);
        if (editableComponent == nullptr)
        {
            editableComponent->DrawPropertyUI();
        }
    }
}

Hudson::Entity::GameObject::GameObject() : _scene(nullptr)
{
    _id = rand();
}

Hudson::Entity::GameObject::~GameObject()
{
    // Delete all 
    for (auto it = _components.begin(); it < _components.end(); ++it)
    {
        auto toDelete = *it;
        // Check we didn't somehow end up holding another object's component
        if (toDelete->_parent != this)
        {
            std::stringstream msg;
            msg << "Found reference to component owned by other object while destroying " << this;
            Util::Debug::LogError(msg.str());
        }
        else
        {
            delete toDelete;
        }
    }

    _components.clear();
}

std::vector<Hudson::Entity::Component*> Hudson::Entity::GameObject::GetAllComponents()
{
    return _components;
}

Hudson::Entity::Component* Hudson::Entity::GameObject::AddComponent(Component* component)
{
    // TODO: queue adds/removal until after object tick
    
    // Check that the component is not owned by another object
    if (component->_parent != nullptr)
    {
        std::stringstream msg;
        msg << "Cannot add component " << component << " to object " << this << " that already belongs to object " << component->_parent;
        Util::Debug::LogError(msg.str());
        return component;
    }

    // Set component's owner to this object
    component->_parent = this;

    // Add component to this object's list of components
    _components.push_back(component);

    return component;
}

Hudson::Entity::Component* Hudson::Entity::GameObject::RemoveComponent(Component* component)
{
    // TODO: queue adds/removal until after object tick

    // Check that we own the component
    if (component->_parent != this)
    {
        // TODO Util::Debug::LogError("Cannot remove a component that does not belong to this object!");
        std::stringstream msg;
        msg << "Cannot remove component " << component << " from object " << this << " that belongs to object " << component->_parent;
        Util::Debug::LogError(msg.str());
        return component;
    }

    // Clear the component's owner
    component->_parent = nullptr;

    // Remove component from this object's list of components
    auto shouldRemove = [&](auto const& val) { return val == component; };
    erase_if(_components, shouldRemove);

    return component;
}

std::string& Hudson::Entity::GameObject::GetName()
{
    return _name;
}

void Hudson::Entity::GameObject::SetName(const std::string& name)
{
    _name = name;
}

Hudson::Entity::GameObject::Transform& Hudson::Entity::GameObject::GetTransform()
{
    return _transform;
}

void Hudson::Entity::GameObject::OnSceneAdd()
{
    // TODO: call Behaviour OnAdd
}

void Hudson::Entity::GameObject::OnSceneRemove()
{
    // TODO: call Behaviour OnRemove
}
