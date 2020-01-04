#include "includes/main_includes.h"

int main()
{
    /// Instance of the class Render that manages the window + initialise GL
    screen::Render window("Projet IGSD", vec4(1.f));

    /// ImGui context
    screen::c_ImGui::init(window.screen);

    /// Vertex Array
    data::VAO m_VAO( ( GLuint() ) );

    /// Shaders
    /// curves shader
    data::Shader programShader("../resources/shaders/SimpleVertexShader.glsl",
                               "../resources/shaders/SimpleFragmentShader.glsl");
    /// lamp shader
    data::Shader lampShader("../resources/shaders/lamp_vs.glsl",
                            "../resources/shaders/lamp_fs.glsl");
    /// texture shader
    data::Shader titleShader("../resources/shaders/title_vs.glsl",
                            "../resources/shaders/title_fs.glsl");

    /// Lamp for lighting
    screen::Lamp lamp(glm::vec3(2000.f, 288.f, 3718.f));

    /// Camera
    screen::Camera cam(glm::vec3(0.0f, 0.0f, 1000.0f));

    /// Texture 0
    data::Texture myTexture("../resources/images/Arsenal.png");

    /// Model View Projection Matrix
    screen::MVP MVP;

    /// Instance of the class LoadData that manages the .csv
    data::LoadData myData("../resources/data/rankspts.csv");

    /// Vector of 20 VBOs
    /// Usable VBOs in t_VBO and t_VBO_0 saving
    var::t_VBO = utils::makeVBOs(myData);
    var::t_VBO_0 = var::t_VBO;

    /// Main loop
    do
    {
        utils::updateTime(var::deltaTime, var::lastFrame);

        screen::Display::clear();

        screen::c_ImGui::loop();

        ///--------- curves ---------///
        data::Shader::use(programShader);
        data::Shader::setMat4_stat(&programShader, "u_Model", *MVP.getModelMatrix());
        data::Shader::setMat4_stat(&programShader, "u_Rotate", *MVP.getRotationMatrix());
        data::Shader::setMat4_stat(&programShader, "u_View", cam.getViewMatrix());
        data::Shader::setMat4_stat(&programShader, "u_Projection", *MVP.getProjectionMatrix());
        data::Shader::setVec3_stat(&programShader, "u_CameraPos", *cam.getPosition());
        data::Shader::setVec3_stat(&programShader, "u_lightPos", lamp.getPosition());
        screen::Display::draw(programShader.ID, var::t_VBO, var::colors, var::selector);

        ///--------- textures ---------///
        data::Texture::update(&myTexture, &myData, &var::selector);
        data::Shader::use(titleShader);
        data::Shader::setMat4_stat(&titleShader, "u_Model", myTexture.modelMatrix);
        data::Texture::draw(&myTexture, var::selector.selected);

        ///--------- lamp ---------///
        data::Shader::use(lampShader);
        data::Shader::setMat4_stat(&lampShader, "projection", *MVP.getProjectionMatrix());
        data::Shader::setMat4_stat(&lampShader, "view", cam.getViewMatrix());
        data::Shader::setMat4_stat(&lampShader, "model", lamp.getModelMatrix());
        screen::Lamp::draw_stat(&lamp);

        ///--------- updates ---------///
        screen::Camera::processInput(&cam, window.screen, 10 * var::deltaTime);
        screen::MVP::maj_stat(&MVP, window.screen);
        screen::Display::selectionCallBack(window.screen, var::selector);
        utils::majVBOs(var::t_VBO, var::selector, &myData);
        screen::Lamp::update(&lamp);

        glm::vec3 lp = lamp.getPosition();
        screen::c_ImGui::maj(var::colors, lp);
        lamp.setPosition(lp);

        screen::Display::update(window);

    } while( window.shouldNotClose() );

    screen::c_ImGui::terminate();
    data::VAO::destroy(&m_VAO);
    screen::Lamp::destroy(&lamp);
    glfwTerminate();

    return 0;
}
