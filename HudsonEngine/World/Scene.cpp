#include "../World/Scene.h"

#include "../Entity/Behaviour.h"
#include "../Entity/GameObject.h"
#include "../Util/Debug.h"

void Hudson::World::Scene::OnQueueUpdate(Common::DeferredObjectSet<Entity::GameObject*>::Action action)
{
    Entity::GameObject* object = action.first;
    switch (action.second)
    {
    case Common::DeferredObjectSet<Hudson::Entity::GameObject*>::ActionType::ADD:
        object->_scene = this;
        object->OnSceneAdd();
        break;

    case Common::DeferredObjectSet<Hudson::Entity::GameObject*>::ActionType::REMOVE:
        object->OnSceneRemove();
        object->_scene = nullptr;
        delete object;
        break;
    }
}

Hudson::World::Scene::Scene()
{
    _objects.SetCallback([&](auto action)
        {
            this->OnQueueUpdate(action);
        });
}

Hudson::World::Scene::~Scene()
{
    for (auto object : _objects.Get())
    {
        delete object;
    }
}

const std::set<Hudson::Entity::GameObject*>& Hudson::World::Scene::GetObjects() const
{
    return _objects.Get();
}

const std::string& Hudson::World::Scene::GetName() const
{
    return _name;
}

void Hudson::World::Scene::Tick(const double dt)
{
    // Don't tick if inactive
    if (!_active)
        return;

    _isCurrentlyTicking = true;

    // Update all objects in scene
    for (const auto& object : _objects.Get())
    {
        object->OnSceneTick(dt);
    }

    _isCurrentlyTicking = false;
    _objects.Update();
}

Hudson::Entity::GameObject* Hudson::World::Scene::AddObject(Entity::GameObject* object)
{
    if (object->_scene != nullptr)
    {
        std::stringstream msg;
        msg << "Trying to add object " << object << " to scene " << this << ", but object is already in scene " << object->_scene << "! Not adding to new scene.";
        Hudson::Util::Debug::LogError(msg.str());
        return object;
    }

    _objects.Add(object);

    return object;
}

Hudson::Entity::GameObject* Hudson::World::Scene::RemoveObject(Entity::GameObject* object)
{
    if (!_objects.Get().contains(object))
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

    _objects.Remove(object);

    return object;
}

uint32_t Hudson::World::Scene::GetSerialID()
{
    return _serialId;
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
