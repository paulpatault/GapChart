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
        //std::vector<std::vector<GLuint>> cylindre_vertexbuffer;
        LoadData *m_data;
    public:
        VBO(LoadData* data);
        VBO(LoadData *data, std::vector<glm::vec3> vec);

        GLuint cylindre_vertexbuffer[cst::NB_TEAMS][cst::DIV_CYLINDER];
        GLuint arc_vertexbuffer[cst::NB_DAYS];
        ~VBO();
        void loadVBO();
        void load_c_VBO(std::vector<glm::vec3> points);
        std::vector<GLuint> cylindre_vb;

        void loadVBO_arc();
    };

}



#endif //MAIN_VBO_H
