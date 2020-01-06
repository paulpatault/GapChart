//
// Created by paul patault on 30/12/2019.
//

#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace screen {

    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    const float YAW   = -90.0f;
    const float PITCH =  0.0f;
    const float SPEED =  2.5f;

    class Camera {
    public:
        explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                float yaw = YAW, float pitch = PITCH );

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        static void processInput(Camera* cam, GLFWwindow *window, float deltaTime);

        glm::mat4 getViewMatrix() const;

        glm::vec3 getPosition() const;

        static void destroy(Camera* cam);

    private:
        glm::vec3 Position,
            Position0,
            Front,
            Up,
            Right,
            WorldUp;

        float Yaw,
            Pitch,
            MovementSpeed = SPEED;

        void reinit();

        void updateCameraVectors();
    };
}



#endif //MAIN_CAMERA_H
