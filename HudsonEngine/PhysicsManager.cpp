#include "PhysicsManager.h"

Hudson::Physics::PhysicsManager::PhysicsManager()
{

}

void Hudson::Physics::PhysicsManager::Update(float deltaTime)
{
	CalculateAcceleration();
	CalculateVelocity(deltaTime);
	UpdatePosition(deltaTime);

	 m_acceleration = { 0 , 0};
	 m_force = { 0, 0};
}

void Hudson::Physics::PhysicsManager::CalculateAcceleration()
{
	m_acceleration = m_force / m_mass;
}

void Hudson::Physics::PhysicsManager::CalculateVelocity(float deltaTime)
{
	m_velocity = m_velocity + m_acceleration * deltaTime;
}

void Hudson::Physics::PhysicsManager::UpdatePosition(float deltaTime)
{
	glm::vec2 currentPosition = GetPosition();
	currentPosition += m_velocity * deltaTime;
	SetPosition(currentPosition);
}


