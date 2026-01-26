//
// Created by abnaclut on 25.01.2026.
//
#pragma once
#ifndef OPENTEMPLATE_INCLUDES_H

// UNIVERSAL INCLUDE HEADER

//standard
#include <iostream>
#include <ostream>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <algorithm>
#include <type_traits>

//OpenGL
#ifndef GLAD_INCLUDED
#include "../../external/glad/include/glad/glad.h"
#define GLAD_INCLUDED
#endif

//glm
#include "../../external/glm/glm/glm.hpp"
#include "../../external/glm/glm/gtc/type_ptr.hpp"
#include "../../external/glm/glm/vec2.hpp"
#include "../glm/gtc/matrix_transform.hpp"

//GLFW
#include "../../../external/glfw/include/GLFW/glfw3.h"

#define OPENTEMPLATE_INCLUDES_H

#endif //OPENTEMPLATE_INCLUDES_H