#include "OneUP.h"

OneUP::OneUP()
{
	_abilityActiveTime = 10;
	_abilityCoolDownTime = 50;
	_abilityState = ready;
}

OneUP::~OneUP()
{
}

void OneUP::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			// INSERT CODE HERE . . .

			break;
		}
	};

	_abilityState = active;
}

void OneUP::DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			// INSERT CODE HERE . . .

			break;
		}
	};

	_abilityState = cooldown;
}
