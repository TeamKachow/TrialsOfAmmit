#include "Stun.h"


Stun::Stun()
{
	_abilityActiveTime = 2;
	_abilityCoolDownTime = 10;
	_abilityState = ready;
	_abilityType = AT_STUN;
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
			_agent->_aiSprite->SetColor(glm::vec3(0, 0, 1));
			// need to make it so that ai can't attack  or player is godmode
		}
	};
	_abilityState = active;
}

void Stun::DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)
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
			_agent->_aiSprite->SetColor(glm::vec3(1, 1, 1));
			// need to make it so that ai can attack again or player isn't godmode
		}
	};
	_abilityState = cooldown;
}
