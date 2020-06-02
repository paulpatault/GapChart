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
        static void selectionCallBack(GLFWwindow* window, Selection& last_selection);

        static void draw(GLuint programID, const std::vector<data::VBO>& vec_VBO, const glm::vec3 *colors, const Selection& select);

        static void clear();

        static void update(const Render* window);

    };

}




#endif //MAIN_DISPLAY_H
