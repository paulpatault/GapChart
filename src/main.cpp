#include "includes/main_includes.h"

int main()
{
    /// Instance of the class Render that manages the window + initialise GL
    screen::Render window("Projet IGSD", vec4(0.7f));

    /// ImGui context
    screen::c_ImGui::init(window.screen);

    /// Vertex Array
    GLuint vaoID;
    data::VAO m_VAO( vaoID );
    //data::VAO m_VAO( ( GLuint() ) );

    /// Load Shaders
    data::Shader programShader("../resources/shaders/SimpleVertexShader.glsl",
                               "../resources/shaders/SimpleFragmentShader.glsl");

    data::Shader lampShader("../resources/shaders/lamp_vs.glsl",
                            "../resources/shaders/lamp_fs.glsl");

    /// Lamp for lighting
    screen::Lamp lamp;

    /// Camera
    screen::Camera cam(glm::vec3(0.0f, 0.0f, 1000.0f));

    /// Model View Projection Matrix
    screen::MVP MVP;

    /// Instance of the class LoadData that manages the .csv
    data::LoadData myData("../resources/data/rankspts.csv");

    /// Vector of 20 VBOs
    /// Usable VBOs in t_VBO and t_VBO_0 saving
    var::t_VBO = utils::makeVBOs(myData);
    var::t_VBO_0 = var::t_VBO;

    /// Vector of 20 textures
    std::vector<data::Texture> tab;
    for(int i = 0; i < cst::NB_TEAMS; i++)
    {
        data::Texture t((GLuint()), myData.getImagesPath(i));
        tab.push_back(t);
    }

    /// Main loop
    do
    {
        utils::updateTime(var::deltaTime, var::lastFrame);

        screen::Display::clear();


        screen::Camera::processInput(&cam, window.screen, 10 * var::deltaTime);

        MVP.maj(window.screen);

        data::Shader::use(programShader);

        programShader.setMat4("u_Model", *MVP.getModelMatrix());
        programShader.setMat4("u_Rotate", *MVP.getRotationMatrix());
        programShader.setMat4("u_View", cam.getViewMatrix());
        programShader.setMat4("u_Projection", *MVP.getProjectionMatrix());
        programShader.setVec3("u_CameraPos", *cam.getPosition());
        programShader.setVec3("u_lightPos", lamp.getPosition());

        screen::c_ImGui::loop();

        screen::Display::selectionCallBack(window.screen, var::selector);

        utils::majVBOs(var::t_VBO, var::selector, &myData);

        screen::Display::draw(programShader.ID, var::t_VBO, var::colors, var::selector);

        data::Shader::use(lampShader);

        lampShader.setMat4("projection", *MVP.getProjectionMatrix());
        lampShader.setMat4("view", cam.getViewMatrix());

        screen::Lamp::update(&lamp);

        lampShader.setMat4("model", lamp.getModelMatrix());

        screen::Lamp::draw(&lamp);

        glm::vec3 lp = lamp.getPosition();

        screen::c_ImGui::maj(var::colors, lp);

        lamp.setPosition(lp);

        screen::Display::update(window);

    } while( window.shouldNotClose() );

    screen::c_ImGui::terminate();
    glfwTerminate();

    return 0;
}
