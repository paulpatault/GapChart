//
// Created by paul patault on 29/12/2019.
//

#include "Texture.h"

namespace data {

    Texture::Texture(const char* filePath)
    {
        ID = LoadTexture(filePath);

        glm::vec3 translation = glm::vec3(0.f, 0.75f, 0.f);

        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, translation);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4));

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    GLuint Texture::LoadTexture(const char* fileName)
    {
        GLuint tId = -1;
        // On utilise OpenCV pour charger l'image
        cv::Mat image = cv::imread(fileName, CV_LOAD_IMAGE_UNCHANGED);
        cv::Mat imageflip;
        cv::flip(image, imageflip, 0);

        glGenTextures(1, &tId);

        glBindTexture(GL_TEXTURE_2D, tId);

        glTexImage2D(GL_TEXTURE_2D,
                     0,     // mipmap level => Attention pas de mipmap dans les textures rectangle
                     GL_RGBA,     // internal color format
                     imageflip.cols,
                     imageflip.rows,
                     0,           // border width in pixels
                     GL_BGRA,     // input file format. Arg le png code les canaux dans l'autre sens
                     GL_UNSIGNED_BYTE, // image data type
                     imageflip.ptr());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        return tId;
    }

    void Texture::draw(data::Texture *t, int team)
    {
        if(team != -1 )
        {
            glBindVertexArray(t->VAO);

            glBindBuffer(GL_ARRAY_BUFFER, t->VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // bind Texture
            glBindTexture(GL_TEXTURE_2D, t->ID);

            // render container

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glDisableVertexAttribArray(0);
        }
    }

    GLuint Texture::getID(Texture *t)
    {
        return t->ID;
    }

    void Texture::update(Texture *t, LoadData* data, Selection* selector)
    {
        if(selector->selected != -1 and selector->changed )
        {
            const char* fileName = data->getImagesPath(selector->selected);
            t->ID = t->LoadTexture(fileName);
            glDeleteVertexArrays(1, &t->VAO);
            glDeleteBuffers(1, &t->VBO);
            glDeleteBuffers(1, &t->EBO);

            glGenVertexArrays(1, &t->VAO);
            glGenBuffers(1, &t->VBO);
            glGenBuffers(1, &t->EBO);
        }
    }

    Texture::~Texture() = default;

}
