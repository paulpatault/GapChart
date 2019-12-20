//
// Created by paul patault on 17/12/2019.
//

#include "Display.h"

namespace screen {

    void Display::draw(GLuint programID, std::vector<data::VBO> vec_VBO, glm::vec4 *colors, int selected)
    {
        //int team = 0;
        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            GLint colorID = glGetUniformLocation(programID,"u_color");
            {
                if( team == selected)
                    glUniform4f(colorID, 0.2, 0.9, 0.2, 1.f);
                else if (team == 0) {
                    glUniform4f(colorID, colors[0].x, colors[0].y, colors[0].z, colors[0].w);              // TOP 1
                } else if (team < 4) {
                    glUniform4f(colorID, colors[1].x, colors[1].y, colors[1].z, colors[1].w);              // TOP 1
                } else if (team < 7) {
                    glUniform4f(colorID, colors[2].x, colors[2].y, colors[2].z, colors[2].w);              // TOP 1
                } else if (team < 9) {
                    glUniform4f(colorID, colors[3].x, colors[3].y, colors[3].z, colors[3].w);              // TOP 1
                } else if (team < 15) {
                    glUniform4f(colorID, colors[4].x, colors[4].y, colors[4].z, colors[4].w);              // TOP 1
                } else {
                    glUniform4f(colorID, colors[5].x, colors[5].y, colors[5].z, colors[5].w);              // TOP 1
                }
            }

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vec_VBO[team].t_combined_data[0]);
            glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)nullptr      // array buffer offset
            );

            glEnableVertexAttribArray(vec_VBO[team].size_of_cylinder * sizeof(float));
            glBindBuffer(GL_ARRAY_BUFFER, vec_VBO[team].t_combined_data[0]);
            glVertexAttribPointer(
                    1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)nullptr      // array buffer offset
            );

            glDrawArrays(GL_TRIANGLES, 0, vec_VBO[team].t_combined_data.size());
        }
    }

    void Display::clear()
    {
        //glClear( GL_COLOR_BUFFER_BIT );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glDepthFunc(GL_ALWAYS);
        glDepthFunc(GL_LESS);
    }

    int Display::update(Render window)
    {
        int selected = teamSelectCallBack(window.render);
        window.update();
        return selected;
    }

    int Display::teamSelectCallBack(GLFWwindow *window) {
        int selected = -1;
        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) selected = 0;
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) selected = 1;
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) selected = 2;
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) selected = 3;
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) selected = 4;
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) selected = 5;
        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) selected = 6;
        if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) selected = 7;
        if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) selected = 8;
        if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) selected = 9;

        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 10;
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 11;
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 12;
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 13;
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 14;
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 15;
        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 16;
        if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 17;
        if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 18;
        if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS
            and glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            selected = 19;

        return selected;

    }


}