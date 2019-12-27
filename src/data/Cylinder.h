//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_CYLINDER_H
#define MAIN_CYLINDER_H

#include <vector>
#include <glm/glm.hpp>
#include "LoadData.h"
#include "includes/constants.h"


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
        static std::vector<glm::vec3> makeHalfCircles(const std::vector<glm::vec3>& backFace, bool arc_only);
        static vector<glm::vec3> makeLinkCircles(const vector<glm::vec3>& backFace);
        std::vector<float> makeCombinedCylinder(bool front);

        static std::vector<float> makeNormals(const std::vector<float>& cylinder);

    };
}



#endif //MAIN_CYLINDER_H
