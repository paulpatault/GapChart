//
// Created by paul patault on 17/12/2019.
//

#include "VBO.h"


namespace data {


    VBO::VBO(LoadData* data)
    {
        //cylindre_vertexbuffer = std::vector<std::vector<GLuint>>(cst::NB_TEAMS);
        m_data = data;
        loadVBO();
        loadVBO_arc();
    }

    VBO::VBO(LoadData* data, std::vector<glm::vec3> vec)
    {
        //cylindre_vertexbuffer = std::vector<std::vector<GLuint>>(cst::NB_TEAMS);
        m_data = data;
        load_c_VBO(vec);
        loadVBO_arc();
    }

    VBO::~VBO() = default;

    void VBO::loadVBO()
    {
        GLfloat t_vertex_data_dim3[cst::NB_TEAMS][cst::DIV_CYLINDER][cst::NB_POINTS * 3];

        m_data->initVertexDataD1();

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
                        t_vertex_data_dim3[team][sous_tableau][i]     = m_data->getVertexDataValue(team, i);                                 // .x
                        t_vertex_data_dim3[team][sous_tableau][i + 1] = m_data->getVertexDataValue(team, i + 1) - (sous_tableau * delta_ep);  // .y
                        t_vertex_data_dim3[team][sous_tableau][i + 2] = m_data->getVertexDataValue(team, i + 2) + (sous_tableau * cst::THICKNESS / (cst::DIV_CYLINDER-1)) ;              // .z
                    }
                    t_vertex_data_dim3[team][milieu][i]     = m_data->getVertexDataValue(team, i);                                         // .x
                    t_vertex_data_dim3[team][milieu][i + 1] = m_data->getVertexDataValue(team, i + 1) - delta_ep;  // .y
                    t_vertex_data_dim3[team][milieu][i + 2] = m_data->getVertexDataValue(team, i + 2) + cst::THICKNESS; // .z
                } else {
                    for(int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++){
                        if(sous_tableau==milieu){
                            continue;
                        }
                        t_vertex_data_dim3[team][sous_tableau][i]     = m_data->getVertexDataValue(team, i);                                                                    // .x
                        t_vertex_data_dim3[team][sous_tableau][i + 1] = m_data->getVertexDataValue(team, i + 1) + ( (float)(cst::DIV_CYLINDER - 1 - sous_tableau) * delta_ep );   // .y
                        t_vertex_data_dim3[team][sous_tableau][i + 2] = m_data->getVertexDataValue(team, i + 2) + ( (float)(cst::DIV_CYLINDER - 1 - sous_tableau) * cst::THICKNESS / (cst::DIV_CYLINDER-1) );
                    }
                    t_vertex_data_dim3[team][milieu][i]     = m_data->getVertexDataValue(team, i);                                         // .x
                    t_vertex_data_dim3[team][milieu][i + 1] = m_data->getVertexDataValue(team, i + 1) + delta_ep;  // .y
                    t_vertex_data_dim3[team][milieu][i + 2] = m_data->getVertexDataValue(team, i + 2) + cst::THICKNESS; // .z
                }
            }
        }



        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            for(int sous_tableau = 0; sous_tableau < cst::DIV_CYLINDER; sous_tableau++)
            {
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

    void VBO::load_c_VBO(std::vector<glm::vec3> points)
    {

        std::vector<float> conv_points;
        for(int i = 0; i < points.size(); i++)
        {
            conv_points.push_back(points[i].x);
            conv_points.push_back(points[i].y);
            conv_points.push_back(points[i].z);
        }

        GLuint res_VBO[points.size() * 3];

        cylindre_vb = std::vector<GLuint> (points.size() * 3);

        glGenBuffers(1, &cylindre_vb[0]);
        glBindBuffer(GL_ARRAY_BUFFER, cylindre_vb[0]);
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(float) * conv_points.size(),
                &conv_points[0],
                GL_STATIC_DRAW
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