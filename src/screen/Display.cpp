//
// Created by paul patault on 17/12/2019.
//

#include "Display.h"

namespace screen {

    void Display::draw2(GLuint programID, data::VBO m_VBO, glm::vec4 colors[], bool newone)
    {
        //int team = 3;
        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            GLint colorID = glGetUniformLocation(programID,"u_color");
            {
                if (team == 0) {
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

            if(newone) {

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, m_VBO.cylindre_vb[0]);
                glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        3,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)nullptr            // array buffer offset
                );
                // Draw the triangle !
                glDrawArrays(GL_TRIANGLES, 0, m_VBO.cylindre_vb.size());

                glDisableVertexAttribArray(0);

            } else {
                for(int j = 0; j < cst::DIV_CYLINDER; j++)
                {
                    glEnableVertexAttribArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, m_VBO.cylindre_vertexbuffer[team][j]);
                    glVertexAttribPointer(
                            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                            3,                  // size
                            GL_FLOAT,           // type
                            GL_FALSE,           // normalized?
                            0,                  // stride
                            (void*)nullptr            // array buffer offset
                    );
                    // Draw the triangle !
                    glDrawArrays(GL_TRIANGLE_STRIP, 0, cst::NB_POINTS );

                    glDisableVertexAttribArray(0);
                }
            }



        }


        /*// ARC.S
        //for(int day = 0; day < 38; day++)
        {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO.arc_vertexbuffer[0]);
            glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)nullptr      // array buffer offset
            );
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 6 ); // * 38

            glDisableVertexAttribArray(0);
        }*/
    }

    void Display::draw(GLuint programID, std::vector<data::VBO> vec_VBO, glm::vec4 *colors)
    {
        //int team = 0;
        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            GLint colorID = glGetUniformLocation(programID,"u_color");
            {
                if (team == 0) {
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
            glBindBuffer(GL_ARRAY_BUFFER, vec_VBO[team].cylindre_vb[0]);
            glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)nullptr      // array buffer offset
            );
            glDrawArrays(GL_TRIANGLES, 0, vec_VBO[team].cylindre_vb.size());

            glDisableVertexAttribArray(0);
        }
    }

    void Display::clear()
    {


        //glClear( GL_COLOR_BUFFER_BIT );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glDepthFunc(GL_ALWAYS);
        glDepthFunc(GL_LESS);


    }

    void Display::update(Render window)
    {
        window.update();
    }


}