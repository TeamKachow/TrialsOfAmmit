#include "Stun.h"


Stun::Stun()
{
	_abilityActiveTime = 2;
	_abilityCoolDownTime = 10;
	_abilityState = ready;
}

Stun::~Stun()
{
}

void Stun::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto AllObjects = _currentScene->GetObjects();

	for (Hudson::Entity::GameObject* other : AllObjects)
	{
		if (other->GetComponent<AiAgent>() != nullptr)
		{
			_agent = other->GetComponent<AiAgent>();
			_agent->_maxSpeed = 0;
		}
	};
	_abilityState = active;
}

void Stun::DeactiveAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto AllObjects = _currentScene->GetObjects();

	for (Hudson::Entity::GameObject* other : AllObjects)
	{
		if (other->GetComponent<AiAgent>() != nullptr)
		{
			_agent = other->GetComponent<AiAgent>();
			_agent->_maxSpeed = 35;
		}
	};
	_abilityState = cooldown;
}
