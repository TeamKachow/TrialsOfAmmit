#include <iostream>
#include <string>

class HudsonGameEngine {
public:
    void run() {
        showMainMenu();
    }

    void showMainMenu() {
        int choice = 0;
        std::cout << "Main Menu" << std::endl;
        std::cout << "1. Play Game" << std::endl;
        std::cout << "2. Options" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            playGame();
            break;
        case 2:
            showOptions();
            break;
        case 3:
            quit();
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            showMainMenu();
        }
    }

    void playGame() {
        std::cout << "Starting game..." << std::endl;
        // Add code for starting the game here
    }

    void showOptions() {
        int choice = 0;
        std::cout << "Options" << std::endl;
        std::cout << "1. Change Resolution" << std::endl;
        std::cout << "2. Change Volume" << std::endl;
        std::cout << "3. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            changeResolution();
            break;
        case 2:
            changeVolume();
            break;
        case 3:
            showMainMenu();
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            showOptions();
        }
    }

    void changeResolution() {
        std::cout << "Changing resolution..." << std::endl;
        // Add code for changing resolution here
        showOptions();
    }

    void changeVolume() {
        std::cout << "Changing volume..." << std::endl;
        // Add code for changing volume here
        showOptions();
    }

    void quit() {
        std::cout << "Quitting game..." << std::endl;
        // Add code for quitting the game here
    }
};

int main() {
    HudsonGameEngine game;
    game.run();
    return 0;
}
