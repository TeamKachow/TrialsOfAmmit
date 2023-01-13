#include "RigidBody.h"

Hudson::RigidBody::RigidBody::RigidBody()
{

}

void Hudson::RigidBody::RigidBody::Update(float deltaTime)
{
	// Using Semi-Implicit Euler Integragtion

	CalculateAcceleration(); // Calculate Acceleration First
	CalculateVelocity(deltaTime); // Calculate Velocity uisng Acceleration
	UpdatePosition(deltaTime);  // Update the gameobject with the values

	 m_acceleration = { 0 , 0};
	 m_force = { 0, 0};
}

void Hudson::RigidBody::RigidBody::CalculateAcceleration()
{
	// a = f / m
	m_acceleration = m_force / m_mass;
}

void Hudson::RigidBody::RigidBody::CalculateVelocity(float deltaTime)
{
	// v = u + at 
	m_velocity = m_velocity + m_acceleration * deltaTime;
}

void Hudson::RigidBody::RigidBody::UpdatePosition(float deltaTime)
{
	glm::vec2 currentPosition = GetPosition();
	currentPosition += m_velocity * deltaTime;
	SetPosition(currentPosition);
}


