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
	// Using Semi-Implicit Euler Integragtion
	static float time = 0;
	time += deltaTime;

	CalculateAcceleration(); // Calculate Acceleration First
	CalculateVelocity(deltaTime); // Calculate Velocity uisng Acceleration
	UpdatePosition(deltaTime);
}

void Hudson::Physics::PhysicsComponent::CalculateAcceleration()
{
	// a = f / m
	m_acceleration = m_force / m_mass;
}

void Hudson::Physics::PhysicsComponent::CalculateVelocity(float deltaTime)
{
	// v = u + at 
	m_velocity = m_velocity + m_acceleration * deltaTime;
}

void Hudson::Physics::PhysicsComponent::UpdatePosition(float deltaTime)
{
	Hudson::Entity::GameObject::Transform tempTrans = _parent->GetTransform();

	tempTrans.posX += m_velocity.x * deltaTime;
	tempTrans.posY += m_velocity.y * deltaTime;

	_parent->SetTransform(tempTrans);
}