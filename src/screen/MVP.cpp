//
// Created by paul patault on 16/12/2019.
//

#include "MVP.h"

namespace screen {

    void MVP::keyboardCallback(GLFWwindow *window)
    {
        // rotation
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            angle.x += 0.5f;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            angle.x -= 0.5f;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            angle.z += 0.5f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            angle.z -= 0.5f;

        // deplacement
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Z
            eyePos.y += 2.f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // S
            eyePos.y -= 2.f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Q
            eyePos.x -= 2.f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // D
            eyePos.x += 2.f;


        // zoom
        if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
            eyePos.z += 2.f;
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            eyePos.z -= 2.f;
    }

    void MVP::updateMVP(glm::mat4 MPV[])
    {
        /// Model Matrix ///
        // rotation
        glm::vec3 xAxis = glm::vec3(1, 0, 0);
        glm::vec3 yAxis = glm::vec3(0, 1, 0);
        glm::vec3 zAxis = glm::vec3(0, 0, 1);

        MPV[0] = glm::rotate(glm::mat4(1.0f), glm::radians(angle.x), xAxis);
        MPV[0] = glm::rotate(MPV[0], glm::radians(angle.y), yAxis);
        MPV[0] = glm::rotate(MPV[0], glm::radians(angle.z), zAxis);
        MPV[0] = glm::rotate(MPV[0], glm::radians(-90.f), xAxis);

        // translation
        glm::vec3 translation = glm::vec3(- cst::FSCREEN_WIDTH/2, - cst::FSCREEN_HEIGHT/2,0.f);
        MPV[0] = glm::translate(MPV[0], translation);

        /// View Matrix ///
        glm::vec3 eye    = glm::vec3(eyePos);
        glm::vec3 center = glm::vec3(0.f, 0.f, zNearFar.x);
        glm::vec3 up     = glm::vec3(0.f, 1.f, 0.f);
        MPV[1] = glm::lookAt( eye, center, up );


        /// Projection Matrix ///
        float ratio = (float)cst::FSCREEN_WIDTH/cst::FSCREEN_HEIGHT;
        MPV[2] = glm::perspective(glm::radians(45.f), ratio, zNearFar.x, zNearFar.y );

    }

    void MVP::reInitMVP(glm::mat4 MPV[])
    {
        eyePos = glm::vec3(0.f, 0.f, 1000.f);
        zNearFar = glm::vec2(-100.f, 100.f);
        angle = glm::vec3(90.f, 0.f,0.f);

        MPV[0] = glm::mat4(1.0f);
        MPV[1] = glm::mat4(1.0f);
        MPV[2] = glm::mat4(1.0f);

        updateMVP(MPV);
    }

    void MVP::maj(GLFWwindow *window, glm::mat4 MPV[])
    {
        keyboardCallback(window);

        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
            MVP::reInitMVP(MPV);
        else
            MVP::updateMVP(MPV);
    }

    void MVP::setLocation(GLuint programID)
    {
        model_id = glGetUniformLocation(programID, "u_Model");
        view_id = glGetUniformLocation(programID, "u_View");
        projection_id = glGetUniformLocation(programID, "u_Projection");
    }

    void MVP::send_updated(GLFWwindow *window)
    {
        glm::mat4 mvp[3];
        maj(window, mvp);
        glUniformMatrix4fv(model_id, 1, GL_FALSE, &mvp[0][0][0] );
        glUniformMatrix4fv(view_id, 1, GL_FALSE, &mvp[1][0][0] );
        glUniformMatrix4fv(projection_id, 1, GL_FALSE, &mvp[2][0][0] );
    }


}