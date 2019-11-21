//
// Created by paul patault on 21/11/2019.
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


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


GLFWwindow* initWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT);

#endif //MAIN_WINDOW_H
