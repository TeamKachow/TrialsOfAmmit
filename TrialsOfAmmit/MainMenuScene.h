#pragma once

#include <vector>
#include <string>

class MainMenuScene
{
public:
    MainMenuScene();
    ~MainMenuScene();

    void displayMainMenu();
    void handleMainMenuInput();

private:
    std::vector<std::string> mainMenuOptions;
};