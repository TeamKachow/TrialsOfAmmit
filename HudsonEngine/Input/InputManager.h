#pragma once
#include "../Util/stdafx.h"
#include <iostream>
#include <cstring>
#include "json.hpp"

struct Key
{
	std::string keyName;
	std::vector<std::string> keyActions;
	int keyID;
	bool keyDown;
};

namespace Hudson::Input
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		std::vector<std::string> getKeyActions(std::string keyName);
		void setKeyEvent(std::string action, std::string keyName);
		void delKeyEvent(std::string action, std::string keyName);

		bool getActionState(std::string action);

		void setDownTemp(std::string keyName);

		void LoadJSON();
		void WriteToJSON();

		static void BindCallbacks(GLFWwindow* window);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void cursorClickCallback(GLFWwindow* window, int button, int action, int mods);


	private:
		std::vector<Key> keys;
		bool m1Click;
		bool m2Click;
		double mouseXpos;
		double mouseYpos;
		static std::vector<InputManager*> instances;

		void initialiseKeys();
		void setKeyDown(int key, bool isDown);
		void setCursorPos(double xPos, double yPos);
		void setM1Click(bool isDown);
		void setM2Click(bool isDown);
	};
}


