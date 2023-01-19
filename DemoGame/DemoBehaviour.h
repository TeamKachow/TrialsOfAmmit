#pragma once
#include "Behaviour.h"

namespace Hudson
{
    namespace Render
    {
        class SpriteComponent;
    }
}

class DemoBehaviour : public Hudson::Entity::Behaviour
{
private:
    Hudson::Render::SpriteComponent* _sprite;
    double _animSpeed = 0, _animAcc = 0;

public:
    DemoBehaviour(Hudson::Render::SpriteComponent* sprite, double animSpeed = 0.8);
    ~DemoBehaviour() override;

    void OnCreate() override;
    void OnTick(const double& dt) override;
    void OnDestroy() override;
};

