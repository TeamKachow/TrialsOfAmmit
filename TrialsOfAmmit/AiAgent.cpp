#include "AiAgent.h"

AiAgent::AiAgent(Hudson::Render::SpriteComponent* aiSprite, double animSpeed) : Behaviour("AiBehavior")
{
	_aiSprite = aiSprite;
	_aiAnimSpeed = 0.6;
}

void AiAgent::OnCreate()
{
	//Set up of health and damage
	_maxHealth = 100.0f;
	_meleeDamage = 10.0f;
	_maxSpeed = 15;
	_maxRange = 250;
	_minRange = -250;
	_currentHealth = _maxHealth;
	_alive = true;
	//sets to true to chose a new point
	_arrive = true;
	//need to add _position
	_target = vec2(0,0);
	//Starting state
	_currentState = WANDER;
	//sets from parent phyics componants 
	_aiPhysicsComponent = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();
	auto _aiPhysics = _aiPhysicsComponent.front();
	_velocity = _aiPhysics->GetVelocity();
	_mass = _aiPhysics->GetMass();
	_acceleration = _aiPhysics->GetAcceleration();

	_currentscene = _parent->GetScene();
	auto _sceneObjects = _currentscene->GetObjects();
	for(Hudson::Entity::GameObject* other: _sceneObjects)
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
	float deltatime = dt;
	Animate(deltatime);
	//lets the Ai chose a new destinations before it has reached the current higher = less jitter
	if (_distanceFromTarget < 100)
	{
		_arrive = true;
	}
	//finite state machine 
	switch (_currentState)
	{
	case SEEK:
		GetPlayerPos();
		_moveForce = Seek(_target);
		Move(deltatime);
		break;
	case WANDER:
		if (_parent->GetTransform().pos != _target)
		{
			if (_arrive == true)
			{
				RandomTargetSelector();
			}
			_moveForce = Wander(_target);
			Move(deltatime);	
		}
		break;
	case ATTACK:
		AiAttack();
		break;
	case DEAD:
		AiDead();
		break;
	default:

		break;
	}
}

void AiAgent::CollisionCheck()
{
	// pushes Ai back and choses a new destination when trying to leave the map bounds 
	if (_parent->GetTransform().pos.x >= 1550.0f)
	{
		if (!_aiPhysicsComponent.empty())
		{
			auto _aiPhysics = _aiPhysicsComponent.front();
			_aiPhysics->SetVelocity(vec2(-100, 0));
			RandomTargetSelector();
		}
	}
	if (_parent->GetTransform().pos.y >= 830.0f)
	{
		if (!_aiPhysicsComponent.empty())
		{
			auto _aiPhysics = _aiPhysicsComponent.front();
			_aiPhysics->SetVelocity(vec2(0,-100));
			RandomTargetSelector();
		}
	}
	if (_parent->GetTransform().pos.x <= 0.0f)
	{
		if (!_aiPhysicsComponent.empty())
		{
			auto _aiPhysics = _aiPhysicsComponent.front();
			_aiPhysics->SetVelocity(vec2(100, 0));
			RandomTargetSelector();
		};
	}
	if (_parent->GetTransform().pos.y <= 0.0f)
	{
		if (!_aiPhysicsComponent.empty())
		{
			auto _aiPhysics = _aiPhysicsComponent.front();
			_aiPhysics->SetVelocity(vec2(0, 100));
			RandomTargetSelector();
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
		//Animation walking down
		if (_velocity.y >= 1)
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
		}
		//Animation walking up
		if (_velocity.y <= 1)
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
	//TODO 
}

void AiAgent::AiDead()
{
	//needs to be able to remove the object from the scene 
	_alive = false;
	_currentscene->RemoveObject(_parent);
}

void AiAgent::TakeDamage(int damageAmount)
{
	//removes damage passed to it and calls dead once health is 0
	_currentHealth = _currentHealth - damageAmount;
	if (_currentHealth <= 0)
	{
		AiDead();
	}
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
	//TODO
	_target = _player->GetParent()->GetTransform().pos;
}

void AiAgent::Move(float deltatime)
{
	//adds the acceleration and velocity to the physics componant
	if (!_aiPhysicsComponent.empty())
	{
		auto _aiPhysics = _aiPhysicsComponent.front();
		//sets velocity
		trunc(_moveForce);
		_acceleration = _moveForce / _mass;
		_velocity = _acceleration * deltatime;
		//cout << _velocity.x << "" << _velocity.y << endl;
		_aiPhysics->SetAcceleration(_acceleration, true);
		_aiPhysics->SetVelocity(_velocity);
		CollisionCheck();
	}
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
	if (ImGui::Button("DEAD")) {
		_currentState = DEAD;
	}
}