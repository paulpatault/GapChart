//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_SHADERS_H
#define MAIN_SHADERS_H

// Include standard includes
#include <stdio.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

#include <GL/glew.h>


namespace data {

    class Shaders {
    public:
        static GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
        static void bind(GLuint programID);
    };


}

#endif //MAIN_SHADERS_H
