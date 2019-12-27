#include "includes/main_includes.h"

int main()
{
    /// Instance of the class Render that manages the window
    screen::Render window;

    /// ImGui context
    screen::c_ImGui::init(window.render);

    /// Vertex Array
    GLuint v_ArrayID;
    data::VAO m_VAO(v_ArrayID);

    /// Load Shaders
    data::Shader shaders("../resources/shaders/SimpleVertexShader.glsl",
                         "../resources/shaders/SimpleFragmentShader.glsl");

    /// Model View Projection Location
    //screen::MVP::setLocation(shaders.ID);

    /// Instance of the class LoadData that manages the .csv
    data::LoadData myData("../resources/data/rankspts.csv");

    /// Vector of 20 VBOs
    /// Usable VBOs in t_VBO and t_VBO_0 saving
    var::t_VBO = utils::makeVBOs(myData);
    var::t_VBO_0 = var::t_VBO;

    glm::vec3 lp;
    lp.x = 500.f;
    lp.y = 350.f;
    lp.z = 1000.f;

    /// Main loop
    do
    {
        screen::Display::clear();

        data::Shader::use(shaders);

        screen::MVP::send_updated(window.render, &shaders);

        screen::c_ImGui::loop();

        screen::Display::selectionCallBack(window.render, var::selector);

        utils::majVBOs(var::t_VBO, var::selector, &myData);

        shaders.setVec3("u_lightPos", lp);
        
        screen::Display::draw(shaders.ID, var::t_VBO, var::colors, var::selector);

        screen::c_ImGui::maj(var::colors, lp);

        screen::Display::update(window);
    }
    while( window.shouldNotClose() );

    screen::c_ImGui::terminate();
    glDeleteVertexArrays(1, &v_ArrayID);
    ///glDeleteBuffers(1, &v_ArrayID);
    glfwTerminate( );

    return 0;
}
