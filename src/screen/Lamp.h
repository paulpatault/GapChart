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

namespace screen {

    class Lamp {
    public:
        explicit Lamp(glm::vec3 pos = glm::vec3(cst::FSCREEN_WIDTH / 2, 5000, 1000.f), bool toDisplay = true);
        glm::vec3 getPosition() const;
        void setPosition(glm::vec3 apos);
        bool isDisplayable() const;
        GLuint getVAO_ID() const;
        glm::mat4 getModelMatrix() const;
        static void update(Lamp* lamp);
        static void draw(Lamp* lamp);
        std::vector<float> vertices;

    private:
        GLuint VAO_ID;
        GLuint VBO_ID;
        glm::vec3 position;
        bool toDisplay;
        glm::mat4 model;

    };

}



#endif //MAIN_LAMP_H
