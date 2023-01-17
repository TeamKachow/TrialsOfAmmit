#pragma once

namespace Hudson::Collision
{
	class Collider
	{
	public:
		Collider();
		bool DoCollision();
	private:
		bool CheckBoxCollision();
		
	};
}
