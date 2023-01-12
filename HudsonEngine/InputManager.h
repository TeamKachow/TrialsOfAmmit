#pragma once
#include <GLFW/glfw3.h>	
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void getKeyInput(string action);
	void setKeyEvent(string action);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	static std::map<int, string> keys;
};

