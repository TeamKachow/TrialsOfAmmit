#pragma once
#include "stdafx.h"

constexpr double FPS_60 = 1.0 / 60.0;

namespace Hudson
{
	namespace Common
	{
		class Engine;
	}
}

namespace Hudson::Physics
{
	class PhysicsComponent;
	class ColliderComponent;

	class PhysicsManager
	{
	public:
		PhysicsManager(Hudson::Common::Engine* engine);
		~PhysicsManager();
		void UpdatePhysics();
		void UpdateMovement(float deltaTime);
		void UpdateCollider();

	private:
		Hudson::Physics::PhysicsComponent* physics;
		Hudson::Physics::ColliderComponent* collider;
		Hudson::Common::Engine* m_engine;
		double lastTime;
		double timer;
		double accumulator;
		double nowTime;
		int frames;
		int updates;
	};
}

