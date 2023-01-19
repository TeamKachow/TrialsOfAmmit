#pragma once
#include "stdafx.h"
#include "Entity/Component.h"
#include "PhysicsManager.h"

namespace Hudson::Physics
{

	class PhysicsComponent : public Entity::Component
	{
	public:
		PhysicsComponent();
		~PhysicsComponent();

		void Update(float deltaTime);
		void CalculateVelocity(float deltaTime);
		void CalculateAcceleration();
		void UpdatePosition(float deltaTime);

		glm::vec2 m_velocity = { 0,0 };
		glm::vec2 m_acceleration = { 0 ,0 };
		glm::vec2 m_force = { 1 ,1 };
		float m_mass = 1.0f;

		void SetAcceleration(const glm::vec2& accel) { m_acceleration = accel; }
		const glm::vec2& GetAcceleration() const { return m_acceleration; }

		void SetVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
		const glm::vec2& GetVelocity() const { return m_velocity; }

		void SetForce(const glm::vec2& force) { m_force = force; }
		const glm::vec2& GetForce() const { return m_force; }

		void SetMass(const float mass) { m_mass = mass; }
		const float GetMass() const { return m_mass; }
	};
}
