//
// Created by paul patault on 16/12/2019.
//

#include "MVP.h"


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

glm::mat4 MVP::updateMVP()
{
    /// Projection Matrix ///
    float ratio = (float)cst::FSCREEN_WIDTH/cst::FSCREEN_HEIGHT;
    glm::mat4 _projection = glm::perspective(glm::radians(45.f), ratio, zNearFar.x, zNearFar.y );

    /// View Matrix ///
    glm::vec3 eye    = glm::vec3(eyePos);
    glm::vec3 center = glm::vec3(0.f, 0.f, zNearFar.x);
    glm::vec3 up     = glm::vec3(0.f, 1.f, 0.f);
    glm::mat4 _view = glm::lookAt( eye, center, up );

    /// Model Matrix ///
    // rotation
    glm::vec3 xAxis = glm::vec3(1, 0, 0);
    glm::vec3 yAxis = glm::vec3(0, 1, 0);
    glm::vec3 zAxis = glm::vec3(0, 0, 1);
    glm::mat4 _model;
    _model = glm::rotate(Model, glm::radians(angle.x), xAxis);
    _model = glm::rotate(_model, glm::radians(angle.y), yAxis);
    _model = glm::rotate(_model, glm::radians(angle.z), zAxis);
    _model = glm::rotate(_model, glm::radians(-90.f), xAxis);

    // scale
    /*
    glm::vec3 scaleXYZ = vec3(scale);
    Model = glm::scale(Model, scaleXYZ);
    */

    // translation
    glm::vec3 translation = glm::vec3(- cst::FSCREEN_WIDTH/2, - cst::FSCREEN_HEIGHT/2,0.f);
    _model = glm::translate(_model, translation);

    /// ModelViewProjection Matrix ///
    return _projection * _view * _model;
}

glm::mat4 MVP::reInitMVP()
{
    eyePos = glm::vec3(0.f, 0.f, 1000.f);
    zNearFar = glm::vec2(-100.f, 100.f);
    angle = glm::vec3(90.f, 0.f,0.f);

    Projection = glm::mat4(1.0f);
    View = glm::mat4(1.0f);
    Model = glm::mat4(1.0f);

    return updateMVP();
}

glm::mat4 MVP::maj(GLFWwindow *window)
{
    keyboardCallback(window);

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
        return MVP::reInitMVP();

    return MVP::updateMVP();
}

void MVP::init_MatID(GLuint programID)
{
    matrixID = glGetUniformLocation(programID, "u_MVP");
}

GLint MVP::getMatrixID()
{
    return matrixID;
}

void MVP::send_updated(GLFWwindow *window)
{
    glm::mat4 mvp = maj(window);
    glUniformMatrix4fv( matrixID, 1, GL_FALSE, &mvp[0][0] ); // Send new matrix
}
