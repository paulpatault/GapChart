//
// Created by paul patault on 29/12/2019.
//

#ifndef MAIN_TEXTURE_H
#define MAIN_TEXTURE_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "LoadData.h"
#include "includes/constants.h"

namespace data {

    static const float vertices[] = {
            // positions          // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
    };

    static const unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    class Texture {
    private:
        GLuint ID, VBO, VAO, EBO;

        GLuint LoadTexture(const char* fileName);

    public:
        Texture(const char* filePath);

        static GLuint getID(Texture *t);

        ~Texture();

        glm::mat4 modelMatrix;

        static void draw(Texture *t, int team);

        static void update(Texture *t, LoadData* data, Selection* selector);
    };

}



#endif //MAIN_TEXTURE_H
