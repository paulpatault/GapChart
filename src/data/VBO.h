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
        VBO(LoadData *data, std::vector<float> cylinder, std::vector<float> normals);

        GLuint cylindre_vertexbuffer[cst::NB_TEAMS][cst::DIV_CYLINDER];
        GLuint arc_vertexbuffer[cst::NB_DAYS];
        ~VBO();
        void load_VBO(std::vector<float> vec3_cylinder, std::vector<float> vec3_normals);
        std::vector<GLuint> cylindre_vb;
        std::vector<GLuint> normals_vb;

        void loadVBO_arc();

        int size_of_cylinder;
    };

}



#endif //MAIN_VBO_H
