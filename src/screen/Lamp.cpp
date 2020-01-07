//
// Created by paul patault on 02/01/2020.
//

#include "Lamp.h"


namespace screen {

    /**
     * Contructeur
     * @param pos initial de la lampe
     * @param in_lightColor couleur d'éclairage de la lampe
     * @param color couleur de la lampe
     * @param t_toDisplay boolean: true si on veut afficher la lampe, false sinon
     */
    Lamp::Lamp(glm::vec3 pos, glm::vec3 in_lightColor, glm::vec3 in_color, bool t_toDisplay)
    {
        position = pos;
        lightColor = in_lightColor;
        color = in_color;
        toDisplay = t_toDisplay;

        update(this);

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

        glGenBuffers(1, &VBO_ID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    }

    glm::vec3 Lamp::getPosition(const Lamp* lamp)
    {
        return lamp->position;
    }

    glm::vec3 Lamp::getLightColor(const Lamp* lamp)
    {
        return lamp->lightColor;
    }

    glm::vec3 Lamp::getColor(const Lamp* lamp)
    {
        return lamp->color;
    }

    bool Lamp::isDisplayable() const
    {
        return toDisplay;
    }

    GLuint Lamp::getVAO_ID() const
    {
        return VAO_ID;
    }

    glm::mat4 Lamp::getModelMatrix(const Lamp* lamp)
    {
        return lamp->model;
    }

    void Lamp::update(Lamp* lamp)
    {
        glm::vec3 translation = glm::vec3(- cst::FSCREEN_WIDTH/2, - cst::FSCREEN_HEIGHT/2,0.f);

        lamp->model = glm::translate(glm::mat4(1.0f), translation);
        lamp->model = glm::translate(lamp->model, lamp->position);

        lamp->model = glm::scale(lamp->model, glm::vec3(100));

    }

    void Lamp::draw(const Lamp* lamp)
    {
        if(lamp->isDisplayable())
        {
            glBindVertexArray(lamp->VAO_ID);
            glBindBuffer(GL_ARRAY_BUFFER, lamp->VBO_ID);
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

    void Lamp::destroy(Lamp* lamp)
    {
        glDeleteVertexArrays(1, &lamp->VAO_ID);
        glDeleteBuffers(1, &lamp->VBO_ID);
    }

    Lamp::~Lamp() = default;


}