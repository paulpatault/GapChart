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
#include "src/data/Arc.h"
#include "src/data/Shaders.h"
#include "src/data/VAO.h"
#include "src/data/VBO.h"

// namespace screen
#include "src/screen/MVP.h"
#include "src/screen/c_ImGui.h"
#include "src/screen/Render.h"
#include "src/screen/Display.h"


std::vector<data::VBO> t_VBO_0;
data::LoadData myData("../resources/data/rankspts.csv");


std::vector<data::VBO> makeVBO()
{
    std::vector<data::VBO> res;

    for(int team = 0; team < cst::NB_TEAMS; team++)
    {
        data::Cylinder cyl(team, &myData);

        std::vector<glm::vec3> combined = cyl.makeCombinedCylinder(false);

        std::vector<float> cylinder;
        for(int i = 0; i < combined.size(); i++)
        {
            cylinder.push_back(combined[i].x);
            cylinder.push_back(combined[i].y);
            cylinder.push_back(combined[i].z);
        }

        std::vector<float> normals = cyl.makeNormals(cylinder);
        data::VBO m_VBO( &myData , cylinder , normals);

        res.push_back(m_VBO);
    }

    return res;
}

std::vector<data::VBO> updateVBO(int selected)
{
    if(selected == -1)
    {
        return t_VBO_0;
    }

    std::vector<data::VBO> res;

    for(int team = 0; team < cst::NB_TEAMS; team++)
    {
        data::Cylinder cyl(team, &myData);
        data::Arc arc(team, &myData);

        std::vector<glm::vec3> back = cyl.makeBackFace(false);
        std::vector<glm::vec3> v3_cylinder = cyl.makeHalfCircles(back, false);
        std::vector<glm::vec3> arcs = arc.makeArcs(v3_cylinder);

        bool front = false;
        if(team == selected)
            front = true;

        std::vector<glm::vec3> combined = cyl.makeCombinedCylinder(front);


        std::vector<float> cylinder;
        for(int i = 0; i < combined.size(); i++)
        {
            cylinder.push_back(combined[i].x);
            cylinder.push_back(combined[i].y);
            cylinder.push_back(combined[i].z);
        }

        std::vector<float> normals = cyl.makeNormals(cylinder);
        data::VBO m_VBO( &myData , cylinder , normals);

        res.push_back(m_VBO);
    }

    return res;
}

int main()
{
    int selected = -1;

    screen::Render window;

    screen::c_ImGui::init(window.render);

    GLuint v_ArrayID;
    data::VAO m_VAO(v_ArrayID);

    GLuint programID = data::Shaders::LoadShaders("../resources/shaders/SimpleVertexShader.glsl", "../resources/shaders/SimpleFragmentShader.glsl");

    screen::MVP::setLocation(programID);

    t_VBO_0 = makeVBO();

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

        t_VBO = updateVBO(selected);

    }
    while( window.shouldNotClose() );

    screen::c_ImGui::terminate();
    glDeleteVertexArrays(1, &v_ArrayID);
    ///glDeleteBuffers(1, &v_ArrayID);
    glfwTerminate( );

    return 0;
}
