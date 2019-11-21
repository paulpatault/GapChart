//
// Created by paul patault on 20/11/2019.
//

#ifndef MAIN_ESCALIER_H
#define MAIN_ESCALIER_H

// Include standard headers
#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "LoadData.h"


std::vector<float> y_Escalier(LoadData myData, int team, float SCREEN_HEIGHT);

void tabEscalier(float vertices[], const int NUMBER_OF_POINTS, const float epaisseur, const float dx, vector<float>  coordCenter);

void escalierV0(vec3 begin, vec3 end, float vertices[], int NUMBER_OF_POINTS, float epaisseur, int winloose[]);

#endif //MAIN_ESCALIER_H
