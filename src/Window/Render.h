//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_RENDER_H
#define MAIN_RENDER_H

#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "headers/constants.h"
using namespace cst;

class Render {
public:
    Render();

    GLFWwindow* render;

    void update();

    bool shouldNotClose();

};


#endif //MAIN_RENDER_H
