//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_DISPLAY_H
#define MAIN_DISPLAY_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Render.h"
#include "src/data/VBO.h"
#include "includes/constants.h"

namespace screen {

    class Display {
    public:
        static int teamSelectCallBack(GLFWwindow *window);
        static void draw(GLuint programID, std::vector<data::VBO> vec_VBO, glm::vec4 colors[], int selected);
        static void clear();
        static int update(Render window);
    };

}




#endif //MAIN_DISPLAY_H
