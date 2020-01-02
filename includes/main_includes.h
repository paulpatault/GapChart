//
// Created by paul patault on 21/12/2019.
//

#ifndef MAIN_MAIN_INCLUDES_H
#define MAIN_MAIN_INCLUDES_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
#else
    #include <GL/gl.h>
#endif

// namespace var
#include "includes/variables.h"
#include "includes/utils.h"

// namespace data
#include "src/data/LoadData.h"
#include "src/data/Cylinder.h"
#include "src/data/Arc.h"
#include "src/data/Shader.h"
#include "src/data/VAO.h"
#include "src/data/VBO.h"
#include "src/data/Texture.h"

// namespace screen
#include "src/screen/MVP.h"
#include "src/screen/c_ImGui.h"
#include "src/screen/Render.h"
#include "src/screen/Display.h"
#include "src/screen/Lamp.h"
#include "src/screen/Camera.h"


#endif //MAIN_MAIN_INCLUDES_H

