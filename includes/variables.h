//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_VARIABLES_CPP
#define MAIN_VARIABLES_CPP

#include <glm/glm.hpp>
#include <vector>
#include "src/data/VBO.h"

namespace var {

    /// Pour la séléction d'équipe à mettre au premier plan
    Selection selector = {-1, false};

    /// vector des 20 VBO (1 par cylindre)
    std::vector<data::VBO> t_VBO;
    /// vector des 20 VBO à "t = 0" (:= c'est une sauvegarde)
    std::vector<data::VBO> t_VBO_0;

    /// tableau des couleurs qui seront assignées à chaque cylindre
    glm::vec3 colors[] = {
            /* // couleurs plus "pastel" comme dans le sujet du projet
            glm::vec3(92.f/255.f,133.f/255.f,209.f/255.f),    // top1
            glm::vec3(142.f/255.f,217.f/255.f,228.f/255.f),   // top
            glm::vec3(234.f/255.f,235.f/255.f,89.f/255.f),   // top_mid
            glm::vec3(213.f/255.f,213.f/255.f,213.f/255.f),  // mid
            glm::vec3(168.f/255.f,168.f/255.f,168.f/255.f),  // bot_mid
            glm::vec3(233.f/255.f,139.f/255.f,139.f/255.f)   // bot
            */
            glm::vec3(0.f, 72.f / 255.f, 204.f / 255.f),             // top1
            glm::vec3(98.f / 255.f, 214.f / 255.f, 230.f / 255.f),   // top
            glm::vec3(236.f / 255.f, 238.f / 255.f, 26.f / 255.f),   // top_mid
            glm::vec3(194.f / 255.f, 194.f / 255.f, 194.f / 255.f),  // mid
            glm::vec3(140.f / 255.f, 140.f / 255.f, 140.f / 255.f),  // bot_mid
            glm::vec3(240.f / 255.f, 35.f / 255.f, 35.f / 255.f)     // bot
    };

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // dupl matrix
    glm::mat4 viewMatrix;
    glm::mat4 rotationMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 projectionMatrix;

}


#endif //MAIN_VARIABLES_CPP
