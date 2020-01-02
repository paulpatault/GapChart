//
// Created by paul patault on 02/01/2020.
//

#include "Lamp.h"


namespace screen {

    Lamp::Lamp(glm::vec3 pos, bool t_toDisplay)
    {
        position = pos;
        toDisplay = t_toDisplay;
        VAO_ID = (GLuint());
        VBO_ID = (GLuint());
        model = (glm::mat4());
        vertices = {
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,

                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,

                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,

                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
        };

    }

    glm::vec3 Lamp::getPosition() const
    {
        return position;
    }

    bool Lamp::isDisplayable() const
    {
        return toDisplay;
    }

    GLuint Lamp::getVAO_ID() const
    {
        return VAO_ID;
    }

    glm::mat4 Lamp::getModelMatrix() const
    {
        return model;
    }

    void Lamp::update(Lamp* lamp)
    {
        glm::vec3 translation = glm::vec3(- cst::FSCREEN_WIDTH/2, - cst::FSCREEN_HEIGHT/2,0.f);

        lamp->model = glm::translate(glm::mat4(1.0f), translation);
        lamp->model = glm::translate(lamp->model, lamp->position);

        lamp->model = glm::scale(lamp->model, glm::vec3(100));

    }

    void Lamp::draw(Lamp *lamp)
    {
        if(lamp->isDisplayable())
        {
            glGenBuffers(1, &lamp->VBO_ID);

            glBindBuffer(GL_ARRAY_BUFFER, lamp->VBO_ID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lamp->vertices.size(), &lamp->vertices[0], GL_STATIC_DRAW);

            glBindVertexArray(lamp->getVAO_ID());

            glBindBuffer(GL_ARRAY_BUFFER, lamp->VBO_ID);

            // position attribute
            glVertexAttribPointer(
                    0,
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    (void*) nullptr
            );
            glEnableVertexAttribArray(0);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    void Lamp::setPosition(glm::vec3 apos)
    {
        position = apos;
    }


}