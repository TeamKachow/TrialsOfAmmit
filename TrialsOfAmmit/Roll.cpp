#include "Roll.h"

Roll::Roll() 
{
	_player = nullptr;
	//_activeTime = 0.5;
	_activeTime = 5;
	_cooldownTime = 5;
	_rollSpeed = 100;
}

Roll::~Roll()
{

}

void Roll::OnCreate()
{
	/*
	_activeTime = 0.5;
	_cooldownTime = 5;
	*/
}

void Roll::OnTick(const double& dt)
{

}

void Roll::UseAbility(Hudson::World::Scene* _CurrentPassScene, float deltaTime)
{
	std::cout << "I dodged" << "\n";
	_currentscene = _CurrentPassScene;
	auto _sceneObjects = _currentscene->GetObjects();
	for (Hudson::Entity::GameObject* other: _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			//timer here
			//once timer finished reset speed 
			break;
		}
	};

	// IF ROLL IS ACTIVE, MAKE THE ABILITY DO ITS THING... TRY MAKE THE SWITCH ENUM IN BASICABILITYCLASS AND HAVE IT REFERENCED IN ABILITYHOLDER SO THAT ROLL.CPP CAN USE THAT TO DETERMINE ITS WORK

	float _defaultPlayerMovementSpeed = _player->_playerMovementSpeed;
	
	/*
	if (_activeTime > 0)
	{
		_player->_playerMovementSpeed = _rollSpeed;
		_activeTime -= deltaTime;
	}
	else
	{
		_player->_playerMovementSpeed = _defaultPlayerMovementSpeed;
	}

	while (_activeTime > 0)
	{
		_player->_playerMovementSpeed = _rollSpeed;
		_activeTime -= deltaTime;
	}

	_player->_playerMovementSpeed = _defaultPlayerMovementSpeed;
	*/

}
// ORIGINAL CODE BEFORE TIMER INPUT
/*
void Roll::UseAbility(Hudson::World::Scene* _CurrentPassScene, float deltaTime)
{
	std::cout << "I dodged" << "\n";
	_currentscene = _CurrentPassScene;
	auto _sceneObjects = _currentscene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			//timer here
			_player->_playerMovementSpeed = _rollSpeed;
			//once timer finished reset speed 
			break;
		}
	};

	//_player->_playerMovementSpeed = _rollSpeed * deltaTime;

}
*/

	// get player's movement stat and multiply by _dashVelocity
	//	PlayerMovement movement = parent.GetComponent<PlayerMovement>();
	//	Rigidbody2D rigidbody = parent.GetComponent < Rigidbody2D();
	//
	//	rigidbody.velocity = movement.movementInput.normalized * dashVelocity;
