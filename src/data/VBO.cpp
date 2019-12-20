//
// Created by paul patault on 17/12/2019.
//

#include "VBO.h"


namespace data {

    VBO::VBO(LoadData* data, std::vector<float> cylinder, std::vector<float> normals)
    {
        m_data = data;
        load_VBO(cylinder, normals);
        loadVBO_arc();
    }

    VBO::~VBO() = default;

    void VBO::load_VBO(std::vector<float> cylinder, std::vector<float> normals)
    {
        /*cylindre_vb = std::vector<GLuint>(cylinder.size() * 3);

        glGenBuffers(1, &cylindre_vb[0]);

        glBindBuffer(GL_ARRAY_BUFFER, cylindre_vb[0]);
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(float) * cylinder.size(),
                &cylinder[0],
                GL_STATIC_DRAW
        );

        normals_vb = std::vector<GLuint>(normals.size() * 3);

        glGenBuffers(1, &normals_vb[0]);
        glBindBuffer(GL_ARRAY_BUFFER, normals_vb[0]);
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(float) * normals.size(),
                &normals[0],
                GL_STATIC_DRAW
        );*/
        size_of_cylinder = cylinder.size() * 3;
        cylindre_vb = std::vector<GLuint>(cylinder.size() * 3 + normals.size() * 3);

        glGenBuffers(1, &cylindre_vb[0]);

        glBindBuffer(GL_ARRAY_BUFFER, cylindre_vb[0]);

        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(float) * (cylinder.size() + normals.size()),
                nullptr,
                GL_STATIC_DRAW
        );

        glBufferSubData(
                GL_ARRAY_BUFFER,
                0,
                sizeof(float) * cylinder.size(),
                &cylinder[0]
                );

        glBufferSubData(
                GL_ARRAY_BUFFER,
                sizeof(float) * cylinder.size(),
                sizeof(float) * normals.size(),
                &normals[0]
        );


    }


    void VBO::loadVBO_arc()
    {
        GLfloat t_vertex_data_dim3[cst::NB_TEAMS][cst::DIV_CYLINDER][cst::NB_POINTS * 3];

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


}