//
// Created by paul patault on 17/12/2019.
//

#include "VAO.h"


VAO::VAO(GLuint vaid) {
    VertexArrayID = vaid;
    generation();
    bind();
}

void VAO::generation()
{
    glGenVertexArrays(1, &VertexArrayID);
}

void VAO::bind()
{
    glBindVertexArray(VertexArrayID);
}

GLuint VAO::getVArrayID()
{
    return VertexArrayID;
}

