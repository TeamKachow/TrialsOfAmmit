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
    for (const auto& object : _objects)
    {
        for (const auto& component : object->_components)
        {
            // TODO: ITickable instead of Behaviour?
            Entity::Behaviour* behaviour = reinterpret_cast<Entity::Behaviour*>(component);
            if (behaviour != nullptr)
            {
                behaviour->OnTick(dt);
            }

            // TODO: cache components into list to prevent multiple re-iterations in physics/graphics
            // TODO: OR consider making systems register a visitor that we call here?
        }
    }
}
