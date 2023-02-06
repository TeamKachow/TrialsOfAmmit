#pragma once

namespace Hudson
{
    namespace Render
    {
        class SpriteComponent;
    }
    namespace Audio
    {
        class AudioManager;
    }
}

class DemoBehaviour : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
private:
    Hudson::Render::SpriteComponent* _sprite;
    double _animSpeed = 0, _animAcc = 0;

public:
    // Editor components need a no-args constructor and a copy constructor
    DemoBehaviour(Hudson::Render::SpriteComponent* sprite = nullptr, double animSpeed = 0.8); // new DemoBehaviour()
    DemoBehaviour(const DemoBehaviour& other) = default;

    ~DemoBehaviour() override;


    void OnCreate() override;
    void OnTick(const double& dt) override;
    void OnDestroy() override;

    void DrawPropertyUI() override;
    void FromJson(const nlohmann::json& j) override;
    void ToJson(nlohmann::json& j) override;
};

