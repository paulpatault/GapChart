//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_MVP_H
#define MAIN_MVP_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <src/data/Shader.h>
#include "includes/constants.h"

namespace screen {

    static glm::vec3 eyePos = glm::vec3(0.f, 0.f, 1000.f);
    static glm::vec2 zNearFar = glm::vec2(-100.f, 100.f);
    static glm::vec3 angle = glm::vec3(90.f, 0.f,0.f);

    class MVP {
    private:
        static void updateMVP(glm::mat4* mvp);
        static void reInitMVP(glm::mat4* mvp);
        static void maj(GLFWwindow* window, glm::mat4* mvp);
        static void keyboardCallback(GLFWwindow* window);
    public:
        static void send_updated(GLFWwindow* window, data::Shader* shader);

    };

}


#endif //MAIN_MVP_H