#include "Roll.h"

Roll::Roll() 
{

}

Roll::~Roll()
{

}

void Roll::OnCreate()
{
	_activeTime = 0.5;
	_cooldownTime = 5;
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
			_player->_playerMovementSpeed = 100;
			//std::cout << "Player movement speed is : " << _player->_playerMovementSpeed << "\n";
			//once timer finished reset speed 
			break;
		}
	};

	//_player->_playerMovementSpeed = _rollSpeed * deltaTime;

}

	// get player's movement stat and multiply by _dashVelocity
	//	PlayerMovement movement = parent.GetComponent<PlayerMovement>();
	//	Rigidbody2D rigidbody = parent.GetComponent < Rigidbody2D();
	//
	//	rigidbody.velocity = movement.movementInput.normalized * dashVelocity;
