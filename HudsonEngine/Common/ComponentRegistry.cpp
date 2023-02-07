#include "ComponentRegistry.h"
#include "../Render/SpriteComponent.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/ColliderComponent.h"
#include "../Render/TextComponent.h"

void Hudson::Common::ComponentRegistry::RegisterEngineComponents()
{
    Register<Render::SpriteComponent>("Sprite");
    Register<Physics::PhysicsComponent>("Physics");
    Register<Physics::ColliderComponent>("Box Collider");
	Register<Render::TextComponent>("Text");
}

std::map<std::string, Hudson::Common::ComponentRegistry::Entry>& Hudson::Common::ComponentRegistry::GetKnownComponents()
{
    return _entries;
}

bool Hudson::Common::ComponentRegistry::IsComponentRegistered(std::string& name)
{
    return _entries.contains(name);
}

Hudson::Entity::Component* Hudson::Common::ComponentRegistry::CreateEmptyComponent(std::string name)
{
    if (!IsComponentRegistered(name))
        throw std::exception(std::format("No component type registered for type name '{}'", name).c_str());

    return _entries[name].constructor();
}

Hudson::Entity::Component* Hudson::Common::ComponentRegistry::CreateComponentFromJson(const nlohmann::json& j)
{
    std::string name = j.at("type");
    Entity::Component* component = CreateEmptyComponent(name);

    try
    {
        component->FromJson(j);
    }
    catch (std::exception& e)
    {
        Hudson::Util::Debug::LogError(std::format("Could not fully deserialize component of type {}:\n    {}", name, e.what()));
    }

    return component;
}
