#pragma once
#include "stdafx.h"

constexpr double FPS_60 = 1.0 / 60.0;

namespace Hudson
{
	namespace Collision
	{
		class Collider;
	}
}

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

	class PhysicsManager
	{
	public:
		PhysicsManager(Hudson::Common::Engine* engine);
		~PhysicsManager();
		void UpdatePhysics();
		void UpdateMovement(float deltaTime);
	private:
		Hudson::Physics::PhysicsComponent* physics;
		Hudson::Collision::Collider* collider;
		Hudson::Common::Engine* m_engine;
		double lastTime;
		double timer;
		double accumulator;
		double nowTime;
		int frames;
		int updates;
	};
}

