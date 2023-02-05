#include "Player.h"
#include "WeaponDisplayUI.h"

Player::Player(Hudson::Render::SpriteComponent* playerSprite, double animSpeed) : Behaviour("PlayerTest")
{
	_playerSprite = playerSprite;
	_playerAnimSpeed = 0.2;
	_playerDirection = Stopped;
	_playerFacingDirection = Stopped;
	_attackTimer = 0;
	_gridX = _playerSprite->GetGridPos().x;
	_gridY = _playerSprite->GetGridPos().y;
	_playerMovementSpeed = 100.0;
	_godMode = false;

}

Player::~Player()
{
	
}

void Player::OnCreate()
{
	_currentScene = _parent->GetScene();
	_playersWeapon = &_axe;
	CreateWeaponUI();
}

void Player::TakeDamage(float _damageTaken)//TODO Add Damage Features -> FLASHING AND PHYSICs
{
	if (_godMode == false)
	{
		_playerHealth = _playerHealth - _damageTaken;
		_playerSprite->SetColor(glm::vec3(1, 0, 0));
		if (_playerHealth <= 0)
		{
			OnDeath();
		}
	}
}


void Player::OnTick(const double& dt)
{

	if(_inputManager.getActionState("Up")) //Key Checks
	{
		_playerDirection = Up;
		_playerFacingDirection = Up;
	}
	else if (_inputManager.getActionState("Down"))
	{
		_playerDirection = Down;
		_playerFacingDirection = Down;
	}
	else if (_inputManager.getActionState("Right"))
	{
		_playerDirection = Right;
		_playerFacingDirection = Right;
	}
	else if (_inputManager.getActionState("Left"))
	{
		_playerDirection = Left;
		_playerFacingDirection = Left;
	}
	else
	{
		_playerDirection = Stopped;
	}


	_attackTimer += dt;
	if (_inputManager.getActionState("Attack"))
	{
		if (_attackTimer > _playersWeapon->_weaponAttackSpeed) //Checks the attack Timer of the weapon
		{
			Fire();
			_attackTimer = 0;
		}
		
	}

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
	_playerSprite->SetColor(glm::vec3(1, 1, 1));

}

void Player::Fire() //Attack Uses facing Direction not the way the player is moving 
{
	_playersWeapon->Attack(_playerFacingDirection, _parent->GetTransform().pos, _currentScene);

}

void Player::MoveUp() //Movement depending on _playerDirection
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 3;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(0, -_playerMovementSpeed));
}

void Player::MoveDown()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 0;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(0, _playerMovementSpeed));
}

void Player::MoveRight()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 2;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(_playerMovementSpeed, 0));
}

void Player::MoveLeft()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>();
	_gridY = 1;
	AnimMove();
	_playerPhysics->SetVelocity(glm::vec2(-_playerMovementSpeed, 0));
}

void Player::StopMove()
{
	_playerPhysics = _parent->GetComponent<Hudson::Physics::PhysicsComponent>(); //Stops the player Moving
	_playerPhysics->SetVelocity(glm::vec2(0, 0));
	if (_playerFacingDirection == Right || _playerFacingDirection == Down) //When Stop player the player stadning still frame
	{
		_gridX = 0;
	}
	else
	{
		_gridX = 2;
	}
	_playerAnimTimer = 0;
	
}

void Player::CreateWeaponUI()
{
	Hudson::Entity::GameObject* WeaponUIPickup = new Hudson::Entity::GameObject();
	WeaponUIPickup->AddComponent(new WeaponDisplayUI(glm::vec2(1450.0f, 25.0f), WeaponUIPickup, _currentScene, _parent->GetComponent<Player>()));
	_currentScene->AddObject(WeaponUIPickup);
}

void Player::AnimMove()//General move through sprite sheet function
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

void Player::OnDeath()
{
	std::cout << "PLayer Dead" << "\n";
}


void Player::OnDestroy()
{
}

void Player::DrawPropertyUI()
{
	if(ImGui::Button("Axe"))
	{
		_playersWeapon = &_axe;
	}
	if (ImGui::Button("Kopesh"))
	{
		_playersWeapon = &_khopesh;
	}
	if (ImGui::Button("Spear"))
	{
		_playersWeapon = &_spear;
	}
	if (ImGui::Button("Bow"))
	{
		_playersWeapon = &_bow;
	}
	if (ImGui::Button("SlingShot"))
	{
		_playersWeapon = &_slingshot;
	}

}
