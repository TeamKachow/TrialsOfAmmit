#include "Roll.h"

Roll::Roll() 
{
	_abilityActiveTime = 0.2;
	_abilityCoolDownTime = 5;
	_abilityState = ready;

	_rollSpeed = 500;
	_defaultSpeed = 100;
	
}

Roll::~Roll()
{

}

void Roll::UseAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			_player->_playerMovementSpeed = _rollSpeed;
			_player->_godMode = true;
		
			break;
		}
	};
	
	_abilityState = active;

}

void Roll::DeactiveAbility(Hudson::World::Scene* _CurrentPassScene)
{
	Hudson::World::Scene* _currentScene;
	_currentScene = _CurrentPassScene;
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			_player->_playerMovementSpeed = _defaultSpeed;
			_player->_godMode = false;
			break;
		}
	};

	_abilityState = cooldown;
}
