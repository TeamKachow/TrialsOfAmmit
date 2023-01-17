#pragma once

#include "PhysicsMaths.h"
#include "Collider.h"
#include "Time.h"

namespace Hudson::Physics
{
	class PhysicsManager
	{
	public:
		PhysicsManager();
		void UpdatePhysics();
		void UpdateCollisions();
	private:
		Hudson::Util::Time* time;
		Hudson::Physics::PhysicsMaths* physics;
		Hudson::Collision::Collider* collider;
	};
}

