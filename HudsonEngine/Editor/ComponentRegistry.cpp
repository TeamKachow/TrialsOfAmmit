#include "ComponentRegistry.h"

#include "../Render/TextComponent.h"

namespace Hudson
{
	namespace Physics
	{
		class ColliderComponent;
		class PhysicsComponent;
	}
}

namespace Hudson
{
	namespace Render
	{
		class SpriteComponent;
	}
}

void Hudson::Editor::ComponentRegistry::RegisterEngineComponents()
{
    // TODO:
    // Register<Render::SpriteComponent>("Sprite");
    // Register<Physics::PhysicsComponent>("Physics");
    // Register<Physics::ColliderComponent>("Box Collider");
	// Register<Render::TextComponent>("Text");

}

std::vector<Hudson::Editor::ComponentRegistry::Entry>& Hudson::Editor::ComponentRegistry::GetKnownComponents()
{
    return _entries;
}
