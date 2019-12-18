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
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "includes/constants.h"


namespace screen {

    class Render {
    public:
        Render();

        GLFWwindow* render;

        void update();

        bool shouldNotClose();

    };

}


#endif //MAIN_RENDER_H
