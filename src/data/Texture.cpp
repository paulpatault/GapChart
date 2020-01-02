//
// Created by paul patault on 29/12/2019.
//

#include "Texture.h"

#include <utility>


namespace data {

    Texture::Texture(GLuint ID, const std::string& filePath)
    {
        this->ID = ID;
        this->filePath = filePath;
        glGenTextures(1, &this->ID);
    }

    void Texture::push(data::Texture *t)
    {
        bind(t);

        cv::Mat image = cv::imread(t->filePath, CV_LOAD_IMAGE_UNCHANGED);
        cv::flip(image, image, 0);

        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                image.cols,
                image.rows,
                0,
                GL_BGRA,
                GL_UNSIGNED_BYTE,
                image.ptr()
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    void data::Texture::bind(data::Texture *t)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, t->ID);
    }

    Texture::~Texture() = default;

}
