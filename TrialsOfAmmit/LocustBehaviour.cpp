#include "LocustBehaviour.h"
#include "PickupAbilitys.h"
#include "PassivePickups.h"
#include "Rooms/Room.h"
#include "MeleeCollider.h"

LocustBehaviour::LocustBehaviour(glm::vec2 spawnPos) : Behaviour("LocustBehaviour")
{
	_spawnPosition = spawnPos;
}

LocustBehaviour::~LocustBehaviour()
{
}

void LocustBehaviour::AiDead()
{
}

void LocustBehaviour::OnCreate()
{
	//sets up sprite
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_aiSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Locust"));
	_aiSprite->SetGridSize(glm::vec2(3, 1));
	_aiSprite->SetGridPos(glm::vec2(0, 0));
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
	_parent->SetName("Locust");
	_parent->GetTransform().pos = _spawnPosition;

	//Set up of health and damage
	_maxSpeed = 35;
	_alive = true;

	//need to add _position
	_target = glm::vec2(0, 0);

	//Starting state
	_currentState = LS_SEEK;

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
	//_currentScene->AddObject(_parent);
}

void LocustBehaviour::Animate(float dt)
{
	_animationTimer += dt;
	if (_animationTimer < 0.1)
	{
		_aiSprite->SetGridPos(glm::vec2(0, 0));
	}
	else if (_animationTimer < 0.2)
	{
		_aiSprite->SetGridPos(glm::vec2(1, 0));
	}
	else if (_animationTimer < 0.3)
	{
		_aiSprite->SetGridPos(glm::vec2(2, 0));
		_animationTimer = 0;
	}
}

void LocustBehaviour::OnDestroy()
{
}

void LocustBehaviour::OnTick(const double& dt)
{
	Animate(dt);
	switch (_currentState)
	{
	case LS_SEEK:
		SetPlayerPos();
		_moveForce = Seek(_target);
		Move(dt);
		break;
	case LS_DEAD:
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
			break;
		}
		_aiAnimDeathTimer += dt;
		if (_aiAnimDeathTimer > 0.5)
		{
			_currentScene->RemoveObject(Blood);
			_currentScene->RemoveObject(_parent);
			break;
		}
		break;
	}
}
void LocustBehaviour::CollisionCheck()
{
	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other->GetParent()->GetComponent<Player>() != nullptr)
			{
				Player* player = other->GetParent()->GetComponent<Player>();
				if (player != nullptr)
				{
					player->TakeDamage(1.0f);
					break;
				}
			}
		}
		collider->ClearColliding();
	}
}

glm::vec2 LocustBehaviour::Seek(glm::vec2 Target)
{
	//TODO change the target to be the players position
	glm::vec2 target = _target;
	glm::vec2 _moveForce = (target - _parent->GetTransform().pos);
	_distanceFromTarget = length(_moveForce);
	normalize(_moveForce);
	_moveForce = _moveForce * _maxSpeed;
	return (_moveForce - _velocity);
}

void LocustBehaviour::Move(float deltatime)
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

void LocustBehaviour::SetPlayerPos()
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

void LocustBehaviour::FromJson(const nlohmann::json& j)
{
}

void LocustBehaviour::ToJson(nlohmann::json& j)
{
}

void LocustBehaviour::Kill()
{
	_currentState = LS_DEAD;
}
