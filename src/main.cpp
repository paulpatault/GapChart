#include "includes/main_includes.h"

int main()
{
    /// Instance of the class Render that manages the window + initialise GL
    screen::Render window("Projet IGSD", vec4(1.f));

    /// ImGui context
    screen::c_ImGui::init(window.screen);

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
    screen::Lamp lamp(glm::vec3(1000.f, 100.f, 2000.f));

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
        utils::updateTime(var::deltaTime, var::lastFrame);

        screen::Display::clear();

        screen::c_ImGui::loop();

        ///--------- curves ---------///
        data::Shader::use(pProgramShader);
        data::Shader::setMat4_stat(pProgramShader, "u_Model", *pMVP->getModelMatrix());
        data::Shader::setMat4_stat(pProgramShader, "u_Rotate", *pMVP->getRotationMatrix());
        data::Shader::setMat4_stat(pProgramShader, "u_View", pCamera->getViewMatrix());
        data::Shader::setMat4_stat(pProgramShader, "u_Projection", *pMVP->getProjectionMatrix());
        data::Shader::setVec3_stat(pProgramShader, "u_CameraPos", *pCamera->getPosition());
        data::Shader::setVec3_stat(pProgramShader, "u_lightPos", lamp.getPosition());
        screen::Display::draw(pProgramShader->ID, var::t_VBO, var::colors, var::selector);

        ///--------- textures ---------///
        data::Texture::update(pTexture, pData, &var::selector);
        data::Shader::use(pTitleShader);

        data::Shader::setMat4_stat(pTitleShader, "u_Model", pTexture->modelMatrix);
        data::Texture::draw(pTexture, var::selector.selected);

        ///--------- lamp ---------///
        data::Shader::use(pLampShader);
        data::Shader::setMat4_stat(pLampShader, "projection", *pMVP->getProjectionMatrix());
        data::Shader::setMat4_stat(pLampShader, "view", pCamera->getViewMatrix());
        data::Shader::setMat4_stat(pLampShader, "model", lamp.getModelMatrix());
        screen::Lamp::draw_stat(&lamp);

        ///--------- keyboard callback ---------///
        screen::Camera::processInput(pCamera, window.screen, 10 * var::deltaTime);
        screen::MVP::maj_stat(pMVP, window.screen);
        screen::Display::selectionCallBack(window.screen, var::selector);
        utils::majVBOs(var::t_VBO, var::selector, pData);
        screen::Lamp::update(&lamp);

        glm::vec3 lp = lamp.getPosition();
        screen::c_ImGui::maj(var::colors, lp);
        lamp.setPosition(lp);

        screen::Display::update(window);

    } while( window.shouldNotClose() );

    screen::c_ImGui::terminate();

    data::VAO::destroy(m_VAO);
    data::Shader::destroy(pProgramShader);
    data::Shader::destroy(pTitleShader);
    data::Shader::destroy(pLampShader);
    screen::Lamp::destroy(&lamp);
    screen::Camera::destroy(pCamera);
    data::Texture::destroy(pTexture);
    screen::MVP::destroy(pMVP);
    data::LoadData::destroy(pData);

    glfwTerminate();

    return 0;
}
