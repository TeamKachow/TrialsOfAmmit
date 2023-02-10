#pragma once
#include "../Util/stdafx.h"

namespace Hudson
{
	namespace Common
	{
		class Engine;
	}
}

namespace Hudson
{
	namespace Util
	{
		class Timestep;
	}
}


namespace Hudson::Physics
{
	class PhysicsComponent;
	class ColliderComponent;
	class Timestep;

	class PhysicsManager
	{
	public:
		PhysicsManager(Hudson::Common::Engine* engine);
		~PhysicsManager();
		void UpdatePhysics();
		void UpdateMovement(double deltaTime);
		void UpdateCollider();

	private:
		Hudson::Physics::PhysicsComponent* _physics;
		Hudson::Physics::ColliderComponent* _collider;
		Hudson::Common::Engine* _engine;
		Hudson::Util::Timestep* _timestep;
	};
}

