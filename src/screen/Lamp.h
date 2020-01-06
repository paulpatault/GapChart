//
// Created by paul patault on 02/01/2020.
//

#ifndef MAIN_LAMP_H
#define MAIN_LAMP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <GL/glew.h>
#include "includes/constants.h"


#include <iostream>
namespace screen {

    class Lamp {
    public:
        explicit Lamp(
                glm::vec3 pos = glm::vec3(glm::vec3(1000.f, 100.f, 2000.f)),
                glm::vec3 lightColor = glm::vec3(glm::vec3(1.f)),
                glm::vec3 color = glm::vec3(glm::vec3(0.92f, 0.53f, 0.f)),
                bool toDisplay = true);

        void setPosition(glm::vec3 apos);

        bool isDisplayable() const;

        GLuint getVAO_ID() const;

        glm::vec3 getPosition() const;

        glm::vec3 getColor() const;

        glm::vec3 getLightColor() const;

        glm::mat4 getModelMatrix() const;

        static void update(Lamp* lamp);

        static void draw_stat(Lamp* lamp);

        static void destroy(Lamp* lamp);

        std::vector<float> vertices;

        ~Lamp();

    private:
        GLuint VAO_ID, VBO_ID;

        glm::vec3 position, lightColor, color;

        bool toDisplay;

        glm::mat4 model;

    };

}



#endif //MAIN_LAMP_H
