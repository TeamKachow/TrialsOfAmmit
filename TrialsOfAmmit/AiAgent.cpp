#include "AiAgent.h"

AiAgent::AiAgent():Behaviour("AiBehavior")
{
	//Set up of health and damage
	_maxHealth = 100.0f;
	_currentHealth = _maxHealth;
	_meleeDamage = 10.0f;
	//Starting state
	_target = vec2(0, 0);
	_currentState = WANDER;
	_aiPhysicsComponent = _parent->GetComponents<Hudson::Physics::PhysicsComponent>();

}

AiAgent::~AiAgent()
{
	
}

void AiAgent::OnTick(const double& dt)
{
	switch (_currentState)
	{
	case SEEK:
		Seek(_target);
		break;
	case WANDER:
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
	//returns a velocity 
	return vec2(0, 0);
}

void AiAgent::AiAttack()
{

}

void AiAgent::AiDead()
{

}