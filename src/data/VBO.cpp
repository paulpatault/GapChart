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
    VBO::VBO(const LoadData* data, const std::vector<float>& cylinder, const std::vector<float>& normals)
    {
        m_data = data;
        load_VBO(cylinder, normals);
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

        size_of_cylinder = cylinder.size() ;
        t_combined_data = std::vector<GLuint>(cylinder.size()  + normals.size() );

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


}