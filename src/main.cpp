#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>

#include "src/LoadData/LoadData.h"
#include "src/Shaders/Shaders.h"
#include "src/MPV/MVP.h"
#include "src/imgui/c_ImGui.h"
#include "src/Window/Render.h"
#include "src/VAO/VAO.h"
#include "src/VBO/VBO.h"
#include "src/Display/Display.h"
#include "includes/colors.h"

int main()
{
    Render window;

    c_ImGui::init(window.render);

    GLuint v_ArrayID;
    VAO m_VAO(v_ArrayID);

    GLuint programID = LoadShaders("../resources/shaders/SimpleVertexShader.glsl", "../resources/shaders/SimpleFragmentShader.glsl");

    MVP::init_MatID(programID);

    LoadData myData("../resources/data/rankspts.csv");

    VBO m_VBO( &myData );

    do
    {
        Display::clear();

        MVP::send_updated(window.render);

        c_ImGui::loop();

        Display::draw(programID, m_VBO, rgb::colors);

        c_ImGui::maj(rgb::colors);

        Display::update(window);
    }
    while( window.shouldNotClose() );

    c_ImGui::terminate();
    glfwTerminate( );

    return 0;
}
