//
// Created by paul patault on 21/12/2019.
//

#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#include <vector>
#include "src/data/VBO.h"
#include "src/data/Cylinder.h"
#include "src/data/Arc.h"


namespace utils {

    inline std::vector<data::VBO> makeVBOs(data::LoadData myData)
    {
        std::vector<data::VBO> res;

        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            data::Cylinder cyl(team, &myData);

            std::vector<float> cylinder = cyl.makeCombinedCylinder(false);

            //////////
            std::vector<glm::vec3> backFace = cyl.makeBackFace(false);
            std::vector<float> f_backFace;
            for(auto & point : backFace)
            {
                f_backFace.push_back(point.x);
                f_backFace.push_back(point.y);
                f_backFace.push_back(point.z);
            }
            std::vector<float> normals1 = data::Cylinder::makeNormals(f_backFace);

            std::vector<glm::vec3> halfDisk = data::Cylinder::makeHalfCircles(backFace, false);
            std::vector<float> f_halfDisk;
            for(auto & point : backFace)
            {
                f_halfDisk.push_back(point.x);
                f_halfDisk.push_back(point.y);
                f_halfDisk.push_back(point.z);
            }
            std::vector<float> normals2 = data::Cylinder::makeNormals(f_halfDisk);

            std::vector<glm::vec3> link = data::Cylinder::makeLinkCircles(backFace);
            std::vector<float> f_link;
            for(auto & point : backFace)
            {
                f_link.push_back(point.x);
                f_link.push_back(point.y);
                f_link.push_back(point.z);
            }
            std::vector<float> normals3 = data::Cylinder::makeNormals(f_link);

            std::vector<float> normals0 = data::Cylinder::pusher2(normals1, normals2);
            normals0 = data::Cylinder::pusher2(normals0, normals3);

            //////////

            std::vector<float> normals = data::Cylinder::makeNormals(cylinder);

            vector<vector<float>> null;

            data::VBO m_VBO(&myData , cylinder , normals, null);

            res.push_back(m_VBO);
        }

        return res;
    }

    inline void updateVBOs(std::vector<data::VBO> &VBO, data::LoadData *myData, Selection select)
    {
        if(select.selected == -1)
        {
            VBO = var::t_VBO_0;
        }
        else
        {
            std::vector<data::VBO> res;
            std::vector<data::Cylinder> v_cyl;

            for(int team = 0; team < cst::NB_TEAMS; team++)
            {
                data::Cylinder cyl(team, myData);
                v_cyl.push_back(cyl);
            }

            for(int team = 0; team < cst::NB_TEAMS; team++)
            {

                std::vector<glm::vec3> back = v_cyl[team].makeBackFace(false);
                std::vector<glm::vec3> v3_cylinder = v_cyl[team].makeHalfCircles(back, false);

                bool front = false;
                if(team == select.selected){
                    front = true;
                }
                std::vector<float> cylinder = v_cyl[team].makeCombinedCylinder(front);


                std::vector<std::vector<float>> combined_arcs;
                if(select.arcs and team == select.selected)
                {
                    data::Arc arc(team, myData);
                    std::vector<std::vector<glm::vec3>> arcs = arc.makeArcs(v3_cylinder, v_cyl);
                    arcs = arc.makeArcs(v3_cylinder, v_cyl);
                    for (int day = 0; day < cst::NB_DAYS; day++)
                    {
                        std::vector<float> sous_combined_arcs;
                        for (auto &point : arcs[day])
                        {
                            sous_combined_arcs.push_back(point.x);
                            sous_combined_arcs.push_back(point.y);
                            sous_combined_arcs.push_back(point.z);
                        }
                        combined_arcs.push_back(sous_combined_arcs);
                    }
                }

                std::vector<float> normals = v_cyl[team].makeNormals(cylinder);
                data::VBO m_VBO( myData , cylinder , normals, combined_arcs);

                res.push_back(m_VBO);
            }
            VBO = res;
        }

    }

    inline void majVBOs(std::vector<data::VBO> &VBO, Selection selection, data::LoadData *myData)
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
