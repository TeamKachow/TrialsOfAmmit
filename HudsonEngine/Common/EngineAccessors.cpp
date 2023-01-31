#include "EngineAccessors.h"

#include "Engine.h"

InputManager* Hudson::Common::EngineAccessors::GetInputManager()
{
    return GetEngine()->GetInputManager();
}

Hudson::Render::Renderer* Hudson::Common::EngineAccessors::GetRenderer()
{
    return GetEngine()->GetRenderer();
}

Hudson::Physics::PhysicsManager* Hudson::Common::EngineAccessors::GetPhysicsManager()
{
    return GetEngine()->GetPhysicsManager();
}

Hudson::World::SceneManager* Hudson::Common::EngineAccessors::GetSceneManager()
{
    return GetEngine()->GetSceneManager();
}

Hudson::Common::Engine* Hudson::Common::EngineAccessors::GetEngine()
{
    return GetEngineAccessorDelegate()->GetEngine();
}
