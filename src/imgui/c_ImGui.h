//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_C_IMGUI_H
#define MAIN_C_IMGUI_H

// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
// Include ImGui
#include "src/imgui/imgui.h"
#include "src/imgui/imgui_impl_glfw.h"
#include "src/imgui/imgui_impl_opengl3.h"

class c_ImGui {
public:
    static void init(GLFWwindow *window);
    static void loop();
    static void maj(glm::vec4 colors[]);
    static void terminate();
};


#endif //MAIN_C_IMGUI_H
