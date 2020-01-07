//
// Created by paul patault on 16/12/2019.
//

#include "Render.h"


namespace screen {

    /**
     * Initialise le contexte GL par le constructeur de la classe Render
     */
    Render::Render(const char* title, glm::vec4 clearColor)
    {
        // Initialize the library
        if ( !glfwInit() )
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(-1);
        }

        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

        // Create a windowed mode window and its OpenGL context
        screen = glfwCreateWindow(cst::SCREEN_WIDTH, cst::SCREEN_HEIGHT, title, nullptr, nullptr);

        if ( !screen )
        {
            glfwTerminate();
            std::cerr << "Fail link to window" << std::endl;
            exit(-1);
        }

        // Make the window's context current
        glfwMakeContextCurrent(screen );

        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            exit(-1);
        }

        // transparence
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        glEnable(GL_DEPTH_TEST);

        std::cout << "Version == " << glGetString(GL_VERSION) << std::endl;

        // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
        glfwSetInputMode(screen, GLFW_STICKY_KEYS, GL_TRUE);

        // Couleur de fond
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    }

    /**
     * Echange l'écran actuel avec le prochain
     * et gère les évenements
     */
    void Render::update() const
    {
        glfwSwapBuffers(screen);
        glfwPollEvents();
    }

    /**
     * Condition de fermeture de la fenetre := touche (echap) ou ( + q) par exemple
     */
    bool Render::shouldNotClose() const
    {
        return (glfwGetKey(screen, GLFW_KEY_ESCAPE) != GLFW_PRESS)
                    and (glfwWindowShouldClose(screen) == 0);
    }

    GLFWwindow *Render::getScreen(const Render* render)
    {
        return render->screen;
    }

}

