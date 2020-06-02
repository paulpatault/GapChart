//
// Created by paul patault on 17/12/2019.
//

#include "VBO.h"

#include <utility>


namespace data {

    /**
     * VBO constructor
     * @param data, vector de la liste des coordonnées des points d'un cylindre
     * @param normals, vector de la liste des normals des triangle qui constituent un cylindre
     */
    VBO::VBO(const std::vector<float>& data, const std::vector<float>& normals)
    {
        load_VBO(data, normals);
    }

    /**
     * default destructor, non implementé
     */
    VBO::~VBO() = default;

    /**
     * chargement des données dans les VBO
     * @param data, vector de la liste des coordonnées des points d'un cylindre
     * @param normals, vector de la liste des normals des triangle qui constituent un cylindre
     */
    void VBO::load_VBO(const std::vector<float>& data, const std::vector<float>& normals)
    {
        index_end_raw_data = data.size() ;
        combined_data = std::vector<GLuint>(data.size() + normals.size() );

        glGenBuffers(1, &combined_data[0]);

        glBindBuffer(GL_ARRAY_BUFFER, combined_data[0]);

        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(float) * (data.size() + normals.size()),
                nullptr,
                GL_STATIC_DRAW
        );

        glBufferSubData(
                GL_ARRAY_BUFFER,
                0,
                sizeof(float) * data.size(),
                &data[0]
        );

        glBufferSubData(
                GL_ARRAY_BUFFER,
                sizeof(float) * data.size(),
                sizeof(float) * normals.size(),
                &normals[0]
        );
    }


}