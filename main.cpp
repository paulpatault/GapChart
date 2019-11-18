// Include standard headers
#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Include ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
using namespace ImGui;

// My includes
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
#define CYLINDRE

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

std::vector<float> y_Escalier(LoadData myData, int team) {

    const int NUMBER_OF_DAYS = myData.cardDays();

    std::vector<float> res(NUMBER_OF_DAYS);

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
            tot[i].y = tot[i - 1].y - epaisseur;
        }
    }
    /// on rempli le tableau avec les pts obtenus
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        vertices[3*i] = tot[i].x;
        vertices[3*i+1] = tot[i].y + 35; // +40 pour que le plus bas ne touche pas le bas de la fenetre
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

int main( void )
{
    // Initialize the library
    if ( !glfwInit( ) )
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
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
        std::cerr << "Fail link to window" << std::endl;
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    //gère le transparence
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    std::cout << "Version == " << glGetString(GL_VERSION) << std::endl;

    // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Couleur de fond := blanc
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders("../SimpleVertexShader.glsl", "../SimpleFragmentShader.glsl");

    /// initialisation des matrices du modèle MVP (ModelViewProjection)
    GLCall(GLint matrixID = glGetUniformLocation(programID, "u_MVP") );
    glm::mat4 Projection = ortho(0.f,FSCREEN_WIDTH,0.f,FSCREEN_HEIGHT,-1.f,1.f);
    // Camera matrix
    const float _x = 0.f;
    const float _y = 0.f;
    const float _z = -1.f;
    glm::mat4 View = glm::lookAt(
            glm::vec3(_x, _y,_z), // Camera is at (x,y,z), in World Space
            glm::vec3(_x + 0.f, _y + 0.f,_z - 1.f), // and looks at the origin
            glm::vec3(0.f,1.f,0.f)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix := identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model; // Attention à bien les multiplier "à l'envers"

    glUseProgram(programID);
    GLCall( glUniformMatrix4fv(matrixID,1,GL_FALSE,&mvp[0][0]) );
    glUseProgram(0);


    /// REMPLISSAGE DES TABLEAUX AVEC LES DONNÉES
    LoadData myData("../DataProjet2019/data/rankspts.csv");

    // 4 pour les 4 coins des rectangles, 38 jours, +4 dernier rectangle
    const int NB_POINTS = 4 * 38 + 4;
    const float epaisseur = ((float)SCREEN_HEIGHT/2)/20;
    GLfloat t_vertex_data[20][NB_POINTS * 3];  // * 3 car {x,y,z} pour chaque point

    std::vector<float> tabY(myData.cardDays());
    for(int team = 0; team < 20; team++)
    {
        tabY = y_Escalier(myData, team);
        tabEscalier(t_vertex_data[team], NB_POINTS, epaisseur, tabY);
        if(team==19)
            for(int i = 0; i < 10; i ++)
                cout << " " << tabY[i]+20 << "  ";
    }
    cout << endl;

#if defined(CYLINDRE)

    const int nbDivCylindre = 3;
    const float delta_epaisseur = epaisseur/nbDivCylindre;

    GLfloat t_vertex_data_dim3[20][nbDivCylindre][NB_POINTS * 3];  // * 3 car {x,y,z} pour chaque point

    for(int team = 0; team < 20; team++)
    {
        for(int i = 0; i < NB_POINTS * 3; i += 3)
        {
            if(i % 2 == 0 ){

                for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++){
                    t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                         // .x
                    t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] - (sous_tableau * delta_epaisseur);  // .y
                    t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2];                                     // .z
                }
            } else {
                for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++){
                    t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                                                         // .x
                    t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] + ( (float)(nbDivCylindre - 1 - sous_tableau) * delta_epaisseur );   // .y
                    t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2];                                                                     // .z
                }
            }
        }
    }


    GLuint cylindre_vertexbuffer[20][nbDivCylindre];
    for(int i = 0; i < 20; i++){
        for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++) {
            glGenBuffers(1, &cylindre_vertexbuffer[i][sous_tableau]);
            glBindBuffer(GL_ARRAY_BUFFER, cylindre_vertexbuffer[i][sous_tableau]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex_data_dim3[i][sous_tableau]), t_vertex_data_dim3[i][sous_tableau], GL_STATIC_DRAW);

        }
    }

#elif defined(NORMAL)
    GLuint vertexbuffer[20];
    for(int i = 0; i < 20; i++){
        glGenBuffers(1, &vertexbuffer[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex_data[i]), t_vertex_data[i], GL_STATIC_DRAW);
    }
#endif

    /// Initialisation de ImGui
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Couleurs pour chaque regroupement de courbes
    glm::vec4 top1(0.f,72.f/255.f,204.f/255.f,1.f);
    glm::vec4 top(98.f/255.f,214.f/255.f,230.f/255.f,1.f);
    glm::vec4 top_mid(236.f/255.f,238.f/255.f,26.f/255.f,1.f);
    glm::vec4 mid(194.f/255.f,194.f/255.f,194.f/255.f,1.f);
    glm::vec4 bot_mid(140.f/255.f,140.f/255.f,140.f/255.f,1.f);
    glm::vec4 bot(231.f/255.f,97.f/255.f,97.f/255.f,1.f);

    do
    {
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        glUseProgram(programID);

        // ImGui loop
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw
        for(int i = 0; i < 20; i++)
        {

#if defined(CYLINDRE)

            for(int j = 0; j < nbDivCylindre; j++)
            {
                GLint colorID = glGetUniformLocation(programID,"u_color");
                {
                    if(i == 0) glUniform4f(colorID, top1[0], top1[1], top1[2], top1[3] );                  // TOP 1
                    else if(i < 4) glUniform4f(colorID, top[0], top[1], top[2], top[3] );                  // 3 suivants
                    else if(i < 7) glUniform4f(colorID, top_mid[0], top_mid[1], top_mid[2], top_mid[3] );  // 3 suivants
                    else if(i < 9) glUniform4f(colorID, mid[0], mid[1], mid[2], mid[3] );                  // 2 suivants
                    else if(i < 15) glUniform4f(colorID, bot_mid[0], bot_mid[1], bot_mid[2], bot_mid[3] ); // les autres
                    else glUniform4f(colorID, bot[0], bot[1], bot[2], bot[3] );                            // le dernier
                }

                glEnableVertexAttribArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, cylindre_vertexbuffer[i][j]);

                glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        3,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)nullptr            // array buffer offset
                );

                // Draw the triangle !
                glDrawArrays(GL_TRIANGLE_STRIP, 0, NB_POINTS );

                glDisableVertexAttribArray(0);
            }


#elif defined(NORMAL)
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
#endif

        } // fin du for ( [0,20[ )

        // ImGui Edit (màj)
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
    }
    // Loop until the user closes the window
    while( (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(window) == 0) );

    glfwTerminate( );

    return 0;
}
