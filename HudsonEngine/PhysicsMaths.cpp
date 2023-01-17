#include "PhysicsMaths.h"

Hudson::Physics::PhysicsMaths::PhysicsMaths()
{

}

void Hudson::Physics::PhysicsMaths::Update(float deltaTime)
{
	// Using Semi-Implicit Euler Integragtion
	static float time = 0;
	time += deltaTime;


	CalculateAcceleration(); // Calculate Acceleration First
	CalculateVelocity(time); // Calculate Velocity uisng Acceleration
}

void Hudson::Physics::PhysicsMaths::CalculateAcceleration()
{
	// a = f / m
	m_acceleration = m_force / m_mass;
}

void Hudson::Physics::PhysicsMaths::CalculateVelocity(float deltaTime)
{
	// v = u + at 
	m_velocity = m_velocity + m_acceleration * deltaTime;
}


