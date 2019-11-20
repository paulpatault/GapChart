// Include standard headers
#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
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
#include "src/imgui/imgui.h"
#include "src/imgui/imgui_impl_glfw.h"
#include "src/imgui/imgui_impl_opengl3.h"
using namespace ImGui;

// My includes
#include "src/myFiles/LoadData.h"
#include "src/myFiles/Escalier.h"
#include "src/debugbreak.h"


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700
#define FSCREEN_WIDTH 1000.f
#define FSCREEN_HEIGHT 700.f


glm::mat4 updateMVP(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, glm::vec3 angle, glm::vec2 zNearFar, glm::vec3 eyePos){

    /// Projection Matrix ///
    Projection = glm::perspective(glm::radians(45.f), FSCREEN_WIDTH/FSCREEN_HEIGHT, zNearFar.x, zNearFar.y );

    /// View Matrix ///
    glm::vec3 eye    = glm::vec3(eyePos);
    glm::vec3 center = glm::vec3(0.f, 0.f, zNearFar.x);
    glm::vec3 up     = glm::vec3(0.f, 1.f, 0.f);
    View = glm::lookAt( eye, center, up );

    /// Model Matrix ///
    // rotation
    glm::vec3 xAxis = glm::vec3(1, 0, 0);
    glm::vec3 yAxis = glm::vec3(0, 1, 0);
    glm::vec3 zAxis = glm::vec3(0, 0, 1);
    Model = glm::rotate(Model, glm::radians(angle.x), xAxis);
    Model = glm::rotate(Model, glm::radians(angle.y), yAxis);
    Model = glm::rotate(Model, glm::radians(angle.z), zAxis);
    Model = glm::rotate(Model, glm::radians(-90.f), xAxis);

    // scale
    /*
    glm::vec3 scaleXYZ = vec3(scale);
    Model = glm::scale(Model, scaleXYZ);
    */

    // translation
    glm::vec3 translation = glm::vec3(- FSCREEN_WIDTH/2, - FSCREEN_HEIGHT/2,0.f);
    Model = glm::translate(Model, translation);

    /// ModelViewProjection Matrix ///
    return Projection * View * Model;
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

int main(void)
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
    GLint matrixID = glGetUniformLocation(programID, "u_MVP");

    glm::vec3 eyePos = glm::vec3(0.f, 0.f, 1000.f);
    glm::vec2 zNearFar = glm::vec2(-100.f, 100.f);
    glm::vec3 angle = glm::vec3(90.f, 0.f,0.f);

    glm::mat4 Projection = glm::mat4(1.0f);
    glm::mat4 View = glm::mat4(1.0f);
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = updateMVP(Model, View, Projection, angle, zNearFar, eyePos);

    glUseProgram(programID);
    GLCall( glUniformMatrix4fv(matrixID,1,GL_FALSE,&mvp[0][0]) );
    glUseProgram(0);




    /// REMPLISSAGE DES TABLEAUX AVEC LES DONNÉES
    LoadData myData("../DataProjet2019/data/rankspts.csv");
    const int NB_DAYS = myData.cardDays();
    const int NB_TEAMS = myData.cardTeams();
    // 4 pour les 4 coins des rectangles, NB_DAYS jours, +4 dernier rectangle
    const int NB_POINTS = 4 * (NB_DAYS + 1);
    const float epaisseur = ((float)SCREEN_HEIGHT/2)/NB_TEAMS;
    const float dx = (SCREEN_WIDTH-100)/(float)NB_POINTS;
    GLfloat t_vertex_data[NB_TEAMS][NB_POINTS * 3];  // * 3 car {x,y,z} pour chaque point

    std::vector<float> tabY(NB_DAYS);
    std::vector<vector<float>> yEscBis(NB_TEAMS);
    for(int team = 0; team < NB_TEAMS; team++)
    {
        tabY = y_Escalier(myData, team, FSCREEN_HEIGHT);
        yEscBis[team] = y_Escalier(myData, team, FSCREEN_HEIGHT);
        tabEscalier(t_vertex_data[team], NB_POINTS, epaisseur, dx, tabY);
    }

    // comme les pts A et B dans le sujet
    glm::vec3 centre[NB_TEAMS][NB_DAYS + 1];
    glm::vec3 centreDecale[NB_TEAMS][2 * NB_DAYS + 1];

    for(int team = 0; team < NB_TEAMS; team++)
    {
        for(int day = 0; day < NB_DAYS; day++)
        {
            centre[team][day].x = 50 + (float)day * dx * 2;   // * 2 car on passe de A à C à E à G à etc.
            centre[team][day].y = yEscBis[team][day] + (epaisseur / 2);
            centre[team][day].z = 0;
        }
        centre[team][NB_DAYS] = centre[team][NB_DAYS - 1];


        for(int day = 0; day < NB_DAYS * 2; day++)
        {
            if(day % 2 == 0)
            {
                centreDecale[team][day].x = centre[team][day / 2].x ;
                centreDecale[team][day].y = centre[team][day / 2].y ;
                centreDecale[team][day].z = centre[team][day / 2].z ;
            } else {
                centreDecale[team][day].x = ( centre[team][day / 2].x + centre[team][(day / 2) + 1].x ) / 2;
                centreDecale[team][day].y = ( centre[team][day / 2].y + centre[team][(day / 2) + 1].y ) / 2;
                centreDecale[team][day].z = ( centre[team][day / 2].z + centre[team][(day / 2) + 1].z ) / 2;
            }
        }

        centreDecale[team][NB_DAYS * 2] = centre[team][NB_DAYS];

    }


    const int nbDivCylindre = 3;
    const float delta_epaisseur = epaisseur/nbDivCylindre;

    GLfloat t_vertex_data_dim3[NB_TEAMS][nbDivCylindre][NB_POINTS * 3];  // * 3 car {x,y,z} pour chaque point
    glm::vec3 normals[NB_TEAMS][NB_DAYS * 2][nbDivCylindre];

    for(int team = 0; team < NB_TEAMS; team++)
    {
        for(int i = 0; i < NB_POINTS * 3; i += 3)
        {

            if(i % 2 == 0 ){
                for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++){
                    t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                         // .x
                    t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] - (sous_tableau * delta_epaisseur);  // .y
                    t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2] + (sous_tableau * epaisseur / nbDivCylindre) ;              // .z
                }
            } else {
                for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++){
                    t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                                                         // .x
                    t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] + ( (float)(nbDivCylindre - 1 - sous_tableau) * delta_epaisseur );   // .y
                    t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2] + ( (float)(nbDivCylindre - 1 - sous_tableau) * epaisseur / nbDivCylindre );
                }
            }
        }
        for(int day = 0; day < NB_DAYS * 2; day++)
        {
            for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++)
            {
                normals[team][day][sous_tableau].x = t_vertex_data_dim3[team][sous_tableau][day]     - centreDecale[team][day].x;
                normals[team][day][sous_tableau].y = t_vertex_data_dim3[team][sous_tableau][day + 1] - centreDecale[team][day].y;
                normals[team][day][sous_tableau].z = t_vertex_data_dim3[team][sous_tableau][day + 2] - centreDecale[team][day].z;
            }
        }
    }

    GLuint cylindre_vertexbuffer[NB_TEAMS][nbDivCylindre];
    for(int team = 0; team < NB_TEAMS; team++){
        for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++){
            glGenBuffers(1, &cylindre_vertexbuffer[team][sous_tableau]);
            glBindBuffer(GL_ARRAY_BUFFER, cylindre_vertexbuffer[team][sous_tableau]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex_data_dim3[team][sous_tableau]), t_vertex_data_dim3[team][sous_tableau], GL_STATIC_DRAW);
        }
    }




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
    glm::vec4 bot(240.f/255.f,35.f/255.f,35.f/255.f,1.f);

    do
    {

        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        glUseProgram(programID);


        /// Move, Rotate
        mvp = updateMVP(Model, View, Projection, angle, zNearFar, eyePos);
        // Send new matrix
        glUniformMatrix4fv(
                matrixID,
                1,
                GL_FALSE,
                &mvp[0][0]
                );

        // ImGui loop
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw
        for(int team = 0; team < NB_TEAMS; team++)
        {
            for(int j = 0; j < nbDivCylindre; j++)
            {
                GLint colorID = glGetUniformLocation(programID,"u_color");
                {
                    if(team == 0) glUniform4f(colorID, top1[0], top1[1], top1[2], top1[3] );                  // TOP 1
                    else if(team < 4) glUniform4f(colorID, top[0], top[1], top[2], top[3] );                  // 3 suivants
                    else if(team < 7) glUniform4f(colorID, top_mid[0], top_mid[1], top_mid[2], top_mid[3] );  // 3 suivants
                    else if(team < 9) glUniform4f(colorID, mid[0], mid[1], mid[2], mid[3] );                  // 2 suivants
                    else if(team < 15) glUniform4f(colorID, bot_mid[0], bot_mid[1], bot_mid[2], bot_mid[3] ); // les autres
                    else glUniform4f(colorID, bot[0], bot[1], bot[2], bot[3] );                            // le dernier
                }

                glEnableVertexAttribArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, cylindre_vertexbuffer[team][j]);

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
        }


        // ImGui Edit (màj)
        /*
        ImGui::ColorEdit3("top1 color", (float*)&top1);
        ImGui::ColorEdit3("top color", (float*)&top);
        ImGui::ColorEdit3("top_mid color", (float*)&top_mid);
        ImGui::ColorEdit3("mid color", (float*)&mid);
        ImGui::ColorEdit3("bot_mid color", (float*)&bot_mid);
        ImGui::ColorEdit3("bot color", (float*)&bot);
        */

        ImGui::SliderFloat("angleX", &angle.x, 0, 180);
        ImGui::SliderFloat("angleY", &angle.y, 0, 360);
        ImGui::SliderFloat("angleZ", &angle.z, 0, 360);
        ImGui::SliderFloat2("zNearFar", &zNearFar.x, -10000, 10000);
        ImGui::SliderFloat("eyePos.x", &eyePos.x, -1000, 1500);
        ImGui::SliderFloat("eyePos.y", &eyePos.y, -1000, 1000);
        ImGui::SliderFloat("eyePos.z", &eyePos.z, 0, 10000);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers( window );

        // Poll for and process events
        glfwPollEvents( );
    }
    // Loop until the user closes the window
    while( (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(window) == 0) );

    // Cleanup
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate( );

    return 0;
}
