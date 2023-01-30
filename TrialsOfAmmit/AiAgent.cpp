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
	_maxSpeed = 30;
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
	switch (_currentState)
	{
	case SEEK:
		
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
	if (_distanceFromTarget < 30)
	{
		_arrive = true;
		cout << "Arrived" << endl;
	}
	if (_parent->GetTransform().pos.x > 1600 || _parent->GetTransform().pos.y > 900 || _parent->GetTransform().pos.x < 0 || _parent->GetTransform().pos.y < 0)
	{
		_target = vec2(500, 500);
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

void AiAgent::RandomTargetSelector()
{
	srand(time(0));
	int max_distance = 250;
	int posX = _parent->GetTransform().pos.x;
	int posY = _parent->GetTransform().pos.y;
	int delta_x = rand() % (2 * max_distance + 1) - max_distance;
	int delta_y = rand() % (2 * max_distance + 1) - max_distance;
	if (_target.x > 1600 && _target.y > 900 || _target.x < 0 && _target.y < 0)
	{
		RandomTargetSelector();
	}
	else
	{
		_target = { posX + delta_x, posY + delta_y };
		_arrive = false;
	}
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
	}
}

void AiAgent::DrawPropertyUI()
{

}