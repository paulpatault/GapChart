//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_VAO_H
#define MAIN_VAO_H

#include <GL/glew.h>


namespace data {

    class VAO {
    private:
        GLuint VertexArrayID;
        void generation();
        void bind();

    public:
        explicit VAO(GLuint vaid);
        GLuint getVArrayID();
    };

}


#endif //MAIN_VAO_H
