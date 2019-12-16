// Include standard headers
#include <cmath>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


// My includes
#include "src/LoadData/LoadData.h"
#include "includes/debugbreak.h"
#include "src/Shaders/Shaders.h"
#include "src/MPV/MVP.h"
#include "includes/constants.h"
#include "src/imgui/c_ImGui.h"
#include "src/Window/Render.h"


void loadVBO_arc(GLuint arc_vertexbuffer[38], GLfloat t_vertex_data_dim3[cst::NB_TEAMS][cst::DIV_CYLINDER][cst::NB_POINTS * 3], LoadData myData, int choice)
{
    GLfloat t_vertex_arc[cst::NB_DAYS][6*3];

    const float sousEpaisseur = cst::THICKNESS / 6 ;
    const float sousDx = cst::dx * 2;
    const float x0 = 50 + cst::dx *3;

    for(int day = 0; day < 38; day++)
    {
        float x = x0 + day * sousDx;
        for(int i = 0; i < 6*3; i+=6)
        {
            /*
            t_vertex_arc[day][0] = x;
            t_vertex_arc[day][1] = t_vertex_data_dim3[choice][0][0];
            t_vertex_arc[day][2] = 0;

            t_vertex_arc[day][3] = x + sousEpaisseur;
            t_vertex_arc[day][4] = t_vertex_arc[day][1];
            t_vertex_arc[day][5] = 0;

            t_vertex_arc[day][6] = x;
            t_vertex_arc[day][7] = t_vertex_data_dim3[choice][0][0];
            t_vertex_arc[day][8] = 40;

            t_vertex_arc[day][9]  = x + sousEpaisseur;
            t_vertex_arc[day][10] = t_vertex_arc[day][7];
            t_vertex_arc[day][11] = 40;

            t_vertex_arc[day][12] = x;
            t_vertex_arc[day][13] = t_vertex_data_dim3[myData.getAdversaire(choice, day)][0][0];
            t_vertex_arc[day][14] = 0;

            t_vertex_arc[day][15] = x + sousEpaisseur;
            t_vertex_arc[day][16] = t_vertex_arc[day][13];
            t_vertex_arc[day][17] = 0;
             */
            t_vertex_arc[day][0] = x0;
            t_vertex_arc[day][1] = 50; //t_vertex_data_dim3[choice][0][0];
            t_vertex_arc[day][2] = cst::THICKNESS;

            t_vertex_arc[day][3] = x0 + sousEpaisseur;
            t_vertex_arc[day][4] = 50;
            t_vertex_arc[day][5] = cst::THICKNESS;

            t_vertex_arc[day][6] = x0;
            t_vertex_arc[day][7] = 150;
            t_vertex_arc[day][8] = cst::THICKNESS + 40;

            t_vertex_arc[day][9]  = x0 + sousEpaisseur;
            t_vertex_arc[day][10] = 150;
            t_vertex_arc[day][11] = cst::THICKNESS + 40;

            t_vertex_arc[day][12] = x0;
            t_vertex_arc[day][13] = 250;
            t_vertex_arc[day][14] = cst::THICKNESS;

            t_vertex_arc[day][15] = x0 + sousEpaisseur;
            t_vertex_arc[day][16] = 250;
            t_vertex_arc[day][17] = cst::THICKNESS;
        }
    }

    for(int day = 0; day < cst::NB_DAYS; day++){

        glGenBuffers(1, &arc_vertexbuffer[0]);
        glBindBuffer(GL_ARRAY_BUFFER, arc_vertexbuffer[0]);
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(t_vertex_arc[day]),
                t_vertex_arc[day],
                GL_STATIC_DRAW
        );

    }

}

void loadVBO( GLuint cylindre_vertexbuffer[cst::DIV_CYLINDER][cst::DIV_CYLINDER], GLfloat t_vertex_data_dim3[cst::NB_TEAMS][cst::DIV_CYLINDER][cst::NB_POINTS * 3], LoadData myData)
{
    myData.initVertexDataD1();

    float delta_ep = cst::THICKNESS / cst::DIV_CYLINDER;
    int milieu = cst::DIV_CYLINDER / 2;

    //glm::vec3 normals[NB_TEAMS][NB_DAYS * 2][cst::DIV_CYLINDER];
    /*
    // comme les pts A et B dans le sujet
    glm::vec3 centre[NB_TEAMS][NB_DAYS + 1];
    glm::vec3 centreDecale[NB_TEAMS][2 * NB_DAYS + 1];

    for(int team = 0; team < NB_TEAMS; team++)
    {
        for(int day = 0; day < NB_DAYS; day++)
        {
            centre[team][day].x = 50 + (float)day * dx * 2;   // * 2 car on passe de A à C à E à G à etc.
            centre[team][day].y = yEscBis[team][day] + (THICKNESS / 2);
            centre[team][day].z = 0;
        }
        centre[team][NB_DAYS] = centre[team][NB_DAYS - 1];


        for(int day = 0; day < NB_DAYS * 2; day++)
        {
            if(day % 2 == 0)
            {
                centreDecale[team][day].x = centre[team][day / 2].x ;
                centreDecale[team][day].y = centre[team][day / 2].y ;
                centreDecale[team][day].z = centre[team][day / 2].z ;
            } else {
                centreDecale[team][day].x = ( centre[team][day / 2].x + centre[team][(day / 2) + 1].x ) / 2;
                centreDecale[team][day].y = ( centre[team][day / 2].y + centre[team][(day / 2) + 1].y ) / 2;
                centreDecale[team][day].z = ( centre[team][day / 2].z + centre[team][(day / 2) + 1].z ) / 2;
            }
        }
        centreDecale[team][NB_DAYS * 2] = centre[team][NB_DAYS];
    }
    */

    for(int team = 0; team < cst::NB_TEAMS; team++)
    {
        for(int i = 0; i < cst::NB_POINTS * 3; i += 3)
        {
            if(i % 2 == 0 ){
                for(int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++){
                    if(sous_tableau==milieu){
                        continue;
                    }
                    t_vertex_data_dim3[team][sous_tableau][i]     = myData.getVertexDataValue(team, i);                                 // .x
                    t_vertex_data_dim3[team][sous_tableau][i + 1] = myData.getVertexDataValue(team, i + 1) - (sous_tableau * delta_ep);  // .y
                    t_vertex_data_dim3[team][sous_tableau][i + 2] = myData.getVertexDataValue(team, i + 2) + (sous_tableau * cst::THICKNESS / (cst::DIV_CYLINDER-1)) ;              // .z
                }
                t_vertex_data_dim3[team][milieu][i]     = myData.getVertexDataValue(team, i);                                         // .x
                t_vertex_data_dim3[team][milieu][i + 1] = myData.getVertexDataValue(team, i + 1) - delta_ep;  // .y
                t_vertex_data_dim3[team][milieu][i + 2] = myData.getVertexDataValue(team, i + 2) + cst::THICKNESS; // .z
            } else {
                for(int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++){
                    if(sous_tableau==milieu){
                        continue;
                    }
                    t_vertex_data_dim3[team][sous_tableau][i]     = myData.getVertexDataValue(team, i);                                                                    // .x
                    t_vertex_data_dim3[team][sous_tableau][i + 1] = myData.getVertexDataValue(team, i + 1) + ( (float)(cst::DIV_CYLINDER - 1 - sous_tableau) * delta_ep );   // .y
                    t_vertex_data_dim3[team][sous_tableau][i + 2] = myData.getVertexDataValue(team, i + 2) + ( (float)(cst::DIV_CYLINDER - 1 - sous_tableau) * cst::THICKNESS / (cst::DIV_CYLINDER-1) );
                }
                t_vertex_data_dim3[team][milieu][i]     = myData.getVertexDataValue(team, i);                                         // .x
                t_vertex_data_dim3[team][milieu][i + 1] = myData.getVertexDataValue(team, i + 1) + delta_ep;  // .y
                t_vertex_data_dim3[team][milieu][i + 2] = myData.getVertexDataValue(team, i + 2) + cst::THICKNESS; // .z
            }
        }
        /*
        for(int day = 0; day < NB_DAYS * 2; day++)
        {
            for(int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++)
            {
                normals[team][day][sous_tableau].x = t_vertex_data_dim3[team][sous_tableau][day]     - centreDecale[team][day].x;
                normals[team][day][sous_tableau].y = t_vertex_data_dim3[team][sous_tableau][day + 1] - centreDecale[team][day].y;
                normals[team][day][sous_tableau].z = t_vertex_data_dim3[team][sous_tableau][day + 2] - centreDecale[team][day].z;
            }
        }
         */
    }


    /*
    int more = 37 * (cst::DIV_CYLINDER + 1);
    GLfloat t_vertex_data_superpose[20][cst::DIV_CYLINDER][4 * (38 + 1) * 3 + more];  // * 3 car {x,y,z} pour chaque point

    for(int team = 0; team < 20; team++)
    {
        int iFaux = 0;
        for (int i = 0; i < NB_POINTS * 3 + more; i += 3)
        {
            if( (iFaux + 1) % 4 == 0)  // point := bas droite
            {
                for (int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++)
                {
                    float dx = (t_vertex_data_dim3[team][sous_tableau][iFaux + 3]     - t_vertex_data_dim3[team][sous_tableau][iFaux]    ) / 2;
                    float dy = (t_vertex_data_dim3[team][sous_tableau][iFaux + 3 + 1] - t_vertex_data_dim3[team][sous_tableau][iFaux + 1]) / 2;
                    float dz = (t_vertex_data_dim3[team][sous_tableau][iFaux + 3 + 2] - t_vertex_data_dim3[team][sous_tableau][iFaux + 2]) / 2;

                    t_vertex_data_superpose[team][sous_tableau][i]     = t_vertex_data_dim3[team][sous_tableau][iFaux]     + dx;
                    t_vertex_data_superpose[team][sous_tableau][i + 1] = t_vertex_data_dim3[team][sous_tableau][iFaux + 1] + dy;
                    t_vertex_data_superpose[team][sous_tableau][i + 2] = t_vertex_data_dim3[team][sous_tableau][iFaux + 2] + dz;
                }
            }
            else
            {
                for (int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++)
                {
                    t_vertex_data_superpose[team][sous_tableau][i]     = t_vertex_data_dim3[team][sous_tableau][iFaux]    ;
                    t_vertex_data_superpose[team][sous_tableau][i + 1] = t_vertex_data_dim3[team][sous_tableau][iFaux + 1];
                    t_vertex_data_superpose[team][sous_tableau][i + 2] = t_vertex_data_dim3[team][sous_tableau][iFaux + 2];
                }
                iFaux += 1 ;
            }
        }
    }
     */

    for(int team = 0; team < cst::NB_TEAMS; team++){
        for(int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++){
            glGenBuffers(1, &cylindre_vertexbuffer[team][sous_tableau]);
            glBindBuffer(GL_ARRAY_BUFFER, cylindre_vertexbuffer[team][sous_tableau]);
            glBufferData(
                    GL_ARRAY_BUFFER,
                    sizeof(t_vertex_data_dim3[team][sous_tableau]),
                    t_vertex_data_dim3[team][sous_tableau],
                    GL_STATIC_DRAW
                    );
        }
    }
}

void draw(GLuint programID, GLuint cylindre_vertexbuffer[cst::NB_TEAMS][cst::DIV_CYLINDER], glm::vec4 colors[])
{
    // Draw
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

        for(int j = 0; j < cst::DIV_CYLINDER; j++)
        {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, cylindre_vertexbuffer[team][j]);
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

int main()
{
    Render window(cst::SCREEN_WIDTH, cst::SCREEN_HEIGHT);

    // VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    GLuint programID = LoadShaders("../src/Shaders/SimpleVertexShader.glsl", "../src/Shaders/SimpleFragmentShader.glsl");


    /// initialisation des matrices du modèle MVP (ModelViewProjection)
    GLint matrixID = glGetUniformLocation(programID, "u_MVP");

    LoadData myData("../resources/data/rankspts.csv");

    // Tab for VBO
    GLfloat t_vertex_data_dim3[cst::NB_TEAMS][cst::DIV_CYLINDER][cst::NB_POINTS * 3];  // * 3 car {x,y,z} pour chaque point
    // VBO
    GLuint cylindre_vertexbuffer[cst::NB_TEAMS][cst::DIV_CYLINDER];
    GLuint arc_vertexbuffer[cst::NB_DAYS];
    // Load
    loadVBO(cylindre_vertexbuffer, t_vertex_data_dim3, myData);
    loadVBO_arc(arc_vertexbuffer, t_vertex_data_dim3, myData, 0);


    glm::vec4 colors[] = {
            /*
            glm::vec4(92.f/255.f,133.f/255.f,209.f/255.f,1.f),            // top1
            glm::vec4(142.f/255.f,217.f/255.f,228.f/255.f,1.f),    // top
            glm::vec4 (234.f/255.f,235.f/255.f,89.f/255.f,1.f),   // top_mid
            glm::vec4 (213.f/255.f,213.f/255.f,213.f/255.f,1.f),  // mid
            glm::vec4 (168.f/255.f,168.f/255.f,168.f/255.f,1.f),  // bot_mid
            glm::vec4 (233.f/255.f,139.f/255.f,139.f/255.f,1.f)     // bot
            */
            glm::vec4(0.f,72.f/255.f,204.f/255.f,1.f),            // top1
            glm::vec4(98.f/255.f,214.f/255.f,230.f/255.f,1.f),    // top
            glm::vec4 (236.f/255.f,238.f/255.f,26.f/255.f,1.f),   // top_mid
            glm::vec4 (194.f/255.f,194.f/255.f,194.f/255.f,1.f),  // mid
            glm::vec4 (140.f/255.f,140.f/255.f,140.f/255.f,1.f),  // bot_mid
            glm::vec4 (240.f/255.f,35.f/255.f,35.f/255.f,1.f)     // bot
    };

    /// Initialisation de ImGui
    c_ImGui::init(window.render);

    glm::mat4 mvp;

    do
    {
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram(programID);

        mvp = MVP::actu(window.render);

        glUniformMatrix4fv( matrixID, 1, GL_FALSE, &mvp[0][0] ); // Send new matrix

        c_ImGui::loop();

        draw(programID, cylindre_vertexbuffer, colors);

        // ARC.S
        //for(int day = 0; day < 38; day++)
        {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, arc_vertexbuffer[0]);
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
        }

        c_ImGui::maj(colors);

        window.update();
    }
    while( window.shouldNotClose() );

    // Cleanup
    c_ImGui::terminate();
    glfwTerminate( );

    return 0;
}
