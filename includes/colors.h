//
// Created by paul patault on 17/12/2019.
//

#ifndef MAIN_COLORS_H
#define MAIN_COLORS_H

#include <glm/glm.hpp>

namespace rgb{

    /**
     *   glm::vec3 colors[]
     *   tableau des couleurs qui seront assignées a chaque cylindre
     **/
    glm::vec3 colors[] = {
            /* // pastel
            glm::vec4(92.f/255.f,133.f/255.f,209.f/255.f,1.f),            // top1
            glm::vec4(142.f/255.f,217.f/255.f,228.f/255.f,1.f),    // top
            glm::vec4 (234.f/255.f,235.f/255.f,89.f/255.f,1.f),   // top_mid
            glm::vec4 (213.f/255.f,213.f/255.f,213.f/255.f,1.f),  // mid
            glm::vec4 (168.f/255.f,168.f/255.f,168.f/255.f,1.f),  // bot_mid
            glm::vec4 (233.f/255.f,139.f/255.f,139.f/255.f,1.f)     // bot
            */
            glm::vec3 (0.f,72.f/255.f,204.f/255.f),            // top1
            glm::vec3 (98.f/255.f,214.f/255.f,230.f/255.f),    // top
            glm::vec3 (236.f/255.f,238.f/255.f,26.f/255.f),   // top_mid
            glm::vec3 (194.f/255.f,194.f/255.f,194.f/255.f),  // mid
            glm::vec3 (140.f/255.f,140.f/255.f,140.f/255.f),  // bot_mid
            glm::vec3 (240.f/255.f,35.f/255.f,35.f/255.f)     // bot
    };
}



#endif //MAIN_COLORS_H
