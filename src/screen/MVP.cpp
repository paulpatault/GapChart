//
// Created by paul patault on 16/12/2019.
//

#include "MVP.h"

namespace screen {

    MVP::MVP()
    {
        eyePos = glm::vec3(0.f, 0.f, 1000.f);
        angle = glm::vec3(90.f, 0.f,0.f);

        model = glm::mat4(1.0f);
        rotation = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
    }

    /**
     * Gere des evenements clavier qui actualise la matrice Model View Projection
     * @param window fenetre de travail
     */
    void MVP::keyboardCallback(GLFWwindow* window)
    {
        // rotation
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
            angle.x += 0.5f;
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
            angle.x -= 0.5f;
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
            angle.z += 0.5f;
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
            angle.z -= 0.5f;
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
            angle.y += 0.5f;
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            angle.y -= 0.5f;

    }

    /**
     * Mise a jour de la matrice MVP après modification de ces paramètres par keyboardCallback
     */
    void MVP::updateMVP()
    {
        /// Model Matrix ///
        // rotation
        glm::vec3 xAxis = glm::vec3(1, 0, 0);
        glm::vec3 yAxis = glm::vec3(0, 1, 0);
        glm::vec3 zAxis = glm::vec3(0, 0, 1);

        rotation = glm::mat4(1.0f);
        rotation = glm::rotate(rotation, glm::radians(angle.x), xAxis);
        rotation = glm::rotate(rotation, glm::radians(angle.y), yAxis);
        rotation = glm::rotate(rotation, glm::radians(angle.z), zAxis);
        rotation = glm::rotate(rotation, glm::radians(-90.f), xAxis);

        // translation
        glm::vec3 translation = glm::vec3(- cst::FSCREEN_WIDTH/2, - cst::FSCREEN_HEIGHT/2,0.f);
        model = glm::translate(glm::mat4(1.0f), translation);


        /// View Matrix ///
        glm::vec3 eye    = glm::vec3(eyePos);
        glm::vec3 center = glm::vec3(0.f, 0.f, cst::Z_NEAR);
        glm::vec3 up     = glm::vec3(0.f, 1.f, 0.f);
        view = glm::lookAt( eye, center, up );


        /// Projection Matrix ///
        float ratio = (float) cst::FSCREEN_WIDTH / cst::FSCREEN_HEIGHT;
        projection = glm::perspective(glm::radians(45.f), ratio, cst::Z_NEAR, cst::Z_FAR );

    }

    /**
     * Remets MVP "à zéro" := position de base lorsqu'on lance le code
     */
    void MVP::reInitMVP()
    {
        eyePos = glm::vec3(0.f, 0.f, 1000.f);
        angle = glm::vec3(90.f, 0.f,0.f);

        updateMVP();
    }

    /**
     * Mise a jour de MVP après sa réinitialisatio ou modification par keyboardCallback
     * @param window fenetre de travail
     */
    void MVP::maj(GLFWwindow* window)
    {
        keyboardCallback(window);

        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
            reInitMVP();
        else
            updateMVP();
    }

    /**
     * Mise a jour de MVP après sa réinitialisatio ou modification par keyboardCallback
     * @param mvp instance de MVP
     * @param window fenetre de travail
     */
    void MVP::maj_stat(MVP* mvp, GLFWwindow* window)
    {
        mvp->keyboardCallback(window);

        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
            mvp->reInitMVP();
        else
            mvp->updateMVP();
    }

    /**
     * Envoie les matrices Model, View et Projection aux shaders
     * @param window fenetre de travail
     */
    void MVP::send_updated(GLFWwindow* window, data::Shader* shader)
    {
        maj(window);
        shader->setMat4("u_Model", model);
        shader->setMat4("u_Rotate", rotation);
        shader->setMat4("u_View", view);
        shader->setMat4("u_Projection", projection);
    }

    glm::mat4* MVP::getModelMatrix()
    {
        return &model;
    }

    glm::mat4* MVP::getRotationMatrix()
    {
        return &rotation;
    }

    glm::mat4* MVP::getProjectionMatrix()
    {
        return &projection;
    }

}