//
// Created by paul patault on 17/12/2019.
//

#include "Display.h"

namespace screen {

    /**
     * Envoie puis dessine les cylindres avec leur couleur associé
     * @param programID
     * @param vec_VBO tableau des 20 VBO
     * @param colors couleurs des cylindres
     * @param selected indice de l'équipe selectinnée
     */
    void Display::draw(GLuint programID, std::vector<data::VBO> vec_VBO, glm::vec3 *colors, int select)
    {
        //int team = 0;
        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            GLint colorID = glGetUniformLocation(programID,"u_color");
            {
                if( team == select)
                    glUniform3f(colorID, 0.2, 0.9, 0.2);
                else if (team == 0) {
                    glUniform3f(colorID, colors[0].x, colors[0].y, colors[0].z);              // TOP 1
                } else if (team < 4) {
                    glUniform3f(colorID, colors[1].x, colors[1].y, colors[1].z);              // TOP 1
                } else if (team < 7) {
                    glUniform3f(colorID, colors[2].x, colors[2].y, colors[2].z);              // TOP 1
                } else if (team < 9) {
                    glUniform3f(colorID, colors[3].x, colors[3].y, colors[3].z);              // TOP 1
                } else if (team < 15) {
                    glUniform3f(colorID, colors[4].x, colors[4].y, colors[4].z);              // TOP 1
                } else {
                    glUniform3f(colorID, colors[5].x, colors[5].y, colors[5].z);              // TOP 1
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

    /**
     * Clear la fenetre avec la couleur glClearColor renseignée précédemment
     * et "relance" glDepth
     */
    void Display::clear()
    {
        //glClear( GL_COLOR_BUFFER_BIT );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glDepthFunc(GL_ALWAYS);
        glDepthFunc(GL_LESS);
    }

    /**
     * Regarde les évenements qui influent sur l'affiche actuel
     * @param window classe de la fenetre sur laquel on travail
     * var::selected = l'indice de l'éuipe séléctionnée (si une l'a été), -1 sinon
     */
    void Display::update(Render window)
    {
        window.update();
    }

    /**
     * Séléction d'une équipe a afficher au premier plan
     * @param window fenetre sur laquelle on travail
     * var::selected = l'indice de l'éuipe séléctionnée (si une l'a été), -1 sinon
     */
    void Display::selectionCallBack(GLFWwindow* window, Selection& last_selection) {

        int n_selected = -1;

        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) n_selected = 0;
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) n_selected = 1;
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) n_selected = 2;
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) n_selected = 3;
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) n_selected = 4;
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) n_selected = 5;
        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) n_selected = 6;
        if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) n_selected = 7;
        if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) n_selected = 8;
        if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) n_selected = 9;

        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS and n_selected != -1)
            n_selected += 10;

        last_selection.changed = n_selected != last_selection.selected;
        last_selection.selected = n_selected;
    }

}