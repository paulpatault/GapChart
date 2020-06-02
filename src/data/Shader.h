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
#include <map>


namespace data {

    class Shader {
    private:
        GLuint ID;

        std::map<std::string, GLint> uniforms;

        static void loadUniform(Shader* shader, const std::string& name);

        GLint findUniform(std::string name) const;

    public:
        Shader(const char* vertex_file_path, const char* fragment_file_path);

        static void loadUniform(Shader* shader, const std::vector<std::string>& names);

        static void use(Shader*);

        static void unbind();

        static GLuint getID(Shader*);

        void setBool(const std::string &name, bool value) const;
        static void setBool(const Shader* shader, const std::string &name, bool value);

        void setInt(const std::string &name, int value) const;
        static void setInt(const Shader* shader, const std::string &name, int value);

        void setFloat(const std::string &name, float value) const;
        static void setFloat(const Shader* shader, const std::string &name, float value);

        void setVec2(const std::string &name, const glm::vec2 &value) const;
        static void setVec2(const Shader* shader, const std::string &name, const glm::vec2 &value);

        void setVec3(const std::string &name, const glm::vec3 &value) const;
        static void setVec3(const Shader* shader, const std::string& name, const glm::vec3 &value);

        void setVec4(const std::string &name, const glm::vec4 &value) const;
        static void setVec4(const Shader* shader, const std::string& name, const glm::vec4 &value);

        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        static void setMat2(const Shader* shader, const std::string& name, const glm::mat2 &mat);

        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        static void setMat3(const Shader* shader, const std::string& name, const glm::mat3 &mat);

        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        static void setMat4(const Shader* shader, const std::string& name, const glm::mat4 &mat);

        static void destroy(const Shader* shader);
    };


}

#endif //MAIN_SHADER_H
