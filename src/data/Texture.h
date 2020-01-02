//
// Created by paul patault on 29/12/2019.
//

#ifndef MAIN_TEXTURE_H
#define MAIN_TEXTURE_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <GL/glew.h>



namespace data {

    class Texture {

    private:
        GLuint ID;
        std::string filePath;
    public:
        Texture(GLuint ID, const std::string& filePath);
        ~Texture();
        static void push(Texture* t);
        static void bind(Texture* t);


    };

}



#endif //MAIN_TEXTURE_H
