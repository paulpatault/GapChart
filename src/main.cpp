#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>

#else
#include <GL/gl.h>
#endif

// namespace rgb
#include "includes/colors.h"
#include "includes/utils.h"

// namespace data
#include "src/data/LoadData.h"
#include "src/data/Cylinder.h"
#include "src/data/Arc.h"
#include "src/data/Shaders.h"
#include "src/data/VAO.h"
#include "src/data/VBO.h"

// namespace screen
#include "src/screen/MVP.h"
#include "src/screen/c_ImGui.h"
#include "src/screen/Render.h"
#include "src/screen/Display.h"


int main()
{
    int selected = -1;

    /// Instance of the class Render that manages the window
    screen::Render window;

    /// ImGui context
    screen::c_ImGui::init(window.render);

    /// Vertex Array
    GLuint v_ArrayID;
    data::VAO m_VAO(v_ArrayID);

    /// Set Program ID
    GLuint programID = data::Shaders::LoadShaders(
            "../resources/shaders/SimpleVertexShader.glsl",
            "../resources/shaders/SimpleFragmentShader.glsl");

    /// Model View Projection Location
    screen::MVP::setLocation(programID);

    /// Instance of the class LoadData that manages the .csv
    data::LoadData myData("../resources/data/rankspts.csv");

    /// Vector of 20 VBOs
    /// Usable VBOs in t_VBO and t_VBO_0 saving
    std::vector<data::VBO> t_VBO_0 = makeVBO(myData);
    std::vector<data::VBO> t_VBO = t_VBO_0;

    /// Main loop
    do
    {
        screen::Display::clear();

        data::Shaders::bind(programID);

        screen::MVP::send_updated(window.render);

        screen::c_ImGui::loop();

        screen::Display::draw(programID, t_VBO, rgb::colors, selected);

        screen::c_ImGui::maj(rgb::colors);

        selected = screen::Display::update(window);

        t_VBO = updateVBO(myData, t_VBO_0, selected);

    }
    while( window.shouldNotClose() );

    screen::c_ImGui::terminate();
    glDeleteVertexArrays(1, &v_ArrayID);
    ///glDeleteBuffers(1, &v_ArrayID);
    glfwTerminate( );

    return 0;
}
