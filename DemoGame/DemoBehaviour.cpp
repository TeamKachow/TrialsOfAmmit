#include "DemoBehaviour.h"

#include "SpriteComponent.h"

DemoBehaviour::DemoBehaviour(Hudson::Render::SpriteComponent* sprite, double animSpeed)
{
	_sprite = sprite;
    _animSpeed = animSpeed;
}

DemoBehaviour::~DemoBehaviour()
= default;

void DemoBehaviour::OnCreate()
{
    std::cout << "Demo behaviour added to an object!\n";
}

void DemoBehaviour::OnTick(const double& dt)
{
    _animAcc += dt;
    if (_animAcc >= _animSpeed)
    {
        _animAcc -= _animSpeed;

		int x = _sprite->GetGridPos().x;
		glm::vec2 spriteGridSize = _sprite->GetGridSize();

		if (x >= spriteGridSize.x - 1) {
			x = 0;
		}
		else {
			x += 1;
		}
		
		_sprite->SetGridPos(glm::vec2(x, 0));
    }
}

void DemoBehaviour::OnDestroy()
{
    std::cout << "Demo behaviour removed from an object!\n";
}
