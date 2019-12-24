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
        std::vector<float> yByDay;

        std::vector<glm::vec3> makeBackFace(bool front);
        std::vector<glm::vec3> makeHalfCircles(const std::vector<glm::vec3>& backFace, bool arc_only);
        vector<glm::vec3> makeLinkCircles(const vector<glm::vec3>& backFace);
        std::vector<glm::vec3> makeCombinedCylinder(bool front);

        std::vector<float> makeNormals(std::vector<float> cylinder);

    };
}



#endif //MAIN_CYLINDER_H
