#include "Player.h"

Player::Player(Hudson::Render::SpriteComponent* playerSprite, double animSpeed) : Behaviour("PlayerTest")
{
	_playerSprite = playerSprite;
	_playerAnimSpeed = 0.5;
	_playerDirection = Right;
	_playerFireRate = 0.8;
	_testTimer = 0;
	_gridX = _playerSprite->GetGridPos().x;
	_gridY = _playerSprite->GetGridPos().y;

}

Player::~Player()
{
	
}

void Player::OnCreate()
{
	_currentScene = _parent->GetScene();

	std::cout<< _playersWeapon->_weaponName << "\n";
	_playersWeapon = &_khopesh;
	std::cout << _playersWeapon->_weaponName << "\n";
	Fire();

}

void Player::TakeDamage(float _damageTaken)
{
	_playerHealth = _playerHealth - _damageTaken;
}


void Player::OnTick(const double& dt)
{
	switch(_playerDirection)
	{
	case Down:
		MoveDown();
		break;
	case Left:
		MoveLeft();
		break;
	case Right:
		MoveRight();
		break;
	case Up:
		MoveUp();
		break;
	case Stopped:
		StopMove();
		break;
	default: ;
	}

	_playerAnimTimer += dt;
	_playerSprite->SetGridPos(glm::vec2(_gridX, _gridY));

}

void Player::Fire()
{
	_projectile = new Hudson::Entity::GameObject();
	_projectile->AddComponent(new Projectile(_playerDirection, _parent->GetTransform().pos, _currentScene, _projectile));
}

void Player::MoveUp()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 3;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(0, -45));
}

void Player::MoveDown()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 0;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(0, 45));
}

void Player::MoveRight()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 2;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(45, 0));
}

void Player::MoveLeft()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 1;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(-45, 0));
}

void Player::StopMove()
{
}

void Player::AnimMove()
{
	if (_playerAnimTimer >= _playerAnimSpeed)
	{
		_playerAnimTimer -= _playerAnimSpeed;

		glm::vec2 spriteGridSize = _playerSprite->GetGridSize();

		_gridX++;

		if (_gridX > spriteGridSize.x - 1)
		{
			_gridX = 0;
		}

	}
}


void Player::OnDestroy()
{
}

void Player::DrawPropertyUI()
{
	if(ImGui::Button("Right"))
	{
		_playerDirection = Right;
	}
	if (ImGui::Button("Left"))
	{
		_playerDirection = Left;
	}
	if (ImGui::Button("Down"))
	{
		_playerDirection = Down;
	}
	if (ImGui::Button("Up"))
	{
		_playerDirection = Up;
	}
	if (ImGui::Button("Fire"))
	{
		Fire();
	}
}
