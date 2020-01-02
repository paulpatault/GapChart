//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_RENDER_H
#define MAIN_RENDER_H

#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "includes/constants.h"


namespace screen {

    class Render {
    public:
        explicit Render(const char* title, glm::vec4 clearColor);

        GLFWwindow* screen;

        void update() const;

        bool shouldNotClose() const;

    };

}


#endif //MAIN_RENDER_H
