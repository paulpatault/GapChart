//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_MVP_H
#define MAIN_MVP_H

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Include
#include "includes/constants.h"

static glm::vec3 eyePos = glm::vec3(0.f, 0.f, 1000.f);
static glm::vec2 zNearFar = glm::vec2(-100.f, 100.f);
static glm::vec3 angle = glm::vec3(90.f, 0.f,0.f);

static glm::mat4 Projection = glm::mat4(1.0f);
static glm::mat4 View = glm::mat4(1.0f);
static glm::mat4 Model = glm::mat4(1.0f);

class MVP {
private:

    static glm::mat4 updateMVP();

    static glm::mat4 reInitMVP();

    static void keyboardCallback(GLFWwindow *window);

public:
    static glm::mat4 actu(GLFWwindow *window);

};


#endif //MAIN_MVP_H
