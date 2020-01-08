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
    void Display::draw(GLuint programID, const std::vector<data::VBO>& vec_VBO, const glm::vec3 *colors, const Selection& select)
    {
        for(int team = 0; team < cst::NB_TEAMS; team++)
        {

            if (team == select.selected) {
                glUniform3fv(glGetUniformLocation(programID, "u_color"), 1, &glm::vec3(0.1, 0.6, 0.1)[0]);
            } else if (team == 0) {
                glUniform3fv(glGetUniformLocation(programID, "u_color"), 1, &colors[0][0]);              // TOP 1
            } else if (team < 4) {
                glUniform3fv(glGetUniformLocation(programID, "u_color"), 1, &colors[1][0]);              // TOP
            } else if (team < 7) {
                glUniform3fv(glGetUniformLocation(programID, "u_color"), 1, &colors[2][0]);              // TOP_MID
            } else if (team < 9) {
                glUniform3fv(glGetUniformLocation(programID, "u_color"), 1, &colors[3][0]);              // MID
            } else if (team < 15) {
                glUniform3fv(glGetUniformLocation(programID, "u_color"), 1, &colors[4][0]);              // BOT_MID
            } else {
                glUniform3fv(glGetUniformLocation(programID, "u_color"), 1, &colors[5][0]);              // BOT
            }


            glBindBuffer(GL_ARRAY_BUFFER, vec_VBO[team].t_combined_data[0]);
            glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)nullptr      // array buffer offset
            );
            glEnableVertexAttribArray(0);


            glBindBuffer(GL_ARRAY_BUFFER, vec_VBO[team].t_combined_data[0]); // optional
            glVertexAttribPointer(
                    1,                  // attribute 1 match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)(vec_VBO[team].t_combined_data[vec_VBO[team].size_of_cylinder] * sizeof(float))      // array buffer offset
            );
            glEnableVertexAttribArray(1);


            glDrawArrays(GL_TRIANGLES, 0, vec_VBO[team].size_of_cylinder);
        }
    }

    /**
     * Clear la fenetre avec la couleur glClearColor renseignée précédemment
     * et garde glDepth
     */
    void Display::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
    }

    /**
     * Regarde les évenements qui influent sur l'affiche actuel
     * @param window classe de la fenetre sur laquel on travail
     */
    void Display::update(const Render* window)
    {
        window->update();
    }

    /**
     * Séléction d'une équipe a afficher au premier plan
     * @param window fenetre sur laquelle on travail
     * @param last_selection sera mis a jour si la séléction change, sera cst sinon, et enfin on "mettra" -1 si la séléction et finie
     */
    void Display::selectionCallBack(GLFWwindow* window, Selection& last_selection)
    {
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