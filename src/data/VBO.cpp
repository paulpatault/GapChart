//
// Created by paul patault on 17/12/2019.
//

#include "VBO.h"

#include <utility>


namespace data {

    /**
     * VBO constructor
     * @param data, instance de la classe loadData
     * @param cylinder, vector de la liste des coordonnées des points d'un cylindre
     * @param normals, vector de la liste des normals des triangle qui constituent un cylindre
     */
    VBO::VBO(LoadData* data, const std::vector<float>& cylinder, const std::vector<float>& normals, const std::vector<std::vector<float>>& combined_arcs)
    {
        m_data = data;
        load_VBO(cylinder, normals);

        if(!combined_arcs.empty())
            loadVBO_arc(combined_arcs);
    }

    /**
     * default destructor, non implementé
     */
    VBO::~VBO() = default;

    /**
     * chargement des données dans les VBO
     * @param cylinder, vector de la liste des coordonnées des points d'un cylindre
     * @param normals, vector de la liste des normals des triangle qui constituent un cylindre
     */
    void VBO::load_VBO(const std::vector<float>& cylinder, const std::vector<float>& normals)
    {
        /*t_combined_data = std::vector<GLuint>(cylinder.size() * 3);

        glGenBuffers(1, &t_combined_data[0]);

        glBindBuffer(GL_ARRAY_BUFFER, t_combined_data[0]);
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
        t_combined_data = std::vector<GLuint>(cylinder.size() * 3 + normals.size() * 3);

        glGenBuffers(1, &t_combined_data[0]);

        glBindBuffer(GL_ARRAY_BUFFER, t_combined_data[0]);

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

    void VBO::loadVBO_arc(const std::vector<std::vector<float>>& combined_arcs)
    {
        for(int day = 0; day < cst::NB_DAYS; day++){

            glGenBuffers(1, &arc_vertexbuffer[0]);
            glBindBuffer(GL_ARRAY_BUFFER, arc_vertexbuffer[0]);
            glBufferData(
                    GL_ARRAY_BUFFER,
                    sizeof(float) * combined_arcs[day].size(),
                    &combined_arcs[day],
                    GL_STATIC_DRAW
            );

        }

    }

}