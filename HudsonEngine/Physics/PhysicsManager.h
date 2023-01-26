#pragma once
#include "../Util/stdafx.h"

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
		Hudson::Physics::PhysicsComponent* _physics;
		Hudson::Physics::ColliderComponent* _collider;
		Hudson::Common::Engine* _engine;
		double _lastTime;
		double _timer;
		double _accumulator;
		double _nowTime;
		int _frames;
		int _updates;
	};
}

