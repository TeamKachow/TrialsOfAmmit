#include "Behaviour.h"

#include "../Common/Engine.h"

Hudson::Common::EngineAccessors* Hudson::Entity::Behaviour::GetEngineAccessorDelegate()
{
    return Common::Engine::GetInstance();
}

Hudson::Entity::Behaviour::Behaviour(const char* name) : Component(name)
{
}
