#pragma once

#include "PhysicsMaths.h"
#include "Collider.h"
#include "Time.h"
#include <GLFW/glfw3.h>

#define FPS_60 1.0f / 60.0f

namespace Hudson::Physics
{
	class PhysicsManager
	{
	public:
		PhysicsManager();
		~PhysicsManager();
		void UpdatePhysics();
	private:
		Hudson::Physics::PhysicsMaths* physics;
		Hudson::Collision::Collider* collider;

		double lastTime;
		double timer;
		double deltaTime;
		double nowTime;
		int frames;
		int updates;
	};
}

