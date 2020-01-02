//
// Created by paul patault on 17/12/2019.
//

#include "VAO.h"

namespace data {

    /**
     * Constructor de la VOA
     * @param vaid := Vertex Array ID
     */
    VAO::VAO(GLuint vaid)
    {
        VertexArrayID = vaid;
        generation();
        bind();
    }

    /**
     * generation of 1 vertex array by gl function
     */
    void VAO::generation()
    {
        glGenVertexArrays(1, &VertexArrayID);
    }

    /**
     * binding a vertex array by gl function
     */
    void VAO::bind()
    {
        glBindVertexArray(VertexArrayID);
    }

    /**
     * getter basic
     * @return vao_id
     */
    GLuint VAO::getVArrayID() const
    {
        return VertexArrayID;
    }

    /**
     * destruction d'un vertex array
     * @param vao
     */
    void VAO::destroy(VAO* vao)
    {
        glDeleteVertexArrays(1, &vao->VertexArrayID);
    }

}

