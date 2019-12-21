//
// Created by paul patault on 16/12/2019.
//

#include "c_ImGui.h"


namespace screen {

    /**
     * Initialisaiton du contexte ImGui
     * @param window fenetre sur laquel le contexte est initialisé
     */
    void c_ImGui::init(GLFWwindow *window)
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window,true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    /**
     * Le contexte ImGui reste dans la fenetre
     */
    void c_ImGui::loop()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /**
     * Actualise les couleurs possiblement changées par le contexte ImGui
     * @param colors, tableau des vec3 de couleurs pour les cylindres
     */
    void c_ImGui::maj(glm::vec3 colors[])
    {
        // ImGui Edit (màj)
        ImGui::ColorEdit3("top1", (float*)&colors[0]);
        ImGui::ColorEdit3("top", (float*)&colors[1]);
        ImGui::ColorEdit3("top_mid", (float*)&colors[2]);
        ImGui::ColorEdit3("mid", (float*)&colors[3]);
        ImGui::ColorEdit3("bot_mid", (float*)&colors[4]);
        ImGui::ColorEdit3("bot", (float*)&colors[5]);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    /**
     * Fermeture du contexte
     */
    void c_ImGui::terminate() {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

}

