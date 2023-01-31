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
	_currentHealth = _maxHealth;
	_meleeDamage = 10.0f;
	_alive = true;
	_maxSpeed = 15;
	_arrive = true;
	//need to add _position
	_target = vec2(0,0);
	//Starting state
	_currentState = WANDER;
	//sets from parent phyics componant 
	_aiPhysicsComponent = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();
	auto _aiPhysics = _aiPhysicsComponent.front();
	_velocity = _aiPhysics->GetVelocity();
	_mass = _aiPhysics->GetMass();
	_acceleration = _aiPhysics->GetAcceleration();
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
	if (_distanceFromTarget < 200)
	{
		_arrive = true;
	}

	switch (_currentState)
	{
	case SEEK:
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
	//return false unless colliding
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
	_aiAnimTimer += deltaTime;
	if (_aiAnimTimer >= _aiAnimSpeed)
	{
		_aiAnimTimer -= _aiAnimSpeed;
		int _gridX = _aiSprite->GetGridPos().x;
		int _gridY = _aiSprite->GetGridPos().y;

		vec2 spriteGridSize = _aiSprite->GetGridSize();
		//Animation walking right
		if (_velocity.x > 1)
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
		}
		//Animation walking left
		if (_velocity.x < 1)
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
		}
		//Animation walking down
		if (_velocity.y > 1)
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
		}
		//Animation walking up
		if (_velocity.y < 1)
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
		}
		//FIX THIS
		/*if (_arrive == true)
		{
			_gridY = 0;
			_gridX = 0;
		}*/
		_aiSprite->SetGridPos(vec2(_gridX, _gridY));
	}
}

vec2 AiAgent::Seek(vec2 Target)
{
	vec2 target = _target;
	vec2 _moveForce = (target - _parent->GetTransform().pos);
	_distanceFromTarget = length(_moveForce);
	normalize(_moveForce);
	_moveForce = _moveForce * _maxSpeed;
	return (_moveForce - _velocity);
}

vec2 AiAgent::Wander(vec2 Target)
{
	vec2 target = _target;
	vec2 _moveForce = (target - _parent->GetTransform().pos);
	_distanceFromTarget = length(_moveForce);
	normalize(_moveForce);
	_moveForce = _moveForce * _maxSpeed;
	return (_moveForce - _velocity);
}

void AiAgent::AiAttack()
{

}

void AiAgent::AiDead()
{
	_alive = false;
}

void AiAgent::TakeDamage(int damageAmount)
{
	_currentHealth = _currentHealth - damageAmount;

	if (_currentHealth <= 0)
	{
		AiDead();
	}
}

void AiAgent::RandomTargetSelector()
{
	random_device rand;
	uniform_int_distribution<int> dist(-250, 250);
	int posX = _parent->GetTransform().pos.x;
	int posY = _parent->GetTransform().pos.y;
	int randX = dist(rand);
	int randY = dist(rand);
	_target = { posX + randX, posY + randY };
	_arrive = false;
	
}

void AiAgent::Move(float deltatime)
{
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
	ImGui::DragScalar("Anim spd", ImGuiDataType_Double, &_aiAnimSpeed, 0.05);

	if (ImGui::Button("Wander")) {
		_currentState = WANDER;
	}

	if (ImGui::Button("Seek")) {
		_currentState = SEEK;
	}
}