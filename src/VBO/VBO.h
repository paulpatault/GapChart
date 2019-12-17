//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_VBO_H
#define MAIN_VBO_H

#include <vector>
#include <GL/glew.h>
#include "includes/constants.h"
#include "src/LoadData/LoadData.h"

class VBO {
private:
    //std::vector<std::vector<GLuint>> cylindre_vertexbuffer;

    LoadData *m_data;
public:
    GLuint cylindre_vertexbuffer[cst::NB_TEAMS][cst::DIV_CYLINDER];
    GLuint arc_vertexbuffer[cst::NB_DAYS];
    VBO(LoadData* data);
    ~VBO();
    void loadVBO();
    void loadVBO_arc();
};


#endif //MAIN_VBO_H
