#include "Scene.h"

const std::vector<Hudson::Entity::GameObject*>& Hudson::Scene::Scene::GetObjects() const
{
    return _objects;
}

const std::string&  Hudson::Scene::Scene::GetName() const
{
    return _name;
}
