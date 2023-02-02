#pragma once

#include <Hudson.h>

class BaseAbilityClass : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	BaseAbilityClass(Hudson::Render::SpriteComponent* _spriteComponent, int cooldown, int active_time /*Target target */);
	~BaseAbilityClass();
protected:
private:
	void OnCreate() override; // Basically Constructor ???
	void OnTick(const double& dt) override; // Basically Update()
	void OnDestroy() override;

	void DrawPropertyUI() override;
};





