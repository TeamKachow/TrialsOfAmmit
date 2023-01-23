#pragma once
#include "../Util/stdafx.h"
#include "../Entity/Component.h"

namespace Hudson::Physics
{

	class PhysicsComponent : public Entity::Component
	{
	public:
		PhysicsComponent();
		~PhysicsComponent();

		void Update(float deltaTime);

		/**
        * Sets the Acceleration of the Object, False for Acceleration or True for Constant Acceleration.
        */
		void SetAcceleration(const glm::vec2& accel, bool Const) { _acceleration = accel; _constantAccel = Const; }
		/**
		* Get the Current Acceleration of the Object.
		*/
		const glm::vec2& GetAcceleration() const { return _acceleration; }
		/**
		* Sets the Velocity of the Object.
		*/
		void SetVelocity(const glm::vec2& velocity) { _velocity = velocity; }
		/**
		* Get the Current Velocity of the Object.
		*/
		const glm::vec2& GetVelocity() const { return _velocity; }

		/**
		* Sets the Force of the Object.
		*/
		void SetForce(const glm::vec2& force) { _force = force; }
		/**
		* Get the Current Force of the Object.
		*/
		const glm::vec2& GetForce() const { return _force; }

		/**
		* Sets the Mass of the Object.
		*/
		void SetMass(const float mass) { _mass = mass; }
		/**
		* Get the Current Mass of the Object.
		*/
		const float GetMass() const { return _mass; }

	private:
		void CalculateVelocity(float deltaTime);
		void CalculateAcceleration(float deltaTime);
		void UpdatePosition(float deltaTime);

		operator glm::vec2() const { return _velocity; }
		glm::vec2 _velocity = { 0,0 };
		glm::vec2 _acceleration = { 0 ,0 };
		glm::vec2 _force = { 0 ,0 };
		float _mass = 1.0f;
		bool _constantAccel = true;
	};
}
