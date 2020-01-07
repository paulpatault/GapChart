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

        static void maj(MVP* mvp, GLFWwindow* window);

        glm::mat4* p_getModelMatrix();

        glm::mat4* p_getRotationMatrix();

        glm::mat4* p_getProjectionMatrix();

        static glm::mat4 getModelMatrix(const MVP* mvp);

        static glm::mat4 getRotationMatrix(const MVP* mvp);

        static glm::mat4 getProjectionMatrix(const MVP* mvp);

        static void destroy(const MVP* pMVP);

    };

}


#endif //MAIN_MVP_H