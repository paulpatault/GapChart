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


int main()
{
    Render window;

    GLuint v_ArrayID;
    VAO m_VAO(v_ArrayID);

    GLuint programID = LoadShaders("../resources/shaders/SimpleVertexShader.glsl", "../resources/shaders/SimpleFragmentShader.glsl");

    MVP::init_MatID(programID);

    LoadData myData("../resources/data/rankspts.csv");

    VBO m_VBO( &myData );

    glm::vec4 colors[] = {
            /*
            glm::vec4(92.f/255.f,133.f/255.f,209.f/255.f,1.f),            // top1
            glm::vec4(142.f/255.f,217.f/255.f,228.f/255.f,1.f),    // top
            glm::vec4 (234.f/255.f,235.f/255.f,89.f/255.f,1.f),   // top_mid
            glm::vec4 (213.f/255.f,213.f/255.f,213.f/255.f,1.f),  // mid
            glm::vec4 (168.f/255.f,168.f/255.f,168.f/255.f,1.f),  // bot_mid
            glm::vec4 (233.f/255.f,139.f/255.f,139.f/255.f,1.f)     // bot
            */
            glm::vec4(0.f,72.f/255.f,204.f/255.f,1.f),            // top1
            glm::vec4(98.f/255.f,214.f/255.f,230.f/255.f,1.f),    // top
            glm::vec4 (236.f/255.f,238.f/255.f,26.f/255.f,1.f),   // top_mid
            glm::vec4 (194.f/255.f,194.f/255.f,194.f/255.f,1.f),  // mid
            glm::vec4 (140.f/255.f,140.f/255.f,140.f/255.f,1.f),  // bot_mid
            glm::vec4 (240.f/255.f,35.f/255.f,35.f/255.f,1.f)     // bot
    };

    c_ImGui::init(window.render);

    do
    {
        Display::clear();

        MVP::send_new(window.render);

        c_ImGui::loop();

        Display::draw(programID, m_VBO, colors);

        c_ImGui::maj(colors);

        Display::update(window);
    }
    while( window.shouldNotClose() );

    c_ImGui::terminate();
    glfwTerminate( );

    return 0;
}
