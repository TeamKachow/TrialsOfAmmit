#include "InputManager.h"

std::vector<Hudson::Common::InputManager*> Hudson::Common::InputManager::instances;

Hudson::Common::InputManager::InputManager()
{
	initialiseKeys();
	InputManager::instances.push_back(this);
}

Hudson::Common::InputManager::~InputManager()
{
	instances.erase(remove(instances.begin(), instances.end(), this), instances.end());
}

void Hudson::Common::InputManager::initialiseKeys()
{
	int keyCodes[] = { 32, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72,
				  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 256,
				  262, 263, 264, 265 };
	for (int key : keyCodes)
	{
		std::string keyName;
		switch (key) {
		case 32:
			keyName = "Spacebar";
			break;
		case 48:
			keyName = "0";
			break;
		case 49:
			keyName = "1";
			break;
		case 50:
			keyName = "2";
			break;
		case 51:
			keyName = "3";
			break;
		case 52:
			keyName = "4";
			break;
		case 53:
			keyName = "5";
			break;
		case 54:
			keyName = "6";
			break;
		case 55:
			keyName = "7";
			break;
		case 56:
			keyName = "8";
			break;
		case 57:
			keyName = "9";
			break;
		case 65:
			keyName = "A";
			break;
		case 66:
			keyName = "B";
			break;
		case 67:
			keyName = "C";
			break;
		case 68:
			keyName = "D";
			break;
		case 69:
			keyName = "E";
			break;
		case 70:
			keyName = "F";
			break;
		case 71:
			keyName = "G";
			break;
		case 72:
			keyName = "H";
			break;
		case 73:
			keyName = "I";
			break;
		case 74:
			keyName = "J";
			break;
		case 75:
			keyName = "K";
			break;
		case 76:
			keyName = "L";
			break;
		case 77:
			keyName = "M";
			break;
		case 78:
			keyName = "N";
			break;
		case 79:
			keyName = "O";
			break;
		case 80:
			keyName = "P";
			break;
		case 81:
			keyName = "Q";
			break;
		case 82:
			keyName = "R";
			break;
		case 83:
			keyName = "S";
			break;
		case 84:
			keyName = "T";
			break;
		case 85:
			keyName = "U";
			break;
		case 86:
			keyName = "V";
			break;
		case 87:
			keyName = "W";
			break;
		case 88:
			keyName = "X";
			break;
		case 89:
			keyName = "Y";
			break;
		case 90:
			keyName = "Z";
			break;
		case 256:
			keyName = "Escape";
			break;
		case 262:
			keyName = "Right";
			break;
		case 263:
			keyName = "Left";
			break;
		case 264:
			keyName = "Down";
			break;
		case 265:
			keyName = "Up";
			break;
		}
		std::pair<std::string, int>keyInsert(keyName, key);
		std::pair<std::string , std::string>actionInsert(keyName, "Not Assigned");
		keys.insert(keyInsert);
		keyActions.insert(std::pair<std::string, std::string>(actionInsert));
		keyDown[key] = false;
	}

}

bool Hudson::Common::InputManager::getKeyInput(std::string action)
{
	std::string actionStr = action;
	std::string keyName;
	int keyID;
	std::map <std::string, std::string> ::iterator it1 = actionKeys.find(actionStr);
	if (it1 != actionKeys.end())
	{
		keyName = actionKeys[actionStr];
		std::map <std::string, int>::iterator it2 = keys.find(keyName);
		if (it2 != keys.end())
		{
			keyID = keys[keyName];
			std::map <int, bool>::iterator it3 = keyDown.find(keyID);
			if (it3 != keyDown.end())
			{
				return keyDown[keyID];
			}
		}
	}

	return false;
}

void Hudson::Common::InputManager::setKeyEvent(std::string action, std::string keyName)
{
	std::string actionStr = action;
	std::map <std::string, std::string> ::iterator it1 = keyActions.find(keyName);
	if (it1 != keyActions.end())
		keyActions[keyName] = action;

	std::map <std::string, std::string> ::iterator it2 = actionKeys.find(action);
	if (it2 != actionKeys.end())
		actionKeys[action] = keyName;
	else
	{
		std::pair<std::string, std::string>insertAction(action, keyName);
		actionKeys.insert(std::pair<std::string, std::string>(insertAction));
	}
}

std::string Hudson::Common::InputManager::getAction(std::string keyName)
{
	std::map <std::string ,std::string> ::iterator it = keyActions.find(keyName);
	if (it != keyActions.end())
		return keyActions[keyName];
}

void Hudson::Common::InputManager::setKeyDown(int key, bool isDown)
{
	std::map<int, bool>::iterator it = keyDown.find(key);
	if (it != keyDown.end())
		keyDown[key] = true;
}

void Hudson::Common::InputManager::setM1Down(bool isDown)
{
	m1Click = isDown;
}

void Hudson::Common::InputManager::setM2Down(bool isDown)
{
	m2Click = isDown;
}

void Hudson::Common::InputManager::setMPos(double mouseX, double mouseY)
{
	mouseXpos = mouseX;
	mouseYpos = mouseY;
}

void Hudson::Common::InputManager::BindCallbacks(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, cursorClickCallback);
}

void Hudson::Common::InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (InputManager* keyInput : instances)
	{
		keyInput->setKeyDown(key, action != GLFW_RELEASE);
	}
	std::cout << key << std::endl;
}

void Hudson::Common::InputManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << xpos << " : " << ypos << std::endl;
	for (InputManager* posInput : instances)
	{
		posInput->setMPos(xpos, ypos);
	}
}

void Hudson::Common::InputManager::cursorClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << button << " has been clicked" << std::endl;
}