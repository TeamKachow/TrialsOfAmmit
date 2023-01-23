#pragma once

#include "../Util/stdafx.h"
#include "../Entity/Component.h"
#include "../Entity/GameObject.h"


struct AABB
{
	double Left; // Left Side Collision
	double Right; // Right Side Collision

	double Up; // Top Side Collision
	double Down; // Bottom Side Collsion
};


namespace Hudson::Physics
{
	class ColliderComponent : public Entity::Component
	{
	public:
		ColliderComponent();
		~ColliderComponent();

		bool AABBCollision(ColliderComponent* collider);
		void SetColliding(ColliderComponent* other);
		void ClearColliding();
		AABB GetAABB();

		std::set<ColliderComponent*> GetCurrentCollisions() { return _colliderList; }
	private:
		std::set<ColliderComponent*> _colliderList;
	};

}
