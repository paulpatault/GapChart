//
// Created by paul patault on 21/12/2019.
//

#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#include <vector>
#include "src/data/VBO.h"
#include "src/data/Cylinder.h"
#include "src/data/Arc.h"

inline std::vector<data::VBO> makeVBO(data::LoadData myData)
{
    std::vector<data::VBO> res;

    for(int team = 0; team < cst::NB_TEAMS; team++)
    {
        data::Cylinder cyl(team, &myData);

        std::vector<glm::vec3> combined = cyl.makeCombinedCylinder(false);

        std::vector<float> cylinder;
        for(int i = 0; i < combined.size(); i++)
        {
            cylinder.push_back(combined[i].x);
            cylinder.push_back(combined[i].y);
            cylinder.push_back(combined[i].z);
        }

        std::vector<float> normals = cyl.makeNormals(cylinder);
        data::VBO m_VBO( &myData , cylinder , normals);

        res.push_back(m_VBO);
    }

    return res;
}

inline std::vector<data::VBO> updateVBO(data::LoadData myData, std::vector<data::VBO> t_VBO_0, int selected)
{
    if(selected == -1)
    {
        return t_VBO_0;
    }

    std::vector<data::VBO> res;

    for(int team = 0; team < cst::NB_TEAMS; team++)
    {
        data::Cylinder cyl(team, &myData);
        data::Arc arc(team, &myData);

        std::vector<glm::vec3> back = cyl.makeBackFace(false);
        std::vector<glm::vec3> v3_cylinder = cyl.makeHalfCircles(back, false);
        std::vector<glm::vec3> arcs = arc.makeArcs(v3_cylinder);

        bool front = false;
        if(team == selected)
            front = true;

        std::vector<glm::vec3> combined = cyl.makeCombinedCylinder(front);


        std::vector<float> cylinder;
        for(int i = 0; i < combined.size(); i++)
        {
            cylinder.push_back(combined[i].x);
            cylinder.push_back(combined[i].y);
            cylinder.push_back(combined[i].z);
        }

        std::vector<float> normals = cyl.makeNormals(cylinder);
        data::VBO m_VBO( &myData , cylinder , normals);

        res.push_back(m_VBO);
    }

    return res;
}


#endif //MAIN_UTILS_H
