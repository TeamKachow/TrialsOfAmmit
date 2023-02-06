#include "RoomAOE.h"

RoomAOE::RoomAOE()
{
	_abilityActiveTime = 3;
	_abilityCoolDownTime = 7;
}

RoomAOE::~RoomAOE()
{

}

void RoomAOE::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto AllObjects = _currentScene->GetObjects();
	
	for (Hudson::Entity::GameObject* other : AllObjects)
	{
		if (other->GetComponent<AiAgent>() != nullptr)
		{
			_agent = other->GetComponent<AiAgent>(); // maybe make it so when they take widespread dmg, they flash red quickly ???
			_agent->TakeDamage(5);
		}
	};
	_abilityState = active;
}

void RoomAOE::DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto AllObjects = _currentScene->GetObjects();

	for (Hudson::Entity::GameObject* other : AllObjects)
	{
		if (other->GetComponent<AiAgent>() != nullptr)
		{
			_agent = other->GetComponent<AiAgent>();
			_agent->_currentHealth = _enemyCurrentHealth;
		}
	};
	_abilityState = cooldown;
}

