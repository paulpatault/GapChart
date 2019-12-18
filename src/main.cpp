#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>

#else
#include <GL/gl.h>
#endif

// namespace rgb
#include "includes/colors.h"

// namespace data
#include "src/data/LoadData.h"
#include "src/data/Cylinder.h"
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
    screen::Render window;

    screen::c_ImGui::init(window.render);

    GLuint v_ArrayID;
    data::VAO m_VAO(v_ArrayID);

    GLuint programID = data::Shaders::LoadShaders("../resources/shaders/SimpleVertexShader.glsl", "../resources/shaders/SimpleFragmentShader.glsl");

    screen::MVP::init_MatID(programID);

    data::LoadData myData("../resources/data/rankspts.csv");

    data::Cylinder m_cyl(0, &myData);
    std::vector<glm::vec3> tab = m_cyl.makeBottom();

    std::cout << tab.size() * 3 << std:: endl;

    data::VBO m_VBO( &myData, tab );

    do
    {
        screen::Display::clear();

        data::Shaders::bind(programID);

        screen::MVP::send_updated(window.render);

        screen::c_ImGui::loop();

        screen::Display::draw(programID, m_VBO, rgb::colors);

        screen::c_ImGui::maj(rgb::colors);

        screen::Display::update(window);
    }
    while( window.shouldNotClose() );

    //c_ImGui::terminate();
    glfwTerminate( );

    return 0;
}
