//
// Created by paul patault on 21/11/2019.
//

// Include standard headers

#include "Window.h"

GLFWwindow* initWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // Initialize the library
    if ( !glfwInit( ) )
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
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
        exit(-1);
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    //gère le transparence
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    std::cout << "Version == " << glGetString(GL_VERSION) << std::endl;

    // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Couleur de fond := blanc
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


    /////// FIN INIT CONTEXT ET FENETRE ///////

    return window;
}