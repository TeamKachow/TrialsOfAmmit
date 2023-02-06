#include "InputManager.h"
#include "../Render/Renderer.h"
#include "../Render/Window.h"

using nlohmann::json;

void to_json(json& j, const Key& key)
{
	j = json{
		{"Name", key.keyName},
		{"Actions", key.keyActions},
		{"KeyID", key.keyID},
		{"KeyDown", key.keyDown}
	};
}

void from_json(const json& j, Key& key)
{
	j.at("Name").get_to(key.keyName);
	j.at("Actions").get_to(key.keyActions);
	j.at("KeyID").get_to(key.keyID);
	j.at("KeyDown").get_to(key.keyDown);
}

using namespace Hudson::Input;

std::vector<InputManager*> InputManager::instances;


InputManager::InputManager()
{
	initialiseKeys();
	InputManager::instances.push_back(this);
}

InputManager::~InputManager()
{
	instances.erase(remove(instances.begin(), instances.end(), this), instances.end());
}

void Hudson::Input::InputManager::Setup(Hudson::Render::Renderer* renderer)
{
	renderRef = renderer;
	BindCallbacks(renderer->GetWindow()->GetWindow());
	ImGui_ImplGlfw_InstallCallbacks(renderer->GetWindow()->GetWindow());

}

void InputManager::initialiseKeys()
{
	std::ifstream file("KeyMappings.json");
	if (!file.fail())
	{
		json j = json::parse(file);
		keys = j;
		file.close();
	}
	else
	{
		std::cout << "File containing mapped key actions failed to load!" << std::endl;
		int keyCodes[] = { 32, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72,
				  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 256,
				  262, 263, 264, 265 };
		for (int key : keyCodes)
		{
			std::string keyName;
			std::string action = "Not Assigned";
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

			Key addKey;
			addKey.keyName = keyName;
			addKey.keyID = key;
			addKey.keyDown = false;
			keys.push_back(addKey);
		}

	}

}

void InputManager::setKeyEvent(std::string action, std::string keyName)
{
	for (Key& tempKey : keys)
	{
		if (tempKey.keyName == keyName)
		{
			if (std::find(tempKey.keyActions.begin(), tempKey.keyActions.end(), action) == tempKey.keyActions.end())
			{
				tempKey.keyActions.push_back(action);
			}
		}
	}
}

void Hudson::Input::InputManager::delKeyEvent(std::string action, std::string keyName)
{
	for (Key& tempKey : keys)
	{
		if (tempKey.keyName == keyName)
		{
			tempKey.keyActions.erase(std::remove(tempKey.keyActions.begin(), tempKey.keyActions.end(), action), tempKey.keyActions.end());
		}
	}
}

bool Hudson::Input::InputManager::getActionState(std::string action)
{
	for (Key tempKey : keys)
	{
		if (std::find(tempKey.keyActions.begin(), tempKey.keyActions.end(), action) != tempKey.keyActions.end())
		{
			return tempKey.keyDown;
		}
	}
	return false;
}

void InputManager::setWorldCursorPos(GLFWwindow* window, glm::mat4 inverseProjMat)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glm::vec3 win(screenMouseXpos, screenMouseYpos, 0);
	glm::vec4 viewport(0, 0, width, height);

	glm::vec2 screenPos = glm::unProject(win, glm::mat4(1), glm::mat4(1), viewport);
	glm::vec4 positionClip = glm::vec4(screenPos.x, -screenPos.y, -1.0f, 1.0f);
	glm::vec4 worldPos = inverseProjMat * positionClip;

	//worldPos = glm::normalize(worldPos);


	worldMouseXpos = worldPos.x;
	worldMouseYpos = worldPos.y;

	//return glm::vec2(worldPos.x, worldPos.y);
}

void Hudson::Input::InputManager::setDownTemp(std::string keyName)
{
	for (Key& tempKey : keys)
	{
		if (tempKey.keyName == keyName)
		{
			tempKey.keyDown = true;
		}
	}
}

void Hudson::Input::InputManager::LoadJSON()
{
	std::ifstream file("KeyMappings.json");
	json j = json::parse(file);
	keys = j;
	file.close();

}

void Hudson::Input::InputManager::WriteToJSON()
{
	json j;
	std::ofstream file("KeyMappings.json");
	if (file.is_open())
	{
		for (Key& key : keys)
		{
			j.push_back(key);
		}
		file << std::setw(4) << j << std::endl;
		file.flush();
		file.close();
	}
}

std::vector<std::string> InputManager::getKeyActions(std::string keyName)
{
	for (Key tempKey : keys)
	{
		if (tempKey.keyName == keyName)
		{
			return tempKey.keyActions;
		}
	}
}

void InputManager::setKeyDown(int key, bool isDown)
{
	for (Key& tempKey : keys)
	{
		if (tempKey.keyID == key)
		{
			tempKey.keyDown = isDown;
		}
	}
}

void Hudson::Input::InputManager::setScreenCursorPos(double xPos, double yPos)
{
	screenMouseXpos = xPos;
	screenMouseYpos = yPos;
}

void Hudson::Input::InputManager::setM1Click(bool isDown)
{
	m1Click = isDown;
}

void Hudson::Input::InputManager::setM2Click(bool isDown)
{
	m2Click = isDown;
}


void InputManager::BindCallbacks(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, cursorClickCallback);
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (InputManager* keyInput : instances)
	{
		keyInput->setKeyDown(key, action != GLFW_RELEASE);
	}
}

void InputManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	for (InputManager* instance : instances)
	{
		instance->setScreenCursorPos(xpos, ypos);
		// Make Sure Setup has been called for this to work
		if (instance->renderRef != nullptr)
			if (instance->renderRef->GetCamera() != nullptr)
				instance->setWorldCursorPos(window, instance->renderRef->GetCamera()->GetInverseViewProjectionMatrix());

		//std::cout << instance->getWorldMPos().x << " " << instance->getWorldMPos().y << std::endl;
	}
	
}

void InputManager::cursorClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	for (InputManager* cursorClick : instances)
	{
		if (button == 0)
		{
			cursorClick->setM1Click(action != GLFW_RELEASE);
		}
		else if (button == 1)
		{
			cursorClick->setM1Click(action != GLFW_RELEASE);
		}
	}
}