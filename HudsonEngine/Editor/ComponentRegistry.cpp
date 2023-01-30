#include "ComponentRegistry.h"
#include "../Render/SpriteComponent.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/ColliderComponent.h"
#include "../Render/TextComponent.h"

void Hudson::Editor::ComponentRegistry::RegisterEngineComponents()
{
    Register<Render::SpriteComponent>("Sprite");
    Register<Physics::PhysicsComponent>("Physics");
    Register<Physics::ColliderComponent>("Box Collider");
	// Register<Render::TextComponent>("Text");
}

std::vector<Hudson::Editor::ComponentRegistry::Entry>& Hudson::Editor::ComponentRegistry::GetKnownComponents()
{
    return _entries;
}
