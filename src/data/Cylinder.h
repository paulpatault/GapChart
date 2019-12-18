//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_CYLINDER_H
#define MAIN_CYLINDER_H

#include <vector>
#include "LoadData.h"
#include "includes/constants.h"
#include <glm/glm.hpp>


namespace data {

    class Cylinder {
    private:
        LoadData *_myData;
        int _teamNumber;

    public:
        Cylinder(int teamNumber, LoadData* data);
        ~Cylinder();
        std::vector<glm::vec3> makeBottom();
        void makeCylinder();
        void makeNormals();



    };
}



#endif //MAIN_CYLINDER_H
