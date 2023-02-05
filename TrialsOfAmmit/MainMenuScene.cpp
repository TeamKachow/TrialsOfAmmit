#include "MainMenuScene.h"
#include <iostream>
#include <vector>
#include <string>

MainMenuScene::MainMenuScene()
{
    mainMenuOptions = { "Play Game", "Options", "Quit" };
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::displayMainMenu()
{
    std::cout << "Main Menu:" << std::endl;
    for (int i = 0; i < mainMenuOptions.size(); i++)
    {
        std::cout << i + 1 << ") " << mainMenuOptions[i] << std::endl;
    }
}

void MainMenuScene::handleMainMenuInput()
{
    int userInput;
    std::cout << "Enter your selection: ";
    std::cin >> userInput;

    // Perform action based on user input
    switch (userInput)
    {
    case 1:
        std::cout << "Starting game..." << std::endl;
        break;
    case 2:
        std::cout << "Displaying options..." << std::endl;
        break;
    case 3:
        std::cout << "Quitting..." << std::endl;
        break;
    default:
        std::cout << "Invalid selection, please try again." << std::endl;
        handleMainMenuInput();
        break;
    }
}
