#include "InputManager.h"

vector<InputManager*> InputManager::instances;

InputManager::InputManager()
{
	initialiseKeys();
	InputManager::instances.push_back(this);
}

InputManager::~InputManager()
{
	instances.erase(remove(instances.begin(), instances.end(), this), instances.end());
}

void InputManager::initialiseKeys()
{
	int keyCodes[] = { 32, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72,
				  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 256,
				  262, 263, 264, 265 };
	for (int key : keyCodes)
	{
		string keyName;
		string action = "Not Assigned";
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
		pair<string, int>keyInsert(keyName, key);
		pair<string, int>actionInsert(action, key);
		keys.insert(keyInsert);
		keyActions.insert(pair<string, int>(actionInsert));
		keyDown[key] = false;
	}

}

bool InputManager::getKeyInput(GLFWwindow* window, string action)
{
	int actionKey = keyActions.find(action)->second;
	return true;
}

void InputManager::setKeyDown(int key, bool isDown)
{
	map<int, bool>::iterator it = keyDown.find(key);
	if (it != keyDown.end())
		keyDown[key] = true;
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (InputManager* keyInput : instances)
	{
		keyInput->setKeyDown(key, action != GLFW_RELEASE);
	}
	cout << key << endl;
}

