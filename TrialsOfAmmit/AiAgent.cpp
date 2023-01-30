#include "AiAgent.h"

AiAgent::AiAgent():Behaviour("AiBehavior")
{

}

void AiAgent::OnCreate()
{
	//Set up of health and damage
	_maxHealth = 100.0f;
	_currentHealth = _maxHealth;
	_meleeDamage = 10.0f;
	_alive = true;
	//Starting state
	//sets from parent phyics componant 
	//need to add _position
}

AiAgent::~AiAgent()
{
	
}

void AiAgent::OnDestroy()
{

}

void AiAgent::OnTick(const double& dt)
{
	_target = vec2(200.0f, 0.0f);
	_currentState = WANDER;
	_aiPhysicsComponent = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();
	auto _aiPhysics = _aiPhysicsComponent.front();
	_velocity = _aiPhysics->GetVelocity();
	_mass = _aiPhysics->GetMass();
	_acceleration = _aiPhysics->GetAcceleration();
	switch (_currentState)
	{
	case SEEK:
		
		break;
	case WANDER:
		if (_parent->GetTransform().pos == _target)
		{
			_velocity = Wander(_target);
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

	if (!_aiPhysicsComponent.empty())
	{
		auto _aiPhysics = _aiPhysicsComponent.front();
		//sets velocity
		_aiPhysics->SetVelocity(_velocity);
	}
}

bool AiAgent::CollisionCheck()
{
	//return false unless colliding
	return false;
}

vec2 AiAgent::Seek(vec2 Target)
{
	//returns a velocity 
	return vec2(0, 0);
}

vec2 AiAgent::Wander(vec2 Target)
{
	RandomTargetSelector();
	vec2 target = Target;
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

void AiAgent::RandomTargetSelector()
{
	int max_distance = 5;

	int delta_x = rand() % (2 * max_distance + 1) - max_distance;
	int delta_y = rand() % (2 * max_distance + 1) - max_distance;

	_target = { _parent->GetTransform().pos.x + delta_x, _parent->GetTransform().pos.y + delta_y};

	/*int x = (rand() % 1920) - (1080 / 2);
	int y = (rand() % 1920) - (1080 / 2);
	_target = vec2(x, y);*/
}

void AiAgent::DrawPropertyUI()
{

}