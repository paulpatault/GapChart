//
// Created by paul patault on 30/12/2019.
//

#include "Camera.h"


namespace screen {

    // Constructor with vectors
    Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    {
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        Position = position;
        Position0 = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 Camera::getViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void Camera::processInput(Camera* cam, GLFWwindow *window, float deltaTime)
    {
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
        if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
            cam->ProcessKeyboard(DOWN, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            cam->ProcessKeyboard(UP, deltaTime);

        /// YAW PITCH
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cam->Yaw -= 0.01f * cam->MovementSpeed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cam->Yaw += 0.01f * cam->MovementSpeed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cam->Pitch -= 0.01f * cam->MovementSpeed;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cam->Pitch += 0.01f * cam->MovementSpeed;

        /// increase MovementSpeed
        if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS and cam->MovementSpeed > 0.2f)
            cam->MovementSpeed -= 0.1f;
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            cam->MovementSpeed += 0.1f;

        /// REINITIALISATION
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) // A
            cam->reinit();

        cam->updateCameraVectors();
    }

    void Camera::reinit()
    {
        MovementSpeed = SPEED;
        Position = Position0;
        Yaw = YAW;
        Pitch = PITCH;
    }

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

    void Camera::updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }

    glm::vec3* Camera::getPosition()
    {
        return &Position;
    }

}