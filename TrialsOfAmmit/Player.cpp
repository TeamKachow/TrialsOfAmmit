#include "Player.h"
#include "WeaponDisplayUI.h"
#include "AbilityDisplayUI.h"
#include "PlayerHealthUI.h"
#include "PickupBehaviour.h"
#include "Rooms/Room.h"
#include "PauseMenu.h"
#include "PlayerReset.h"

Player::Player(glm::vec2 spawnPos) : Behaviour("PlayerTest")
{
	//Player Moving Directions
	_playerDirection = Stopped;
	_playerFacingDirection = Stopped;
	
	//Player Stats
	_maxHealth = 150;
	_playerHealth = _maxHealth;
	_playerMovementSpeed = 125.0;
	_playerDamageMod = 1;
	_attackTimer = 0;
	_playerAnimSpeed = 0.2;
	_spawnPos = spawnPos;

	//Checks
	_godMode = false;
	_isDead = false;
	_isDamaged = false;

	//Pause Menus
	_isPaused = false;

	//Death Vars
	_deathTimer = 0;
	_deathAnim = 0.4;
	_deathGridX = 0;

	//Wall Collisions
	_isHittingUp = false;
	_isHittingDown = false;
	_isHittingRight = false;
	_isHittingLeft = false;

	toPause = false;
}

Player::~Player()
{
	
}

void Player::OnCreate() //The magic is set up here
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

	_pauseScene = new Hudson::World::Scene();
	_pauseScene->SetName("PauseScene");
	_pauseMenu = new Hudson::Entity::GameObject();
	_pauseMenu->AddComponent(new PauseMenu(glm::vec2(232, 200), _parent->GetScene(), _parent->GetComponent<Player>()));
	_pauseScene->AddObject(_pauseMenu);
	GetEngine()->GetSceneManager()->AddScene(_pauseScene);

	_resetScene = new Hudson::World::Scene();
	_resetScene->SetName("ResetScene");
	_resetMenu = new Hudson::Entity::GameObject();
	_resetMenu->AddComponent(new PlayerReset(glm::vec2(232, 200), _parent->GetScene(), _parent->GetComponent<Player>()));
	_resetScene->AddObject(_resetMenu);
	GetEngine()->GetSceneManager()->AddScene(_resetScene);

	_resetText = new Hudson::Render::TextComponent("Fonts\\origa___.ttf", resManager->GetShader("textShader"));
	_resetText->SetText("Press K To Restart");
	_resetText->SetColor(vec3(1, 1, 1));
	_resetText->SetDepthOrder(30);

	_resetTextObj = new Hudson::Entity::GameObject();
	_resetTextObj->AddComponent(_resetText);
	_resetTextObj->SetName("ResetText");
	_resetTextObj->GetTransform().pos = vec2(2000, 2000);
	_resetTextObj->GetTransform().scale = vec2(2, 1);
	_parent->GetScene()->AddObject(_resetTextObj);

	_pauseText = new Hudson::Render::TextComponent("Fonts\\origa___.ttf", resManager->GetShader("textShader"));
	_pauseText->SetText("Pause");
	_pauseText->SetColor(vec3(1, 1, 1));
	_pauseText->SetDepthOrder(30);
	
	PauseText = new Hudson::Entity::GameObject();
	PauseText->AddComponent(_pauseText);
	PauseText->SetName("PauseText");
	PauseText->GetTransform().pos = vec2(500, 200);
	PauseText->GetTransform().scale = vec2(5, 1);
	_parent->GetScene()->AddObject(PauseText);
	_audioMan = GetAudioManager();

	CreateUI();
	HealthBarUI();
}

//Function the Passive Mods will access to change the player Stats when passives are pickup in the pickup behaviour
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

void Player::SetPosition(glm::vec2 Position)
{
	_parent->GetTransform().pos = Position;
}

void Player::TakeDamage(float _damageTaken)
{
	//God Mode For DEBUG and Unity Frames on Roll
	if (_godMode == false)
	{
		_playerHealth = _playerHealth - _damageTaken;
		_playerSprite->SetColor(glm::vec3(1, 0, 0));
		_isDamaged = true;
		if (_playerHealth <= 0)
		{
			_resetTextObj->GetTransform().pos = vec2(232, 200);
			_resetMenu->GetComponent<PlayerReset>()->PauseScene();
			OnDeath();
			_isDead = true;
		}
	}
}


void Player::OnTick(const double& dt)
{
	
	//Wall Collisions Reset once a frame due to the player being pushed back and now not colliding and if they are it will be picked up in the function
	_isHittingUp = false;
	_isHittingDown = false;
	_isHittingLeft = false;
	_isHittingRight = false;
	WallCollisions();
	
	
	//Flashing When Damaged
	if (_isDamaged)
	{
		_playerSprite->SetColor(glm::vec3(1, 1, 1));
		_isDamaged = false;
	}
	//Checking For Death
	if (_isDead)
	{
		_deathTimer += dt;
		if (_deathTimer >= _deathAnim)
		{
			//GraveSprite->SetGridPos(glm::vec2(_deathGridX, 0));
			_deathTimer = 0;
			_deathGridX += 1;
			if (_deathGridX >= 3)
			{
				//Grave->GetTransform().pos = vec2(2000, 2000);
				_isDead = false;
				_deathGridX = 0;
			}
		}
	}

	//Checks for keypress is not it is paused - It works with the pause menus double key check system
	if (_inputManager.getActionState("Pause"))
	{
		if (_isPaused == false)
		{
			PauseText->GetTransform().pos = vec2(232, 200);
			_pauseMenu->GetComponent<PauseMenu>()->PauseScene();
			
			
		}
	}
	else
	{
		PauseText->GetTransform().pos = vec2(INT64_MAX, INT64_MAX);
		_isPaused = false;
	}



	//Keypresses
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

	//Attack Timer / Function using the current weapon stats
	_attackTimer += dt;
	if (_inputManager.getActionState("Attack"))
	{
		if (_attackTimer > _playersWeapon->_weaponAttackSpeed)
		{
			_audioMan->playSound("audio/PlayerMeleeAttackSwing.wav", false, 0);
			Fire();
			_attackTimer = 0;
		}
		
	}
	switch (_playerDirection) //Switch for the player movement
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
	
	_lastFramePos = _parent->GetTransform().pos; //Saving Last Frame for wall collsions

	_playerAnimTimer += dt; //Calls Anim Calculations
	_playerSprite->SetGridPos(glm::vec2(_gridX, _gridY)); //Sets the Based of the Calcs
	
}

void Player::Fire() //Attack Uses facing Direction not the way the player is moving 
{
	_playersWeapon->Attack(_playerFacingDirection, _parent->GetTransform().pos, _currentScene, _playerDamageMod);
}

void Player::MoveUp() //Movement depending on _playerDirection called once a frame
{
	if (_isHittingUp == false)
	{
		_gridY = 3;
		AnimMove();
		playerPhysics->SetVelocity(glm::vec2(0, -_playerMovementSpeed));
		
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
}

void Player::MoveRight()
{
	if (_isHittingRight == false)
	{
		_gridY = 2;
		AnimMove();
		playerPhysics->SetVelocity(glm::vec2(_playerMovementSpeed,0));

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

}

void Player::StopMove()//When the player isnt moving sets sprite sheet and stops them
{
	playerPhysics->SetAcceleration(glm::vec2(0, 0), true);
	playerPhysics->SetVelocity(glm::vec2(0, 0));
	if (_playerFacingDirection == Right || _playerFacingDirection == Down) 
	{
		_gridX = 0;
	}
	else
	{
		_gridX = 2;
	}
	_playerAnimTimer = 0;
	
}

void Player::CreateUI() //Both functions are to make the UI of the player Stats
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
	HealthBar->AddComponent(new PlayerHealthUI(glm::vec2(10.0f, 10.0f), _currentScene, _parent->GetComponent<Player>()));
	_currentScene->AddObject(HealthBar);
}

void Player::Respawn() //DEBUG RESPAWN PLAYER
{
	
	_isDead = false;
	_parent->GetTransform().pos = glm::vec2(750, 500);
	_playerHealth = _maxHealth;
	_playersWeapon = new Axe;

	_resetTextObj->GetTransform().pos = vec2(2000, 2000);
}

void Player::WallCollisions()//Checks the First collision box on the player to see if they are hitting walls
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
				//std::cout << other->GetParent()->GetName() << "\n";
				if (other->GetParent()->GetComponent<Room>() != nullptr)
				{
					Room* _Room = other->GetParent()->GetComponent<Room>();
					if (_Room != nullptr)
					{
						playerPhysics->SetAcceleration(glm::vec2(0, 0), true);
						InverseForce();
						break;
					}
				}
			}
			
		}
		collider->ClearColliding();

		collider->ClearColliding();
	}
}

void Player::InverseForce()//Called When colliding on walls and then stops the player moving does this by calling opersite force and making back to last frame pos to stop the player colliding
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

void Player::AnimMove()//Animation is based of player moving and called when it is
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

void Player::OnDeath() //Makes the graves stone and animates after
{
	/*Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	Grave = new Hudson::Entity::GameObject;
	GraveSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Grave"));
	GraveSprite->SetGridSize(glm::vec2(3, 1));
	GraveSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	GraveSprite->SetGridPos(glm::vec2(1, 1));
	GraveSprite->SetDepthOrder(2);

	Grave->AddComponent(GraveSprite);
	_currentScene->AddObject(Grave);
	Grave->GetTransform().pos = _parent->GetTransform().pos;
	_parent->GetTransform().pos = glm::vec2(1000, 2000);
	Grave->SetName("Grave");*/
}


void Player::OnDestroy()
{
}

void Player::DrawPropertyUI() //IMGUI DEBUG TOOLS
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
