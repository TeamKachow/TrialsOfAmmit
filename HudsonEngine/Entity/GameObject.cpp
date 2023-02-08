﻿#include "../Entity/GameObject.h"

#include "Behaviour.h"
#include "../Common/Engine.h"
#include "../Entity/Component.h"
#include "../Util/Debug.h"

void Hudson::Entity::GameObject::DrawPropertyUI()
{
    for (auto component : _components.Get())
    {
        IEditable* editableComponent = dynamic_cast<IEditable*>(component);
        if (editableComponent == nullptr)
        {
            editableComponent->DrawPropertyUI();
        }
    }
}

void Hudson::Entity::GameObject::UpdateDeferredComponents()
{
    _components.Update();
}

void Hudson::Entity::GameObject::OnQueueUpdate(Common::DeferredObjectSet<Component*>::Action action)
{
    Component* component = action.first;
    Behaviour* behaviour = dynamic_cast<Behaviour*>(component);
    switch (action.second)
    {
    case Common::DeferredObjectSet<Hudson::Entity::Component*>::ActionType::ADD:
        if (behaviour != nullptr) behaviour->OnCreate();
        break;

    case Common::DeferredObjectSet<Hudson::Entity::Component*>::ActionType::REMOVE:
        if (behaviour != nullptr) behaviour->OnDestroy();
        component->_parent = nullptr;
        delete component;
        break;
    }
}

Hudson::Entity::GameObject::GameObject() : _scene(nullptr)
{
    _components.SetCallback([&](auto action)
        {
            this->OnQueueUpdate(action);
        });
}

Hudson::Entity::GameObject::~GameObject()
{
    // Delete all
    auto& components = _components.Get();
    for (auto component : components)
    {
        // Check we didn't somehow end up holding another object's component
        if (component->_parent != this)
        {
            std::stringstream msg;
            msg << "Found reference to component owned by other object while destroying " << this;
            Util::Debug::LogError(msg.str());
        }
        else
        {
            delete component;
            _components.Remove(component);
        }
    }
}

std::set<Hudson::Entity::Component*> Hudson::Entity::GameObject::GetAllComponents()
{
    return _components.Get();
}

Hudson::Entity::Component* Hudson::Entity::GameObject::AddComponent(Component* component)
{
    // Check that the component is not owned by another object
    if (component->_parent != nullptr && component->_parent != this)
    {
        std::stringstream msg;
        msg << "Cannot add component " << component << " to object " << this << " that already belongs to object " << component->_parent;
        Util::Debug::LogError(msg.str());
        return component;
    }

    // Queue for addition
    _components.Add(component);
    component->_parent = this;

    return component;
}

Hudson::Entity::Component* Hudson::Entity::GameObject::RemoveComponent(Component* component)
{
    // Check that we own the component
    if (component->_parent != this)
    {
        // TODO Util::Debug::LogError("Cannot remove a component that does not belong to this object!");
        std::stringstream msg;
        msg << "Cannot remove component " << component << " from object " << this << " that belongs to object " << component->_parent;
        Util::Debug::LogError(msg.str());
        return component;
    }

    // Queue component for removal
    _components.Remove(component);

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
    for (auto component : GetAllComponents())
    {
        component->_parent = this;

        auto behaviour = dynamic_cast<Behaviour*>(component);
        if (behaviour)
        {
            behaviour->OnCreate();
        }
    }
}

void Hudson::Entity::GameObject::OnSceneTick(const double dt)
{
    _isCurrentlyTicking = true;

    // Run cached component adds/removals
    _components.Update();

    // Update behaviours
    for (const auto& component : _components.Get())
    {
        auto behaviour = dynamic_cast<Entity::Behaviour*>(component);
        if (behaviour != nullptr)
        {
            // TODO: exception catching -> stacktrace?
            behaviour->OnTick(dt);
        }
    }

    _isCurrentlyTicking = false;
}

void Hudson::Entity::GameObject::OnSceneRemove()
{
    for (auto behaviour : this->GetComponents<Behaviour>())
    {
        behaviour->OnDestroy();
    }
}

Hudson::World::Scene* Hudson::Entity::GameObject::GetScene() const
{
    return _scene;
}

uint32_t Hudson::Entity::GameObject::GetSerialID()
{
    return _serialId;
}

void Hudson::Entity::GameObject::FromJson(const nlohmann::json& j)
{
    Hudson::Common::ComponentRegistry* componentRegistry = Hudson::Common::Engine::GetInstance()->GetComponentRegistry();

    _name = j.at("name");
    _serialId = j.at("id");
    _transform = j.at("transform");
    _components = {};

    for (auto&& componentJson : j.at("components"))
    {
        // check component is registered
        std::string typeName = componentJson.at("type");
        if (!componentRegistry->IsComponentRegistered(typeName))
        {
            Hudson::Util::Debug::LogError(std::format("Could not find component registered as type '{}'!", typeName));
            continue;
        }

        // construct and initialise object using component registry
        Component* comp = componentRegistry->CreateComponentFromJson(componentJson);
        _components.Add(comp);
    }

    _components.Update();
}

void Hudson::Entity::GameObject::ToJson(nlohmann::json& j) const
{
    // TODO: all of this
    j["name"] = _name;
    j["id"] = _serialId;
    j["transform"] = _transform;
    j["components"] = nlohmann::json::array();

    for (auto&& component: _components.Get())
    {
        nlohmann::json compJson;
        compJson["type"] = component->GetTypeName();
        // TODO: check against component registry
        component->ToJson(compJson["data"]);
        j["components"].push_back(compJson); 
    }
}
