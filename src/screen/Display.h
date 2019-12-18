//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_DISPLAY_H
#define MAIN_DISPLAY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Render.h"
#include "src/data/VBO.h"
#include "includes/constants.h"

namespace screen {

    class Display {
    public:
        static void draw(GLuint programID, data::VBO m_VBO, glm::vec4 colors[]);
        static void clear();
        static void update(Render window);
    };

}




#endif //MAIN_DISPLAY_H
