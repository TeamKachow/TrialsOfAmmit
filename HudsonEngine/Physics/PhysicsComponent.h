#pragma once
#include "../Util/stdafx.h"
#include "../Entity/Component.h"
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
		void CalculateConstantAcceleration(float deltaTime);
		void UpdatePosition(float deltaTime);

		glm::vec2 _velocity = { 0,0 };
		glm::vec2 _acceleration = { 0 ,0 };
		glm::vec2 _force = { 0 ,0 };
		float _mass = 1.0f;

		void SetAcceleration(const glm::vec2& accel) { _acceleration = accel; }
		const glm::vec2& GetAcceleration() const { return _acceleration; }

		void SetVelocity(const glm::vec2& velocity) { _velocity = velocity; }
		const glm::vec2& GetVelocity() const { return _velocity; }

		void SetForce(const glm::vec2& force) { _force = force; }
		const glm::vec2& GetForce() const { return _force; }

		void SetMass(const float mass) { _mass = mass; }
		const float GetMass() const { return _mass; }
	};
}
