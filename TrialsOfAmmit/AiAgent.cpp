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
	_target = vec2(0, 0);
	_currentState = WANDER;
	//sets from parent phyics componant 
	_aiPhysicsComponent = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();
	auto _aiPhysics = _aiPhysicsComponent.front();
	_velocity = _aiPhysics->GetVelocity();
	_mass = _aiPhysics->GetMass();
	_acceleration = _aiPhysics->GetAcceleration();
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
	switch (_currentState)
	{
	case SEEK:
		
		break;
	case WANDER:
		RandomTargetSelector();
		Wander(_target);
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

	auto _aiPhysics = _aiPhysicsComponent.front();
	//sets velocity
	_aiPhysics->SetVelocity(_velocity);
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
	vec2 target = Target;
	vec2 _moveForce = (Target - _parent->GetTransform().pos);
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
	int x = (rand() % 1920) - (1080 / 2);
	int y = (rand() % 1920) - (1080 / 2);
	_target = vec2(x, y);
}

void AiAgent::DrawPropertyUI()
{

}