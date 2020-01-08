//
// Created by paul patault on 17/12/2019.
//

#include "Shader.h"


namespace data {

    /**
     * Compilation des shaders
     * @param vertex_file_path  chemin du vertex shader
     * @param fragment_file_path chemin du fragment shader
     * @return ProgramID
     */
    Shader::Shader(const char* vertex_file_path, const char* fragment_file_path)
    {
        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        if(VertexShaderStream.is_open())
        {
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();

        } else {
            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
            getchar();
            exit(-1);
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if(FragmentShaderStream.is_open()){
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;


        // Compile Vertex Shader
        printf("Compiling shader : %s\n", vertex_file_path);
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }


        // Compile Fragment Shader
        printf("Compiling shader : %s\n", fragment_file_path);
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }


        // Link the program
        printf("Linking program\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);
        glValidateProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }


        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        ID = ProgramID;
    }

    /**
     * Return d'ID du shader sh
     */
    GLuint Shader::getID(Shader* sh)
    {
        return sh->ID;
    }


    /**
     * Liaison des shaders avec le programID
     * @param sh le shader a lier
     */
    void Shader::use(Shader* sh)
    {
        glUseProgram(sh->ID);
    }

    /**
     * Détachement d'un shader
     */
    void Shader::unbind()
    {
        glUseProgram(0);
    }

    /**
     * Envoie un boolean au shader
     * @param name nom dans le shader
     * @param value bool a envoyer
     */
    void Shader::setBool(const std::string &name, bool value) const
    {
        glUniform1i(findUniform(name), (int)value);
    }

    /**
     * Envoie un int au shader
     * @param name nom dans le shader
     * @param value int a envoyer
     */
    void Shader::setInt(const std::string &name, int value) const
    {
        glUniform1i(findUniform(name), value);
    }

    /**
     * Envoie un float au shader
     * @param name nom dans le shader
     * @param value float a envoyer
     */
    void Shader::setFloat(const std::string &name, float value) const
    {
        glUniform1f(findUniform(name), value);
    }

    /**
     * Envoie un vec2 au shader
     * @param name nom dans le shader
     * @param value vector a envoyer
     */
    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(findUniform(name), 1, &value[0]);
    }

    /**
     * Envoie un vec2 au shader
     * @param name nom dans le shader
     * @param x 1ere coord du vec2
     * @param y 2eme coord du vec2
     */
    void Shader::setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(findUniform(name), x, y);
    }

    /**
     * Envoie un vec3 au shader
     * @param name nom dans le shader
     * @param value vector a envoyer
     */
    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(findUniform(name), 1, &value[0]);
    }

    /**
     * Envoie un vec3 au shader
     * @param name nom dans le shader
     * @param x 1ere coord du vec3
     * @param y 2eme coord du vec3
     * @param z 3eme coord du vec3
     */
    void Shader::setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(findUniform(name), x, y, z);
    }

    /**
     * Envoie un vec4 au shader
     * @param name nom dans le shader
     * @param value vector a envoyer
     */
    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(findUniform(name), 1, &value[0]);
    }

    /**
     * Envoie un vec4 au shader
     * @param name nom dans le shader
     * @param x 1ere coord du vec4
     * @param y 2eme coord du vec4
     * @param z 3eme coord du vec4
     * @param w 4eme coord du vec4
     */
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(findUniform(name), x, y, z, w);
    }

    /**
     * Envoie une mat2 au shader
     * @param name nom dans le shader
     * @param mat matrice a envoyer
     */
    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(findUniform(name), 1, GL_FALSE, &mat[0][0]);
    }

    /**
     * Envoie une mat3 au shader
     * @param name nom dans le shader
     * @param mat matrice a envoyer
     */
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(findUniform(name), 1, GL_FALSE, &mat[0][0]);
    }

    /**
     * Envoie une mat4 au shader
     * @param name nom dans le shader
     * @param mat matrice a envoyer
     */
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(findUniform(name), 1, GL_FALSE, &mat[0][0]);
    }

    /**
     * Idem que setVec3 sauf que la methode est static
     */
    void Shader::setVec3(const Shader *shader, std::string name, const glm::vec3 &value)
    {
        shader->setVec3(name, value);
    }

    /**
     * Idem que setMat4 sauf que la methode est static
     */
    void Shader::setMat4(const Shader *shader, std::string name, const glm::mat4 &mat)
    {
        shader->setMat4(name, mat);
    }

    void Shader::destroy(const Shader* shader)
    {
        delete shader;
    }

    /**
     * Loading uniform location into a map so that the graphics card does not have to be asked again each time.
     */
    void Shader::loadUniform(Shader* shader, const std::string& name)
    {
        GLint location = glGetUniformLocation(shader->ID, name.c_str());
        shader->uniforms.insert({name, location});
    }

    /**
     * trouve le GLint location associé a name dans la map
     */
    GLint Shader::findUniform(std::string name) const
    {
        return uniforms.at(name);
    }

    /**
     * Call names.size() Shader::loadUniform
     * @param shader associé
     * @param names a charger
     */
    void Shader::loadUniform(Shader *shader, const std::vector<std::string>& names)
    {
        for(const std::string& s: names)
        {
            shader->loadUniform(shader, s);
        }
    }


}