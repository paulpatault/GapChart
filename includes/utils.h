//
// Created by paul patault on 21/12/2019.
//

#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#include <vector>
#include "src/data/VBO.h"
#include "src/data/Cylinder.h"


namespace utils {

    inline std::vector<data::VBO> makeVBOs(const data::LoadData* myData)
    {
        std::vector<data::VBO> res;

        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            data::Cylinder c_cylinder(team, myData);
            std::vector<float> cylinder = c_cylinder.makeCombinedCylinder(false);
            std::vector<float> normals = data::Cylinder::makeNormals(cylinder);

            res.push_back(*new data::VBO(cylinder , normals));
        }

        return res;
    }

    inline void updateVBOs(std::vector<data::VBO> &VBO, const data::LoadData* myData, Selection select)
    {
        if(select.selected == -1) {
            VBO = var::t_VBO_0;
        }
        else
        {
            VBO.clear();

            for(int team = 0; team < cst::NB_TEAMS; team++)
            {
                bool front = (team == select.selected);

                data::Cylinder c_cylinder(team, myData);

                std::vector<float> cylinder = c_cylinder.makeCombinedCylinder(front);
                std::vector<float> normals = data::Cylinder::makeNormals(cylinder);

                VBO.push_back(*new data::VBO(cylinder , normals));
            }
        }
    }

    inline void majVBOs(std::vector<data::VBO>& VBO, Selection selection, const data::LoadData* myData)
    {
        if(selection.changed){
            updateVBOs(VBO, myData, selection);
        }
    }

    inline void updateTime(float& deltaTime, float& lastFrame)
    {
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

}


#endif //MAIN_UTILS_H
