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
	class ColliderComponent : public Entity::Component, public Common::IEditable
	{
	public:
		ColliderComponent();
		ColliderComponent(const ColliderComponent& other) = default;
		~ColliderComponent();

		bool AABBCollision(ColliderComponent* collider);
		void SetColliding(ColliderComponent* other);
		void ClearColliding();
		AABB GetAABB();

	    std::set<ColliderComponent*> GetCurrentCollisions() { return _colliderList; }

        void DrawPropertyUI() override;
        void FromJson(const nlohmann::json& j) override;
        void ToJson(nlohmann::json& j) override;

    private:
		std::set<ColliderComponent*> _colliderList;
	};

}
