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
    auto* pWindow = new screen::Render("Projet IGSD", glm::vec4(1.f));

    /// ImGui context
    screen::c_ImGui::init(screen::Render::getScreen(pWindow));

    /// Vertex Array
    auto* pVAO = new data::VAO( GLuint() );

    /// Shaders
    /// curves shader
    auto* pProgramShader = new data::Shader(
            "../resources/shaders/SimpleVertexShader.glsl",
            "../resources/shaders/SimpleFragmentShader.glsl"
            );
    /// Loading uniform location into a map so that the graphics card does not have to be asked again each time.
    data::Shader::loadUniform(pProgramShader,
            {"u_Model", "u_Rotate", "u_View", "u_Projection", "u_CameraPos" , "u_lightPos", "u_lightColor"}
            );

    /// lamp shader
    auto* pLampShader = new data::Shader(
            "../resources/shaders/lamp_vs.glsl",
            "../resources/shaders/lamp_fs.glsl"
            );
    data::Shader::loadUniform(pLampShader,
            {"projection", "view", "model", "u_color"}
            );

    /// texture shader
    auto* pTitleShader = new data::Shader(
            "../resources/shaders/title_vs.glsl",
            "../resources/shaders/title_fs.glsl"
            );
    data::Shader::loadUniform(pTitleShader,
            std::vector<std::string>{"u_Model"}
            );

    /// Lamp for lighting
    screen::Lamp lamp(
            glm::vec3(glm::vec3(1000.f, 100.f, 2000.f)),
            glm::vec3(glm::vec3(1.f)),
            glm::vec3(glm::vec3(0.99f, 0.76f, 0.18f))
            //glm::vec3(glm::vec3(0.9f, 0.5f, 0.f))
            );
    auto* pLamp = &lamp;

    /// Camera
    auto* pCamera = new screen::Camera(pWindow->screen, glm::vec3(0.0f, 0.0f, 1000.0f));

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

    glfwSetCursorPos(pWindow->screen, cst::FSCREEN_WIDTH / 2, cst::FSCREEN_HEIGHT / 2);

    /// Main loop
    do
    {
        screen::Display::clear();

        screen::c_ImGui::loop();

        GLFWwindow* window = screen::Render::getScreen(pWindow);

        ///--------- Matrix M(R)VP ---------///
        var::modelMatrix = screen::MVP::getModelMatrix(pMVP);
        var::rotationMatrix = screen::MVP::getRotationMatrix(pMVP);
        var::viewMatrix = screen::Camera::getViewMatrix(pCamera);
        var::projectionMatrix = screen::MVP::getProjectionMatrix(pMVP);

        ///--------- curves ---------///
        data::Shader::use(pProgramShader);
        data::Shader::setMat4(pProgramShader, "u_Model", var::modelMatrix);
        data::Shader::setMat4(pProgramShader, "u_Rotate", var::rotationMatrix);
        data::Shader::setMat4(pProgramShader, "u_View", var::viewMatrix);
        data::Shader::setMat4(pProgramShader, "u_Projection", var::projectionMatrix);
        data::Shader::setVec3(pProgramShader, "u_CameraPos", pCamera->getPosition());
        data::Shader::setVec3(pProgramShader, "u_lightPos", pLamp->getPosition());
        data::Shader::setVec3(pProgramShader, "u_lightColor", pLamp->getLightColor());
        screen::Display::draw(data::Shader::getID(pProgramShader), var::t_VBO, var::colors, var::selector);
        data::Shader::unbind();

        ///--------- textures ---------///
        data::Texture::update(pTexture, pData, &var::selector); // on doit update la texture avant l'affichage car sinon sur 1 image on aura la mauvaise texture
        data::Shader::use(pTitleShader);
        data::Shader::setMat4(pTitleShader, "u_Model", pTexture->getModelMatrix());
        data::Texture::draw(pTexture, var::selector.selected);
        data::Shader::unbind();

        ///--------- lamp ---------///
        data::Shader::use(pLampShader);
        data::Shader::setMat4(pLampShader, "projection", var::projectionMatrix);
        data::Shader::setMat4(pLampShader, "view", var::viewMatrix);
        data::Shader::setMat4(pLampShader, "model", pLamp->getModelMatrix());
        data::Shader::setVec3(pLampShader, "u_color", pLamp->getColor());
        screen::Lamp::draw(pLamp);
        data::Shader::unbind();

        ///--------- keyboard callback ---------///
        screen::Camera::processInput(pCamera, window, var::deltaTime);
        screen::Display::selectionCallBack(window, var::selector);

        ///--------- updates ---------///
        screen::MVP::maj(pMVP, window);
        screen::c_ImGui::maj(var::colors);
        utils::majVBOs(var::t_VBO, var::selector, pData);
        utils::updateTime(var::deltaTime, var::lastFrame);

        screen::Display::update(pWindow);

    } while( pWindow->shouldNotClose() );

    screen::c_ImGui::terminate();
    data::VAO::destroy(pVAO);
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
