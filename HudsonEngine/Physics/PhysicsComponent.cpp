#include "../Physics/PhysicsComponent.h"
#include "../Entity/GameObject.h"

Hudson::Physics::PhysicsComponent::PhysicsComponent()
{

}

Hudson::Physics::PhysicsComponent::~PhysicsComponent()
{

}


void Hudson::Physics::PhysicsComponent::Update(float deltaTime)
{
	// Using Semi-Implicit Euler Integration

	// Calculate Acceleration Or Constant Acceleration
	CalculateAcceleration(deltaTime); 
	//CalculateConstantAcceleration(deltaTime);

	// Calculate Velocity using Acceleration
	CalculateVelocity(deltaTime);

	// Update Positions
	UpdatePosition(deltaTime);
}

void Hudson::Physics::PhysicsComponent::CalculateAcceleration(float deltaTime)
{
	// a = f / m

	if(_constantAccel == true)
	{
		_acceleration = _acceleration * deltaTime + 0.5f * _acceleration * deltaTime * deltaTime;
	}
	else
	{
		_acceleration = _force / _mass;
	}
}

void Hudson::Physics::PhysicsComponent::CalculateVelocity(float deltaTime)
{
	// v = u + at 
	_velocity = _velocity + _acceleration * deltaTime;
}

void Hudson::Physics::PhysicsComponent::UpdatePosition(float deltaTime)
{
	Hudson::Entity::GameObject::Transform tempTrans = _parent->GetTransform();

	tempTrans.pos.x += _velocity.x * deltaTime;
	tempTrans.pos.y += _velocity.y * deltaTime;

	_parent->SetTransform(tempTrans);
}