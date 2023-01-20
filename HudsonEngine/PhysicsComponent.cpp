#include "PhysicsComponent.h"
#include "Entity/GameObject.h"

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
	m_acceleration = m_force / m_mass;
}

void Hudson::Physics::PhysicsComponent::CalculateConstantAcceleration(float deltaTime)
{
	m_acceleration = m_acceleration * deltaTime + 0.5f * m_acceleration * deltaTime * deltaTime;
}


void Hudson::Physics::PhysicsComponent::CalculateVelocity(float deltaTime)
{
	// v = u + at 
	m_velocity = m_velocity + m_acceleration * deltaTime;
}

void Hudson::Physics::PhysicsComponent::UpdatePosition(float deltaTime)
{
	Hudson::Entity::GameObject::Transform tempTrans = _parent->GetTransform();

	tempTrans.pos.x += m_velocity.x * deltaTime;
	tempTrans.pos.y += m_velocity.y * deltaTime;

	_parent->SetTransform(tempTrans);
}