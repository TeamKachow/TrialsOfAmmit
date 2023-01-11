#include "Scene.h"

const std::vector<Hudson::Entity::GameObject*>& Hudson::World::Scene::GetObjects() const
{
    return _objects;
}

const std::string&  Hudson::World::Scene::GetName() const
{
    return _name;
}
