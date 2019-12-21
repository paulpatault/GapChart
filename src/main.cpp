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

    screen::Render window;

    screen::c_ImGui::init(window.render);

    GLuint v_ArrayID;
    data::VAO m_VAO(v_ArrayID);

    GLuint programID = data::Shaders::LoadShaders("../resources/shaders/SimpleVertexShader.glsl", "../resources/shaders/SimpleFragmentShader.glsl");

    screen::MVP::setLocation(programID);

    data::LoadData myData("../resources/data/rankspts.csv");

    std::vector<data::VBO> t_VBO_0 = makeVBO(myData);

    std::vector<data::VBO> t_VBO = t_VBO_0;

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
