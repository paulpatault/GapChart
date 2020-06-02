//
// Created by paul patault on 30/12/2019.
//

#include "Camera.h"


namespace screen {


    /**
     * Constructeur de la classe
     * @param position initiale
     * @param up sens
     * @param yaw angle selon y
     * @param pitch angle selon x
     */
    Camera::Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    {
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        Position = position;
        Position0 = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        glfwGetCursorPos(window, &lastX, &lastY);
        updateCameraVectors();
    }

    /**
     * Gere le déplacement de la camera
     * @param cam la camera a deplacer
     * @param window fenetre de travail
     */
    void Camera::processInput(Camera* cam, GLFWwindow* window, float deltaTime)
    {
        // réajustement de la vitesse de déplacement
        deltaTime *= 10;

        /// ZQSD
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cam->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cam->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cam->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cam->ProcessKeyboard(RIGHT, deltaTime);

        /// UP DOWN
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
            cam->ProcessKeyboard(DOWN, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            cam->ProcessKeyboard(UP, deltaTime);

        /// YAW & PITCH
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cam->Yaw -= 0.01f * cam->MovementSpeed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cam->Yaw += 0.01f * cam->MovementSpeed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cam->Pitch -= 0.01f * cam->MovementSpeed;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cam->Pitch += 0.01f * cam->MovementSpeed;

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        float xDiff = (float)cam->lastX - (float)xPos;
        float yDiff = (float)cam->lastY - (float)yPos;

        cam->lastX = (float)xPos;
        cam->lastY = (float)yPos;

        cam->Yaw -= xDiff;
        cam->Pitch += yDiff;

        /// increase MovementSpeed
        if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS and cam->MovementSpeed > 0.2f) // > 0.2 pour ne pas avoir une vitesse négative
            cam->MovementSpeed -= 0.1f;
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            cam->MovementSpeed += 0.1f;

        /// REINITIALISATION
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) // A
            cam->reinit();

        cam->updateCameraVectors();
    }

    /**
     * Replace la camera a sa position initiale et réinitialise la vitesse de déplacement
     */
    void Camera::reinit()
    {
        MovementSpeed = SPEED;
        Position = Position0;
        Yaw = YAW;
        Pitch = PITCH;
    }

    /**
     * Update la position de la camera en fonction de l'input clavier
     * @param direction de déplacement
     * @param deltaTime pour la vitesse de déplacement
     */
    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;

        if (direction == UP)
            Position += Up * velocity;
        if (direction == DOWN)
            Position -= Up * velocity;

    }

    /**
     * Uptades des attributs de la camera
     */
    void Camera::updateCameraVectors()
    {
        // On calcule le nouveau vec3 front
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // idem pour right et up
        // -> Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }

    /**
     * @return Position actuelle de la camera
     */
    glm::vec3 Camera::getPosition(const Camera* cam)
    {
        return cam->Position;
    }

    glm::vec3 Camera::getPosition()
    {
        return Position;
    }

    /**
     * Matrice de vue calculée avec les angles d'euler et la matrice LookAt
     * @return view matrix
     */
    glm::mat4 Camera::getViewMatrix(const Camera* cam)
    {
        return glm::lookAt(cam->Position, cam->Position + cam->Front, cam->Up);
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    /**
     * delete
     * @param cam a détruire
     */
    void Camera::destroy(Camera* cam)
    {
        delete cam;
    }

}