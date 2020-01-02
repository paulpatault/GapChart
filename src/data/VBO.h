//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_VBO_H
#define MAIN_VBO_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "includes/constants.h"
#include "LoadData.h"


namespace data {

    class VBO {
    private:
        LoadData *m_data;

    public:
        GLuint arc_vertexbuffer[cst::NB_DAYS]{};

        std::vector<GLuint> t_combined_data;

        int size_of_cylinder;

        VBO(LoadData *data, const std::vector<float>& cylinder, const std::vector<float>& normals, const std::vector<std::vector<float>>& combined_arcs);

        ~VBO();

        void load_VBO(const std::vector<float>& vec3_cylinder, const std::vector<float>& vec3_normals);

        void loadVBO_arc(const std::vector<std::vector<float>>& combined_arcs);

    };

}



#endif //MAIN_VBO_H
