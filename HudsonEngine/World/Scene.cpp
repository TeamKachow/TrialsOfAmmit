#include "../World/Scene.h"

#include "../Entity/Behaviour.h"
#include "../Entity/GameObject.h"
#include "../Util/Debug.h"

const std::set<Hudson::Entity::GameObject*>& Hudson::World::Scene::GetObjects() const
{
    return _objects;
}

const std::string& Hudson::World::Scene::GetName() const
{
    return _name;
}

void Hudson::World::Scene::Tick(const double dt) const
{
    // Don't tick if inactive
    if (!_active)
        return;
    
    for (const auto& object : _objects)
    {
        for (const auto& component : object->_components)
        {
            auto behaviour = dynamic_cast<Entity::Behaviour*>(component);
            if (behaviour != nullptr)
            {
                // TODO: exception catching -> stacktrace?
                behaviour->OnTick(dt);
            }
        }
    }
}

Hudson::Entity::GameObject* Hudson::World::Scene::AddObject(Entity::GameObject* object)
{
    // TODO: THIS MUST CHECK FOR DUPLICATES EVENTUALLY
    if (object->_scene != nullptr)
    {
        std::stringstream msg;
        msg << "Trying to add object " << object << " to scene " << this << ", but object is already in scene " << object->_scene << "! Not adding to new scene.";
        Hudson::Util::Debug::LogError(msg.str());
        return object;
    }

    _objects.emplace(object);
    object->_scene = this;
    object->OnSceneAdd();

    return object;
}

Hudson::Entity::GameObject* Hudson::World::Scene::RemoveObject(Entity::GameObject* object)
{
    if (!_objects.contains(object))
    {
        std::stringstream msg;
        msg << "Tried to remove object " << object << " from scene " << this << ", but scene was not holding object! Object's scene: " << object->_scene;
        Hudson::Util::Debug::LogError(msg.str());
    }

    if (object->_scene == nullptr)
    {
        std::stringstream msg;
        msg << "Tried to remove object " << object << " from scene " << this << ", but object thought it was in scene " << object->_scene;
        Hudson::Util::Debug::LogError(msg.str());
    }

    _objects.erase(object);
    object->_scene = nullptr;

    return object;
}

void Hudson::World::Scene::SetName(const std::string& name)
{
    _name = name;
}

bool Hudson::World::Scene::IsActive() const
{
    return _active;
}

void Hudson::World::Scene::SetActive(bool active)
{
    _active = active;
}

bool Hudson::World::Scene::IsRendering() const
{
    return _rendering;
}

void Hudson::World::Scene::SetRendering(bool rendering)
{
    _rendering = rendering;
}
