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
