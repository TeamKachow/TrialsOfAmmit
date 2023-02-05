#pragma once

#include <Hudson.h>
#include "../World/Scene.h"

class Menus : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	Menus(Hudson::Render::SpriteComponent* menuSprite) : Behaviour("Menus"), _menuSprite(menuSprite), _selectedOption(0)
	{
		_menuSprite->SetGridPos(glm::vec2(0, 0));
	}
    ~Menus() {}

private:
    Hudson::Render::SpriteComponent* _menuSprite;
    int _selectedOption;
    Hudson::World::Scene* _currentScene;

public:
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;

	void DrawPropertyUI() override;

};





