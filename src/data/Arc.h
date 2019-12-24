//
// Created by paul patault on 20/12/2019.
//

#ifndef MAIN_ARC_H
#define MAIN_ARC_H

#include "LoadData.h"
#include "Cylinder.h"
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
        std::vector<std::vector<glm::vec3>> makeArcs(std::vector<glm::vec3> cylinder, std::vector<data::Cylinder> v_cyl);
    };

}



#endif //MAIN_ARC_H
