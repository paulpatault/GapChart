//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_SHADER_H
#define MAIN_SHADER_H

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
#include <glm/glm.hpp>


namespace data {

    class Shader {
    private:
        GLuint ID;

    public:
        Shader(const char* vertex_file_path, const char* fragment_file_path);

        static void use(Shader*);

        static GLuint getID(Shader*);

        void setBool(const std::string &name, bool value) const;

        void setInt(const std::string &name, int value) const;

        void setFloat(const std::string &name, float value) const;

        void setVec2(const std::string &name, const glm::vec2 &value) const;

        void setVec2(const std::string &name, float x, float y) const;

        void setVec3(const std::string &name, const glm::vec3 &value) const;

        static void setVec3_stat(const Shader* shader, const std::string &name, const glm::vec3 &value);

        void setVec3(const std::string &name, float x, float y, float z) const;

        void setVec4(const std::string &name, const glm::vec4 &value) const;

        void setVec4(const std::string &name, float x, float y, float z, float w);

        void setMat2(const std::string &name, const glm::mat2 &mat) const;

        void setMat3(const std::string &name, const glm::mat3 &mat) const;

        void setMat4(const std::string &name, const glm::mat4 &mat) const;

        static void setMat4_stat(const Shader* shader, const std::string &name, const glm::mat4 &mat);

        static void destroy(const Shader* shader);
    };


}

#endif //MAIN_SHADER_H
