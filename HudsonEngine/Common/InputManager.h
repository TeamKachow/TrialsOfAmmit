#pragma once
#include "../Util/stdafx.h"
#include <string>

namespace Hudson::Common
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		bool getKeyInput(std::string action);
		void setKeyEvent(std::string action, std::string keyName);
		std::string getAction(std::string keyName);

		static void BindCallbacks(GLFWwindow* window);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void cursorClickCallback(GLFWwindow* window, int button, int action, int mods);


	private:
		std::map<std::string, int> keys;
		std::map<std::string, std::string> keyActions;
		std::map<std::string, std::string> actionKeys;
		std::map<int, bool> keyDown;
		bool m1Click;
		bool m2Click;
		double mouseXpos;
		double mouseYpos;
		static std::vector<InputManager*> instances;

		void initialiseKeys();
		void setKeyDown(int key, bool isDown);
		void setM1Down(bool isDown);
		void setM2Down(bool isDown);
		void setMPos(double mouseX, double mouseY);
	};
}

