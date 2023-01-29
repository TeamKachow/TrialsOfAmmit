#include "Player.h"

void Player::Fire()
{
}

Player::Player(Hudson::Render::SpriteComponent* playerSprite, double animSpeed) : Behaviour("PlayerTest")
{
	_playerSprite = playerSprite;
	_playerAnimSpeed = 0.1;
	playerDirection = Down;
	_playerFireRate = 0.8;
	_testTimer = 0;
}

Player::~Player()
{
}

void Player::OnCreate()
{
}

void Player::OnTick(const double& dt)
{
	_testTimer += dt;
	_playerAnimTimer += dt;
	if (_testTimer >= _playerFireRate)
	{
		std::vector<Hudson::Physics::PhysicsComponent*> _playerPhysics = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();
		if (!_playerPhysics.empty())
		{
			auto _playerPhysic =  _playerPhysics.front();
		}
		_testTimer -= _playerFireRate;
	}


		//Todo Check way the player is walking
	
	if (_playerAnimTimer >= _playerAnimSpeed)
	{
		_playerAnimTimer -= _playerAnimSpeed;
		int _gridX = _playerSprite->GetGridPos().x;
		int _gridY = _playerSprite->GetGridPos().y;

		//std::cout << playerDirection << "\n";
		glm::vec2 spriteGridSize = _playerSprite->GetGridSize();
		if (_gridX < spriteGridSize.x - 1)
		{
			_gridX ++;
		}
		else
		{
			_gridX = 0;
			_gridY++;
		}
		if (_gridY > spriteGridSize.y - 1)
		{
			_gridY = 0;
		}
		_playerSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	}
	
	




	
}

void Player::OnDestroy()
{
}

void Player::DrawPropertyUI()
{
}
