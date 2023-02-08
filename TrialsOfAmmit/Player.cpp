#include "Player.h"
#include "WeaponDisplayUI.h"
#include "AbilityDisplayUI.h"
#include "PlayerHealthUI.h"
#include "PickupBehaviour.h"
#include "Rooms/Room.h"

Player::Player(glm::vec2 spawnPos) : Behaviour("PlayerTest")
{
	_maxHealth = 100;
	_playerHealth = _maxHealth;
	_deathTimer = 0;
	_deathAnim = 0.4;
	_deathGridX;
	_playerAnimSpeed = 0.2;
	_playerDirection = Stopped;
	_playerFacingDirection = Stopped;
	_attackTimer = 0;
	_playerMovementSpeed = 125.0;
	_godMode = false;
	_isDead = false;
	_isDamaged = false;
	_playerDamageMod = 1;
	_spawnPos = spawnPos;

	_isHittingUp = false;
	_isHittingDown = false;
	_isHittingRight = false;
	_isHittingLeft = false;

	_moveX = 0;
	_moveY = 0;

}

Player::~Player()
{
	
}

void Player::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_playerSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Player"));
	_playerSprite->SetGridSize(glm::vec2(3, 4));
	_playerSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_playerSprite->SetDepthOrder(10);
	playerCollider = new Hudson::Physics::ColliderComponent();
	playerPhysics = new Hudson::Physics::PhysicsComponent();
	playerPhysics->SetMass(1.0f);
	playerPhysics->SetForce(glm::vec2(0, 0));
	playerPhysics->SetAcceleration(glm::vec2(0, 0), true);
	playerPhysics->SetVelocity(glm::vec2(0, 0));

	_parent->AddComponent(_playerSprite);
	_parent->AddComponent(playerPhysics);
	_parent->AddComponent(playerCollider);

	_gridX = _playerSprite->GetGridPos().x;
	_gridY = _playerSprite->GetGridPos().y;

	_parent->GetTransform().pos = _spawnPos;
	_currentScene = _parent->GetScene();
	_playersWeapon = &_axe;
	_parent->AddComponent(new PickupBehaviour());
	_parent->AddComponent(new AbilityHolder());
	CreateUI();
	HealthBarUI();
}

//Function the Passive Mods will access to change the player Stats
void Player::PassiveAddMaxHealth(float additionalHealth)
{
	std::cout << "Added Health" << "\n";
	_maxHealth = _maxHealth + additionalHealth;
	_playerHealth = _playerHealth + additionalHealth;
}

void Player::PassiveAddSpeed(float additionalSpeed)
{
	std::cout << "Added Speed" << "\n";
	_playerMovementSpeed = _playerMovementSpeed + additionalSpeed;
}

void Player::PassiveAddDamageMod(float additionalDamage)
{
	std::cout << "Added Damage" << "\n";
	_playerDamageMod = _playerDamageMod + additionalDamage;
}

void Player::TakeDamage(float _damageTaken)
{
	if (_godMode == false)
	{
		_playerHealth = _playerHealth - _damageTaken;
		_playerSprite->SetColor(glm::vec3(1, 0, 0));
		_isDamaged = true;
		if (_playerHealth <= 0)
		{
			OnDeath();
			_isDead = true;
		}
	}
}


void Player::OnTick(const double& dt)
{
	_isHittingUp = false;
	_isHittingDown = false;
	_isHittingLeft = false;
	_isHittingRight = false;
	WallCollisions();
	
	

	if (_isDamaged)
	{
		_playerSprite->SetColor(glm::vec3(1, 1, 1));
		_isDamaged = false;
	}

	if (_isDead)
	{
		_deathTimer += dt;
		if (_deathTimer >= _deathAnim)
		{
			GraveSprite->SetGridPos(glm::vec2(_deathGridX, 0));
			_deathTimer = 0;
			_deathGridX += 1;
			if (_deathGridX >= 3)
			{
				_isDead = false;
				_deathGridX = 0;
			}
		}
	}

	if(_inputManager.getActionState("Up"))
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
		if (_attackTimer > _playersWeapon->_weaponAttackSpeed)
		{
			Fire();
			_attackTimer = 0;
		}
		
	}

	switch (_playerDirection)
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
	default:;
	}
	
	_lastFramePos = _parent->GetTransform().pos;

	_playerAnimTimer += dt;
	_playerSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	
	//_playerSprite->SetColor(glm::vec3(1, 1, 1)); -- oopsie

}

void Player::Fire() //Attack Uses facing Direction not the way the player is moving 
{
	_playersWeapon->Attack(_playerFacingDirection, _parent->GetTransform().pos, _currentScene, _playerDamageMod);
}

void Player::MoveUp() //Movement depending on _playerDirection
{
	if (_isHittingUp == false)
	{
		_gridY = 3;
		AnimMove();
		playerPhysics->SetVelocity(glm::vec2(0, -_playerMovementSpeed));
		
	}
	else
	{
		//StopMove();
		//_parent->GetTransform().pos = (_lastFramePos);
	}
	
}

void Player::MoveDown()
{
	if (_isHittingDown == false)
	{
		_gridY = 0;
		AnimMove();
		playerPhysics->SetVelocity(glm::vec2(0, _playerMovementSpeed));
	}
	else
	{
		//StopMove();
		//_parent->GetTransform().pos = (_lastFramePos);
	}
	
	
}

void Player::MoveRight()
{
	if (_isHittingRight == false)
	{
		_gridY = 2;
		AnimMove();
		playerPhysics->SetVelocity(glm::vec2(_playerMovementSpeed,0));

	}
	else
	{
		//StopMove();
		//
	}

}

void Player::MoveLeft()
{
	if (_isHittingLeft == false)
	{
		_gridY = 1;
		AnimMove();
		playerPhysics->SetVelocity(glm::vec2(-_playerMovementSpeed, 0));
	}
	else
	{
		//StopMove();
		//_parent->GetTransform().pos = (_lastFramePos);
	}
	
}

void Player::StopMove()
{
	playerPhysics->SetAcceleration(glm::vec2(0, 0), true);
	playerPhysics->SetVelocity(glm::vec2(0, 0));
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

void Player::CreateUI()
{
	Hudson::Entity::GameObject* WeaponUIPickup = new Hudson::Entity::GameObject();
	WeaponUIPickup->AddComponent(new WeaponDisplayUI(glm::vec2(1450.0f, 25.0f), _currentScene, _parent->GetComponent<Player>()));
	_currentScene->AddObject(WeaponUIPickup);

	Hudson::Entity::GameObject* AbilityUI= new Hudson::Entity::GameObject();
	AbilityUI->AddComponent(new AbilityDisplayUI(glm::vec2(1350.0f, 25.0f), _currentScene, _parent->GetComponent<Player>()));
	_currentScene->AddObject(AbilityUI);

}

void Player::HealthBarUI()
{
	Hudson::Entity::GameObject* HealthBar = new Hudson::Entity::GameObject();
	HealthBar->AddComponent(new PlayerHealthUI(glm::vec2(25.0f, 25.0f), _currentScene, _parent->GetComponent<Player>()));
	_currentScene->AddObject(HealthBar);
}

void Player::Respawn()
{
	_parent->GetTransform().pos = glm::vec2(500, 500);
	_playerHealth = 100;
	_playersWeapon = new Axe;
}

void Player::WallCollisions()
{
	
	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>(); //TODO Make it so it can only Collide Once
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other != nullptr)
			{
				if (other->GetParent()->GetComponent<Room>() != nullptr)
				{
					Room* _Room = other->GetParent()->GetComponent<Room>();
					if (_Room != nullptr)
					{
						playerPhysics->SetAcceleration(glm::vec2(0, 0), true);
						InverseForce();
					}
				}
				else
				{
					collider->ClearColliding();
					break;
				}
			}
			
		}

	}
}

void Player::InverseForce()
{
	
	switch (_playerFacingDirection)
	{
	case Down:
		_isHittingDown = true;
		playerPhysics->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_playerDirection = Up;
		break;
	case Left:
		_isHittingLeft = true;
		playerPhysics->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_playerDirection = Right;
		break;
	case Right:
		_isHittingRight = true;
		playerPhysics->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_playerDirection = Left;
		break;
	case Up:
		_isHittingUp = true;
		playerPhysics->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_playerDirection = Down;

		break;
	}
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
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	Hudson::Entity::GameObject* Grave = new Hudson::Entity::GameObject;
	GraveSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Grave"));
	GraveSprite->SetGridSize(glm::vec2(3, 1));
	GraveSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	GraveSprite->SetGridPos(glm::vec2(1, 1));
	GraveSprite->SetDepthOrder(2);

	Grave->AddComponent(GraveSprite);
	_currentScene->AddObject(Grave);
	Grave->GetTransform().pos = _parent->GetTransform().pos;
	_parent->GetTransform().pos = glm::vec2(1000, 2000);
	Grave->SetName("Blood");
}


void Player::OnDestroy()
{
}

void Player::DrawPropertyUI()
{
	if (ImGui::Button("Respawn"))
	{
		Respawn();
	}
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
	if (ImGui::Button("Upgrade Weapon"))
	{
		_playersWeapon->UpgradeWeapon(Gold);
	}


}

void Player::FromJson(const nlohmann::json& j)
{

}

void Player::ToJson(nlohmann::json& j)
{

}
