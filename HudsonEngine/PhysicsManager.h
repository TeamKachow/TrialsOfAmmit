#pragma once

#include<glm/glm.hpp>

#include "Time.h"

namespace Hudson::Physics
{
	class PhysicsManager
	{
	public:
		glm::vec2 m_velocity = {0,0};
	private:
		// FORCES / MOVEMENT FORCES
		PhysicsManager();
		void Update(float timeDelta);

		void UpdatePosition(float deltaTime);

		void CalculateVelocity(float deltaTime);
		void CalculateAcceleration();

		glm::vec2 m_acceleration = { 0 ,0};
		glm::vec2 m_force = { 1 ,1};
		float m_mass = 1.0f;
		glm::vec2 m_position = {0 ,0};
		private:
			void SetPosition(const glm::vec2& position) { m_position = position; }
			const glm::vec2& GetPosition() const { return m_position; }

			void SetVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
			const glm::vec2& GetVelocity() const { return m_velocity; }

			void SetForce(const glm::vec2& force) { m_force = force; }
			const glm::vec2& GetForce() const { return m_force; }

			void SetMass(const float mass) { m_mass = mass; }
			const float GetMass() const { return m_mass; }
	private:
		// COLLISIONS

		// AABB COLLSIONS

		

	};

}

