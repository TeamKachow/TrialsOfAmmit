#include "AiAgent.h"
#include "PickupAbilitys.h"
#include "PassivePickups.h"
#include "Rooms/Room.h"
#include "MeleeCollider.h"
AiAgent::AiAgent(vec2 spawnPos) : Behaviour("AiBehavior")
{
	_aiAnimSpeed = 0.4;
	_spawnPosition = spawnPos;
}

void AiAgent::OnCreate()
{
	//sets up sprite
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_aiSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
	_aiSprite ->SetGridSize(glm::vec2(3, 4));
	_aiSprite->SetDepthOrder(8);
	_parent->AddComponent(_aiSprite);

	//sets up collider
	_aiCollider = new Hudson::Physics::ColliderComponent();
	_parent->AddComponent(_aiCollider);
	_aiColliderWall = new Hudson::Physics::ColliderComponent();
	_parent->AddComponent(_aiColliderWall);

	//sets up physics componant
	_aiPhysicsComponent = new Hudson::Physics::PhysicsComponent();
	_aiPhysicsComponent->SetMass(1.0f);
	_aiPhysicsComponent->SetForce(glm::vec2(10.0, 0));
	_aiPhysicsComponent->SetAcceleration(glm::vec2(10, 0), true);
	_aiPhysicsComponent->SetVelocity(glm::vec2(0, 0));

	//adds objects to the parent game object 
	_parent->AddComponent(_aiPhysicsComponent);
	_parent->SetName("AIAgent");
	_parent->GetTransform().pos = _spawnPosition;

	//Set up of health and damage
	_maxHealth = 100.0f;
	_meleeDamage = 10.0f;
	_maxSpeed = 35;
	_maxRange = 200;
	_minRange = -200;
	_distanceFromPlayer = 10000;
	_currentHealth = _maxHealth;
	_alive = true;

	//sets to true to chose a new point
	_arrive = true;

	//need to add _position
	_target = vec2(0, 0);

	//Starting state
	_currentState = WANDER;
	_attackTimer = 1.5;
	_aiAnimDeathTimer = 0;
	_isDamaged = false;

	//sets eatch physics opertaion 
	_velocity = _aiPhysicsComponent->GetVelocity();
	_mass = _aiPhysicsComponent->GetMass();
	_acceleration = _aiPhysicsComponent->GetAcceleration();

	//adds sprite from resManager to the _AiDeathSprite
	_aiDeathSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Blood"));
	Blood = new Hudson::Entity::GameObject;

	//gets the player from the current scene 
	_currentScene = _parent->GetScene();
	auto _sceneObjects = _currentScene->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			break;
		}
	}
}

AiAgent::~AiAgent()
{

}

void AiAgent::OnDestroy()
{

}

void AiAgent::OnTick(const double& dt)
{
	if (_isDamaged)
	{
		_aiSprite->SetColor(vec3(1, 1, 1));
		_isDamaged = false;
	}
	Animate(dt);
	//lets the Ai chose a new destinations before it has reached the current higher = less jitter
	if (_distanceFromTarget < 100)
	{
		_arrive = true;
	}
	GetPlayerPos();
	//finite state machine 
	switch (_currentState)
	{
	case SEEK:
		SetPlayerPos();
		_moveForce = Seek(_target);
		Move(dt);
		break;
	case WANDER:
		if (_parent->GetTransform().pos != _target)
		{
			if (_arrive == true)
			{
				RandomTargetSelector();
			}
			_moveForce = Wander(_target);
			Move(dt);
		}
		break;
	case ATTACK:
		_attackTimer += dt;
		if (_attackTimer > _aiWeapon->_weaponAttackSpeed) //Checks the attack Timer of the weapon
		{
			AiAttack();
		}
		break;
	case DEAD:

		if (_alive)
		{
			_aiDeathSprite->SetGridSize(glm::vec2(3, 1));
			_aiDeathSprite->SetGridPos(glm::vec2(1, 1));
			_aiDeathSprite->SetDepthOrder(9);
			_parent->RemoveComponent(_aiSprite);
			Blood->AddComponent(_aiDeathSprite);
			_currentScene->AddObject(Blood);
			Blood->GetTransform().pos = _parent->GetTransform().pos;
			_maxSpeed = 0;
			_alive = false;
		}	
		_aiAnimDeathTimer += dt;	
		if (_aiAnimDeathTimer > 0.5)
		{
			AiDead();
		}
		_currentState = DEAD;
		break;
	default:

		break;
	}

	if (_distanceFromPlayer < 300.0f && _distanceFromPlayer > 100.0f && _alive)
	{
		_currentState = SEEK;
	}
	else if (_distanceFromPlayer < 100.0f && _alive)
	{
		_attackTimer += dt;
		if (_attackTimer > _aiWeapon->_weaponAttackSpeed) //Checks the attack Timer of the weapon
		{
			//auto _aiPhysics = _aiPhysicsComponent.front();
			_velocity = vec2(0, 0);
			_acceleration = vec2(0, 0);
			_aiPhysicsComponent->SetAcceleration(_acceleration, false);
			_aiPhysicsComponent->SetVelocity(_velocity);
			_currentState = ATTACK;
			_attackTimer = 0;
		}
	}
	else if (_distanceFromPlayer > 300.0f && _alive)
	{
		_currentState = WANDER;
	}
	_lastFramePos = _parent->GetTransform().pos;

}

void AiAgent::CollisionCheck()
{
	//TODO: Remove code and change to check for collision with the wall 
	
	// pushes Ai back and choses a new destination when trying to leave the map bounds 
	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>(); //TODO Make it so it can only Collide Once
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(1);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other != nullptr)
			{
				if (other->GetParent()->GetComponent<MeleeCollider>() == nullptr)
				{
					collider->ClearColliding();
				}
				if (other->GetParent()->GetComponent<Room>() != nullptr)
				{
					Room* _Room = other->GetParent()->GetComponent<Room>();
					if (_Room != nullptr)
					{
						_aiPhysicsComponent->SetAcceleration(glm::vec2(0, 0), true);
						_aiPhysicsComponent->SetVelocity(vec2(0, 0));
						InverseVel();
						collider->ClearColliding();
						break;
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

void AiAgent::Animate(float deltaTime)
{
	//loops through the sprite sheet based off the current velocity
	_aiAnimTimer += deltaTime;
	if (_aiAnimTimer >= _aiAnimSpeed)
	{
		_aiAnimTimer -= _aiAnimSpeed;
		int _gridX = _aiSprite->GetGridPos().x;
		int _gridY = _aiSprite->GetGridPos().y;
		vec2 spriteGridSize = _aiSprite->GetGridSize();

		//right
		if (_velocity.x > 0 && _velocity.y == 0)
		{
			_gridY = 2;
			if (_gridX < spriteGridSize.x - 1)
			{
				_gridX++;
			}
			else
			{
				_gridX = 0;
			}
			_aiSprite->SetGridPos(vec2(_gridX, _gridY));
			_facingDirection = Right;
		}
		//left
		if (_velocity.x < 0 && _velocity.y == 0)
		{
			_gridY = 1;
			if (_gridX < spriteGridSize.x - 1)
			{
				_gridX++;
			}
			else
			{
				_gridX = 0;
			}
			_aiSprite->SetGridPos(vec2(_gridX, _gridY));
			_facingDirection = Left;
		}
		//up
		if (_velocity.x == 0 && _velocity.y < 0)
		{
			_gridY = 3;
			if (_gridX < spriteGridSize.x - 1)
			{
				_gridX++;
			}
			else
			{
				_gridX = 0;
			}
			_aiSprite->SetGridPos(vec2(_gridX, _gridY));
			_facingDirection = Up;
		}
		//down
		if (_velocity.x == 0 && _velocity.y > 0)
		{
			_gridY = 0;
			if (_gridX < spriteGridSize.x - 1)
			{
				_gridX++;
			}
			else
			{
				_gridX = 0;
			}
			_aiSprite->SetGridPos(vec2(_gridX, _gridY));
			_facingDirection = Down;
		}

		if (_velocity.x < 0 && _velocity.y > 0)
		{
			float differance;
			differance = 0 - _velocity.x;
			if (differance > _velocity.y)
			{
				//left
				_gridY = 1;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Left;
			}
			else if (differance < _velocity.y)
			{
				//down
				_gridY = 0;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Down;
			}
		}

		if (_velocity.y < 0 && _velocity.x > 0)
		{
			float differance;
			differance = 0 - _velocity.y;
			if (differance > _velocity.x)
			{
				//up
				_gridY = 3;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Up;
			}
			else if (differance < _velocity.x)
			{
				//right
				_gridY = 2;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Right;
			}
		}

		if (_velocity.y > 0 && _velocity.x > 0)
		{
			if (_velocity.x > _velocity.y)
			{
				//right
				_gridY = 2;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Right;
			}
			else if (_velocity.x < _velocity.y)
			{
				//down
				_gridY = 0;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Down;
			}
		}

		if (_velocity.x < 0 && _velocity.y < 0)
		{

			if (_velocity.x < _velocity.y)
			{
				//left
				_gridY = 1;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Left;
			}
			else if (_velocity.x > _velocity.y)
			{
				//up
				_gridY = 3;
				if (_gridX < spriteGridSize.x - 1)
				{
					_gridX++;
				}
				else
				{
					_gridX = 0;
				}
				_aiSprite->SetGridPos(vec2(_gridX, _gridY));
				_facingDirection = Up;
			}
		}
	}
}

vec2 AiAgent::Seek(vec2 Target)
{
	//TODO change the target to be the players position
	vec2 target = _target;
	vec2 _moveForce = (target - _parent->GetTransform().pos);
	_distanceFromTarget = length(_moveForce);
	normalize(_moveForce);
	_moveForce = _moveForce * _maxSpeed;
	return (_moveForce - _velocity);
}

vec2 AiAgent::Wander(vec2 Target)
{
	//calculates the force needed to move to the random position passed to it 
	vec2 target = _target;
	vec2 _moveForce = (target - _parent->GetTransform().pos);
	_distanceFromTarget = length(_moveForce);
	normalize(_moveForce);
	_moveForce = _moveForce * _maxSpeed;
	return (_moveForce - _velocity);
}

void AiAgent::AiAttack()
{
	_currentScene = _parent->GetScene();
	_aiWeapon->AiAttack(_facingDirection, _parent->GetTransform().pos, _currentScene);
	_attackTimer = 0;
}

void AiAgent::InverseVel()
{
	_aiPhysicsComponent->SetVelocity(-_velocity);
	_parent->GetTransform().pos = vec2(_parent->GetTransform().pos);
	switch (_facingDirection)
	{
	case Down:
		_aiPhysicsComponent->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_facingDirection = Up;
		break;
	case Left:
		_aiPhysicsComponent->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_facingDirection = Right;
		break;
	case Right:
		_aiPhysicsComponent->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_facingDirection = Left;
		break;
	case Up:
		_aiPhysicsComponent->SetVelocity(glm::vec2(0, 0));
		_parent->GetTransform().pos = _lastFramePos;
		_facingDirection = Down;
		break;
	}
	RandomTargetSelector();

}

void AiAgent::AiDead()
{
	random_device rand;
	uniform_int_distribution<int> dist(1, 100);
	int randChance = dist(rand);
	if (randChance < 60)
	{
		//TODO: make a random chance of dropping an item 
		Hudson::Entity::GameObject* PassivePickup = new Hudson::Entity::GameObject();
		PassivePickup->AddComponent(new PassivePickups(_parent->GetTransform().pos));
		_currentScene->AddObject(PassivePickup);
	}
	if (randChance < 30 && randChance > 60)
	{
		Hudson::Entity::GameObject* AbilityPickup = new Hudson::Entity::GameObject();
		AbilityPickup->AddComponent(new PickupAbilitys(_parent->GetTransform().pos));
		_currentScene->AddObject(AbilityPickup);
	}
	//TODO: Remove the AI from the scene after the animaion 
	_currentScene->RemoveObject(Blood);
	_currentScene->RemoveObject(_parent);
}

void AiAgent::TakeDamage(int damageAmount)
{
	//removes damage passed to it and calls dead once health is 0
	_currentHealth = _currentHealth - damageAmount;
	_aiSprite->SetColor(vec3(1, 0, 0));

	if (_currentHealth >= 0)
	{
		_currentState = SEEK;
		_aiSprite->SetColor(vec3(1, 0, 0));
	}
	if (_currentHealth <= 0)
	{
		_currentState = DEAD;
	}
	_isDamaged = true;
}

void AiAgent::RandomTargetSelector()
{
	//choses a new target position with in an area of the ai current position 
	//choses a random position within the range 
	random_device rand;
	uniform_int_distribution<int> dist(_minRange, _maxRange);
	int posX = _parent->GetTransform().pos.x;
	int posY = _parent->GetTransform().pos.y;
	int randX = dist(rand);
	int randY = dist(rand);
	//adds the random number to the current position 
	_target = { posX + randX, posY + randY };
	_arrive = false;
}

void AiAgent::GetPlayerPos()
{
	if (_player == nullptr)
	{
		auto _sceneObjects = _currentScene->GetObjects();

		for (Hudson::Entity::GameObject* other : _sceneObjects)
		{

			if (other->GetName() == "Player")
			{
				_player = other->GetComponent<Player>();
				break;
			}
		}
	}

	if (_player != nullptr)
	{
		vec2 target = _player->GetParent()->GetTransform().pos;
		vec2 _moveForce = (target - _parent->GetTransform().pos);
		_distanceFromPlayer = length(_moveForce);
	}
	else
	{
		return;
	}
}

void AiAgent::SetPlayerPos()
{
	if (_player == nullptr)
	{
		auto _sceneObjects = _currentScene->GetObjects();

		for (Hudson::Entity::GameObject* other : _sceneObjects)
		{

			if (other->GetName() == "Player")
			{
				_player = other->GetComponent<Player>();
				break;
			}
		}
	}
	if (_player != nullptr)
	{
		_target = _player->GetParent()->GetTransform().pos;
	}
}

void AiAgent::Move(float deltatime)
{
	//adds the acceleration and velocity to the physics componant

	//sets velocity
	trunc(_moveForce);
	_acceleration = _moveForce / _mass;
	_velocity = _acceleration * deltatime;
	//cout << _velocity.x << "" << _velocity.y << endl;
	_aiPhysicsComponent->SetAcceleration(_acceleration, true);
	_aiPhysicsComponent->SetVelocity(_velocity);
	CollisionCheck();
}

void AiAgent::DrawPropertyUI()
{
	// draws to ImGui
	ImGui::DragScalar("Anim spd", ImGuiDataType_Float, &_aiAnimSpeed, 0.6);
	ImGui::DragScalar("Min Move Range", ImGuiDataType_Float, &_minRange, -300);
	ImGui::DragScalar("Max Move Range", ImGuiDataType_Float, &_maxRange, 300);
	ImGui::DragScalar("Move Speed", ImGuiDataType_Float, &_maxSpeed, 15);
	if (ImGui::Button("Wander")) {
		_currentState = WANDER;
	}
	if (ImGui::Button("Seek")) {
		_currentState = SEEK;
	}
	if (ImGui::Button("Attack")) {
		_currentState = ATTACK;
	}
	if (ImGui::Button("DEAD")) {
		_currentState = DEAD;
	}
}

void AiAgent::FromJson(const nlohmann::json& j)
{

}

void AiAgent::ToJson(nlohmann::json& j)
{

}