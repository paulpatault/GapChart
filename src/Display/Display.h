//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_DISPLAY_H
#define MAIN_DISPLAY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "src/Window/Render.h"
#include "src/VBO/VBO.h"

class Display {
public:
    static void draw(GLuint programID, VBO m_VBO, glm::vec4 colors[]);
    static void clear();
    static void update(Render window);
};


#endif //MAIN_DISPLAY_H
