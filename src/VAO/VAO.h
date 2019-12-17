//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_VAO_H
#define MAIN_VAO_H

// Include GLEW
#include <GL/glew.h>

class VAO {
private:
    GLuint VertexArrayID;
    void generation();
    void bind();

public:
    explicit VAO(GLuint vaid);
    GLuint getVArrayID();
};


#endif //MAIN_VAO_H
