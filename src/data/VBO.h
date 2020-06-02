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
    public:
        std::vector<GLuint> combined_data;

        int index_end_raw_data;

        VBO(const std::vector<float>& cylinder, const std::vector<float>& normals);

        ~VBO();

        void load_VBO(const std::vector<float>& data, const std::vector<float>& vec3_normals);

    };

}



#endif //MAIN_VBO_H
