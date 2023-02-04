/*#pragma once

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
*/


#pragma once

#include <Hudson.h>
#include "../World/Scene.h"
void Menus::OnCreate()
{
    _currentScene = _parent->GetScene();
    _menuSprite->SetGridPos(glm::vec2(0, 0));
}

void Menus::OnTick(const double& dt)
{
    if (_selectedOption == 0)
    {
        // highlight "Start Game" option
    }
    else if (_selectedOption == 1)
    {
        // highlight "Options" option
    }
    else if (_selectedOption == 2)
    {
        // highlight "Quit" option
    }
}

void Menus::OnDestroy()
{
}

void Menus::DrawPropertyUI()
{
    if (ImGui::Button("Start Game"))
    {
        _selectedOption = 0;
        // start the game
    }
    if (ImGui::Button("Options"))
    {
        _selectedOption = 1;
        // open options menu
    }
    if (ImGui::Button("Quit"))
    {
        _selectedOption = 2;
        // quit the game
    }
}

