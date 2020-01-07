//
// Created by paul patault on 15/12/2019.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

// namespace var
#include "includes/variables.h"
#include "includes/utils.h"

// namespace data
#include "src/data/LoadData.h"
#include "src/data/Shader.h"
#include "src/data/VAO.h"
#include "src/data/Texture.h"

// namespace screen
#include "src/screen/MVP.h"
#include "src/screen/c_ImGui.h"
#include "src/screen/Render.h"
#include "src/screen/Display.h"
#include "src/screen/Lamp.h"
#include "src/screen/Camera.h"


int main()
{
    /// Instance of the class Render that manages the window + initialise GL
    auto* window = new screen::Render("Projet IGSD", glm::vec4(1.f));

    /// ImGui context
    screen::c_ImGui::init(screen::Render::getScreen(window));

    /// Vertex Array
    auto* m_VAO = new data::VAO( ( GLuint() ) );

    /// Shaders
    /// curves shader
    auto* pProgramShader = new data::Shader(
            "../resources/shaders/SimpleVertexShader.glsl",
            "../resources/shaders/SimpleFragmentShader.glsl"
            );

    /// lamp shader
    auto* pLampShader = new data::Shader(
            "../resources/shaders/lamp_vs.glsl",
            "../resources/shaders/lamp_fs.glsl"
            );

    /// texture shader
    auto* pTitleShader = new data::Shader(
            "../resources/shaders/title_vs.glsl",
            "../resources/shaders/title_fs.glsl"
            );

    /// Lamp for lighting
    screen::Lamp lamp(
            glm::vec3(glm::vec3(1000.f, 100.f, 2000.f)),
            glm::vec3(glm::vec3(1.f)),
            glm::vec3(glm::vec3(0.9f, 0.5f, 0.f))
            );
    auto* pLamp = &lamp;

    /// Camera
    auto* pCamera = new screen::Camera(glm::vec3(0.0f, 0.0f, 1000.0f));

    /// Texture 0
    auto* pTexture = new data::Texture("../resources/images/Arsenal.png");

    /// Model View Projection Matrix
    auto* pMVP = new screen::MVP;

    /// Pointer to an instance of the class LoadData that manages the .csv
    auto* pData = new data::LoadData("../resources/data/rankspts.csv");

    /// Vector of 20 VBOs
    /// Usable VBOs in t_VBO and t_VBO_0 saving
    var::t_VBO = utils::makeVBOs(pData);
    var::t_VBO_0 = var::t_VBO;

    /// Main loop
    do
    {
        screen::Display::clear();

        screen::c_ImGui::loop();

        ///--------- curves ---------///
        data::Shader::use(pProgramShader);
        data::Shader::setMat4_stat(pProgramShader, "u_Model", screen::MVP::getModelMatrix(pMVP));
        data::Shader::setMat4_stat(pProgramShader, "u_Rotate", screen::MVP::getRotationMatrix(pMVP));
        data::Shader::setMat4_stat(pProgramShader, "u_View", screen::Camera::getViewMatrix(pCamera));
        data::Shader::setMat4_stat(pProgramShader, "u_Projection", screen::MVP::getProjectionMatrix(pMVP));
        data::Shader::setVec3_stat(pProgramShader, "u_CameraPos", screen::Camera::getPosition(pCamera));
        data::Shader::setVec3_stat(pProgramShader, "u_lightPos", screen::Lamp::getPosition(pLamp));
        data::Shader::setVec3_stat(pProgramShader, "u_lightColor", screen::Lamp::getLightColor(pLamp));
        screen::Display::draw(data::Shader::getID(pProgramShader), var::t_VBO, var::colors, var::selector);

        ///--------- textures ---------///
        data::Texture::update(pTexture, pData, &var::selector);
        data::Shader::use(pTitleShader);
        data::Shader::setMat4_stat(pTitleShader, "u_Model", data::Texture::getModelMatrix(pTexture));
        data::Texture::draw(pTexture, var::selector.selected);

        ///--------- lamp ---------///
        data::Shader::use(pLampShader);
        data::Shader::setMat4_stat(pLampShader, "projection", screen::MVP::getProjectionMatrix(pMVP));
        data::Shader::setMat4_stat(pLampShader, "view", screen::Camera::getViewMatrix(pCamera));
        data::Shader::setMat4_stat(pLampShader, "model", screen::Lamp::getModelMatrix(pLamp));
        data::Shader::setVec3_stat(pLampShader, "u_color", screen::Lamp::getColor(pLamp));
        screen::Lamp::draw(pLamp);

        ///--------- keyboard callback ---------///
        screen::Camera::processInput(pCamera, screen::Render::getScreen(window), var::deltaTime);
        screen::Display::selectionCallBack(screen::Render::getScreen(window), var::selector);

        ///--------- updates ---------///
        screen::MVP::maj(pMVP, screen::Render::getScreen(window));
        screen::c_ImGui::maj(var::colors);
        utils::majVBOs(var::t_VBO, var::selector, pData);
        utils::updateTime(var::deltaTime, var::lastFrame);

        screen::Display::update(window);

    } while( window->shouldNotClose() );

    screen::c_ImGui::terminate();

    data::VAO::destroy(m_VAO);
    data::Shader::destroy(pProgramShader);
    data::Shader::destroy(pTitleShader);
    data::Shader::destroy(pLampShader);
    screen::Lamp::destroy(pLamp);
    screen::Camera::destroy(pCamera);
    data::Texture::destroy(pTexture);
    screen::MVP::destroy(pMVP);
    data::LoadData::destroy(pData);

    glfwTerminate();

    return 0;
}
