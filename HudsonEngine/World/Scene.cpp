#include "Scene.h"

#include "../Entity/Behaviour.h"
#include "../Entity/GameObject.h"

const std::vector<Hudson::Entity::GameObject*>& Hudson::World::Scene::GetObjects() const
{
    return _objects;
}

const std::string& Hudson::World::Scene::GetName() const
{
    return _name;
}

void Hudson::World::Scene::Tick(const double dt) const
{
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

void Hudson::World::Scene::AddObject(Entity::GameObject* object)
{
    // TODO: THIS MUST CHECK FOR DUPLICATES EVENTUALLY
    _objects.push_back(object);
}
