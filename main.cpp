#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace glm;
using namespace std;

#include "LoadData.h"

#include "debugbreak.h"
#define ASSERT(x) if(!(x)) debug_break();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));
bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout << "[OpenGL Error] (" << error << ") at " << function << " in " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
void GLClearError(){
    while(glGetError()!= GL_NO_ERROR);
}



#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700
#define FSCREEN_WIDTH 1000.f
#define FSCREEN_HEIGHT 700.f


void escalier(const vec3 begin, const vec3 end, float vertices[], const int NUMBER_OF_POINTS, const float epaisseur, int winloose[]){
    vec3 tot[NUMBER_OF_POINTS];
    float dx = (end.x-begin.x)/(float)NUMBER_OF_POINTS;
    float dy = 3*(end.y-begin.y)/(float)NUMBER_OF_POINTS;

    int days = 0;
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        if(i%2 == 0) {
            tot[i].x = begin.x + (float)i * dx;
            if(i%4 == 0){
                if( i == 0 ){
                    tot[i].y = begin.y;
                }
                else if(winloose[days] == 0){
                    tot[i].y =  tot[i-2].y - dy;
                } else {
                    tot[i].y = tot[i-2].y + dy;
                }
                if(i != 0) {
                    days++;
                }
            } else{
                tot[i].y = tot[i-2].y;
            }
            tot[i].z = 0;
        } else {
            tot[i].x = tot[i-1].x;
            tot[i].y = tot[i-1].y + epaisseur;
            tot[i].z = 0;
        }
    }

    /// on rempli le tableau avec les pts obtenus
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        vertices[3*i] = tot[i].x;
        vertices[3*i+1] = tot[i].y;
        vertices[3*i+2] = tot[i].z;
    }
}

vector<float> y_Escalier(LoadData myData, int team) {

    int NUMBER_OF_DAYS = myData.cardDays();

    vector<float> res(NUMBER_OF_DAYS);

    float complementaire, points;

    for(int day = 0; day < NUMBER_OF_DAYS; day++)
    {
        complementaire = myData.getComplementaryRankNormalized(team, day);
        points = myData.getPointsNormalized(team, day);

        res[day] = (points + complementaire) * SCREEN_HEIGHT/2.2;
    }

    return res;
}

void tabEscalier(GLfloat vertices[], const int NUMBER_OF_POINTS, const float epaisseur, vector<float>  coordCenter) {
    vec2 tot[NUMBER_OF_POINTS];
    float dx = (SCREEN_WIDTH-100)/(float)NUMBER_OF_POINTS;
    float x0 = 50;
    int days = 0;
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        if(i % 4 == 0)  // i divisible par 4 => debut de nouveau rectangle (->point haut gauche)
        {
            tot[i].x = x0 + (float) i * dx;
            if( i == 0 ) // on prend y0 pour le premier sommet du premier rectangle (->point haut gauche)
            {
                tot[i].y = coordCenter[0]; // == y0 (at t = 0)
            }
            else
            {
                tot[i].y = coordCenter[days];
            }

            if(i != 0)  // on change de jour pour chaque nouveau rectangle sauf pour le premier
            {
                days += 1;
            }
        }
        else if (i % 2 == 0) // i divisible par 2 => point haut droit du rectangle
        {
            tot[i].x = x0 + (float) i * dx;
            tot[i].y = tot[i - 2].y;
        }
        else // i impair => les autres points (:= bas gauche ou bas droit)
        {
            tot[i].x = tot[i - 1].x;
            tot[i].y = tot[i - 1].y + epaisseur;
        }
    }
    /// on rempli le tableau avec les pts obtenus
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        vertices[3*i] = tot[i].x;
        vertices[3*i+1] = tot[i].y + 20; // +20 pour que le plus bas ne touche pas le bas de la fenetre
        vertices[3*i+2] = 0;
    }
}


// Charge un programme de shaders, le compile et recupere dedans des pointeurs vers
// les variables homogenes que nous voudront mettre a jour plus tard, a chaque dessin
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    glValidateProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

int main( )
{
    // Initialize the library
    if ( !glfwInit( ) )
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    GLFWwindow *window;


    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL


    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL );


    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    //gère le transparence
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    cout << "version :: " << glGetString(GL_VERSION) << endl;


    // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders("../SimpleVertexShader.glsl", "../SimpleFragmentShader.glsl");


    /// matrice pour changement de repère
    GLCall(GLint matrixID = glGetUniformLocation(programID, "u_MVP") );
    mat4 my_projection = ortho(0.f,FSCREEN_WIDTH,0.f,FSCREEN_HEIGHT,-1.f,1.f);
    glUseProgram(programID);
    GLCall( glUniformMatrix4fv(matrixID,1,GL_FALSE,&my_projection[0][0]) );
    glUseProgram(0);



    LoadData myData("../DataProjet2019/data/rankspts.csv");

    // 4 pour les 4 coins des rectangles, 38 jours, +4 dernier rectangle
    int NB_POINTS = 4 * 38 + 4;
    float epaisseur = ((float)SCREEN_HEIGHT/2)/20;
    GLfloat t_vertex_data[20][NB_POINTS * 3];  // * 3 car {x,y,z} pour chaque point

    for(int team = 0; team < 20; team++)
    {
        vector<float> myVec1 = y_Escalier(myData, team);
        tabEscalier(t_vertex_data[team], NB_POINTS, epaisseur, myVec1);
    }


    GLuint vertexbuffer[20];
    for(int i = 0; i < 20; i++){
        glGenBuffers(1, &vertexbuffer[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex_data[i]), t_vertex_data[i], GL_STATIC_DRAW);
    }


    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    glm::vec4 top1(0.f,0.f,0.8f,1.f);
    glm::vec4 top(98.f/255.f,214.f/255.f,230.f/255.f,1.f);
    glm::vec4 top_mid(236.f/255.f,238.f/255.f,26.f/255.f,1.f);
    glm::vec4 mid(194.f/255.f,194.f/255.f,194.f/255.f,1.f);
    glm::vec4 bot_mid(140.f/255.f,140.f/255.f,140.f/255.f,1.f);
    glm::vec4 bot(239.f/255.f,113.f/255.f,113.f/255.f,1.f);

    do
    {
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        glUseProgram(programID);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for(int i = 0; i < 20; i++){

            GLint colorID = glGetUniformLocation(programID,"u_color");
            if(i == 0)
            {
                glUniform4f(colorID, top1[0], top1[1], top1[2], top1[3] );
            }
            else if(i < 4)
            {
                glUniform4f(colorID, top[0], top[1], top[2], top[3] );
            }
            else if(i < 7)
            {
                glUniform4f(colorID, top_mid[0], top_mid[1], top_mid[2], top_mid[3] );
            }
            else if(i < 9)
            {
                glUniform4f(colorID, mid[0], mid[1], mid[2], mid[3] );
            }
            else if(i < 15)
            {
                glUniform4f(colorID, bot_mid[0], bot_mid[1], bot_mid[2], bot_mid[3] );
            }
            else
            {
                glUniform4f(colorID, bot[0], bot[1], bot[2], bot[3] );
            }

            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
            glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)nullptr            // array buffer offset
            );

            // Draw the triangle !
            glDrawArrays(GL_TRIANGLE_STRIP, 0, NB_POINTS);

            glDisableVertexAttribArray(0);
        }

        ImGui::ColorEdit3("top1 color", (float*)&top1);
        ImGui::ColorEdit3("top color", (float*)&top);
        ImGui::ColorEdit3("top_mid color", (float*)&top_mid);
        ImGui::ColorEdit3("mid color", (float*)&mid);
        ImGui::ColorEdit3("bot_mid color", (float*)&bot_mid);
        ImGui::ColorEdit3("bot color", (float*)&bot);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers( window );

        // Poll for and process events
        glfwPollEvents( );

    } while( (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(window) == 0) ); // Loop until the user closes the window

    glfwTerminate( );

    return 0;
}
