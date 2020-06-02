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

        void __generation();

        void __bind();

    public:
        explicit VAO(GLuint vaid);

        GLuint getVArrayID() const;

        static void destroy(VAO* vao);

    };

}


#endif //MAIN_VAO_H
