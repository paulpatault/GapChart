//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_C_IMGUI_H
#define MAIN_C_IMGUI_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "includes/imgui/imgui.h"
#include "includes/imgui/imgui_impl_glfw.h"
#include "includes/imgui/imgui_impl_opengl3.h"


namespace screen {

    class c_ImGui {
    public:
        static void init(GLFWwindow *window);
        static void loop();
        static void maj(glm::vec4 colors[]);
        static void terminate();
    };

}




#endif //MAIN_C_IMGUI_H
