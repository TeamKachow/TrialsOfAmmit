#pragma once

// Pre-compiled header.
// 
// IMPORTANT: Put all your "library" includes here, and then include them from here.
// This includes C/C++ standard libraries, and any dependencies we're including

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

// C
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// C++
#include <chrono>
#include <codecvt>
#include <concepts>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>


// Boost
// TODO


// GLAD (OpenGL)
#include <glad/glad.h>


// GLFW
#include <GLFW/glfw3.h>


// GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// JSON
#include <json.hpp>
#include "GlmJsonFunctions.h"

// STB
#include <stb-master/stb_image.h>


// ImGui
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_stdlib.h"

// irrKlang
#include <irrKlang/irrKlang.h>

// Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

// Filesystem
#include <filesystem>
