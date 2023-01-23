#pragma once

// Pre-compiled header.
// 
// IMPORTANT: Put all your "library" includes here, and then include them from here.
// This includes C/C++ standard libraries, and any dependencies we're including (imgui/glad/glfw/boost/cereal)

// C
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// C++
#include <chrono>
#include <concepts>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>


// Boost
// TODO


// Cereal
// TODO include


// GLAD (OpenGL)
#include <glad/glad.h>


// GLFW
#include <GLFW/glfw3.h>


// GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// STB
#include <stb-master/stb_image.h>


// ImGui
#include"../imgui/imgui.h"
#include"../imgui/imgui_impl_glfw.h"
#include"../imgui/imgui_impl_opengl3.h"
