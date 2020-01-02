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

    class MVP {
    private:
        glm::vec3 eyePos, angle;
        glm::mat4 model, rotation, view, projection;

        void updateMVP();
        void reInitMVP();
        void keyboardCallback(GLFWwindow* window);

    public:
        MVP();
        void maj(GLFWwindow* window);
        static void maj_stat(MVP* mvp, GLFWwindow* window);
        void send_updated(GLFWwindow* window, data::Shader* shader);
        glm::mat4* getModelMatrix() ;
        glm::mat4* getRotationMatrix() ;
        glm::mat4* getProjectionMatrix() ;

    };

}


#endif //MAIN_MVP_H