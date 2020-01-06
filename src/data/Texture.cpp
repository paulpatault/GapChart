//
// Created by paul patault on 29/12/2019.
//

#include "Texture.h"

namespace data {

    /**
     * Constructeur banal
     * @param filePath chemin de l'image
     */
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

    /**
     * Charge la texture et retourne son ID
     * @param fileName chemin de l'image
     * @return GLuint texture.ID
     */
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

    /**
     * Dessine la texture dans la fenetre
     * @param pTexture texture a dessiner
     * @param team équipe a checker
     */
    void Texture::draw(const data::Texture *pTexture, int team)
    {
        if(team != -1 )
        {
            glBindVertexArray(pTexture->VAO);

            glBindBuffer(GL_ARRAY_BUFFER, pTexture->VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pTexture->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // bind Texture
            glBindTexture(GL_TEXTURE_2D, pTexture->ID);

            // render container

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glDisableVertexAttribArray(0);
        }
    }

    /**
     * Getter simple
     * @param t la texture
     * @return un Gluint := son ID
     */
    GLuint Texture::getID(const Texture *t)
    {
        return t->ID;
    }

    /**
     * On load un autre texture dans la meme instance -> on remplace l'ancienne
     * @param texture a changer
     * @param data
     * @param selector n° de la nouvelle texture si nouvelle il y a
     */
    void Texture::update(Texture *texture, const LoadData* data, const Selection* selector)
    {
        if(selector->selected != -1 and selector->changed )
        {
            const char* fileName = data->getImagesPath(selector->selected);
            texture->ID = texture->LoadTexture(fileName);
            glDeleteVertexArrays(1, &texture->VAO);
            glDeleteBuffers(1, &texture->VBO);
            glDeleteBuffers(1, &texture->EBO);

            glGenVertexArrays(1, &texture->VAO);
            glGenBuffers(1, &texture->VBO);
            glGenBuffers(1, &texture->EBO);
        }
    }

    void Texture::destroy(const Texture *texture)
    {
        delete texture;
    }

    Texture::~Texture() = default;

}
