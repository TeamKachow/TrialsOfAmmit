#include "PhysicsComponent.h"
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
	//CalculateAcceleration(); 
	CalculateConstantAcceleration(deltaTime);

	// Calculate Velocity using Acceleration
	CalculateVelocity(deltaTime);

	// Update Positions
	UpdatePosition(deltaTime);
}

void Hudson::Physics::PhysicsComponent::CalculateAcceleration()
{
	// a = f / m
	_acceleration = _force / _mass;
}

void Hudson::Physics::PhysicsComponent::CalculateConstantAcceleration(float deltaTime)
{
	_acceleration = _acceleration * deltaTime + 0.5f * _acceleration * deltaTime * deltaTime;
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