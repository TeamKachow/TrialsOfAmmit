#include "ComponentRegistry.h"

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
    // Register<Render::SpriteComponent>("Sprite Component");
    // Register<Physics::PhysicsComponent>("Physics Component");
    // Register<Physics::ColliderComponent>("Box Collider");



    // in <game-editor>/main.cpp
    //Register<AIBehaviour>()
    //Register<EmeneyBehaviour>()
    //Register<PlayersBehaviour>()
    //Register<PotatoBehaviour>()
    //new Editor(componentRegistry)

}
