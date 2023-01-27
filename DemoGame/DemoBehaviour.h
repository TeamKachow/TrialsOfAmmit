#pragma once

class DemoBehaviour : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
private:
    Hudson::Render::SpriteComponent* _sprite;
    double _animSpeed = 0, _animAcc = 0;

public:
    DemoBehaviour(Hudson::Render::SpriteComponent* sprite, double animSpeed = 0.8);
    ~DemoBehaviour() override;

    // Editor components need a no-args constructor
    DemoBehaviour();
    DemoBehaviour(const DemoBehaviour& other) = default;

    void OnCreate() override;
    void OnTick(const double& dt) override;
    void OnDestroy() override;

    void DrawPropertyUI() override;
};

