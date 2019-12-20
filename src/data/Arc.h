//
// Created by paul patault on 20/12/2019.
//

#ifndef MAIN_ARC_H
#define MAIN_ARC_H

#include "LoadData.h"
#include "includes/constants.h"
#include <glm/glm.hpp>
#include <vector>

namespace data {

    class Arc {
    private:
        LoadData *_myData;
        int _teamNumber;
    public:
        Arc(int teamNumber, LoadData* data);
        ~Arc();
        std::vector<glm::vec3> makeArcs(std::vector<glm::vec3> cylinder);
    };

}



#endif //MAIN_ARC_H
