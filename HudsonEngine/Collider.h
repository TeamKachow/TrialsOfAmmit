#pragma once

namespace Hudson::Collision
{
	class Collider
	{
	public:
		bool DoCollision();
	private:
		Collider();
		bool CheckBoxCollision();
		
	};
}
