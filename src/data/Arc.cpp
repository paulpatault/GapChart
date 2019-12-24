//
// Created by paul patault on 20/12/2019.
//

#include "Arc.h"

namespace data {
    Arc::Arc(int teamNumber, LoadData *data)
    {
        _teamNumber = teamNumber;
        _myData = data;
    }

    Arc::~Arc() = default;

    std::vector<std::vector<glm::vec3>> Arc::makeArcs(std::vector<glm::vec3> cylinder, std::vector<data::Cylinder> v_cyl)
    {

        std::vector<glm::vec3> arc;
        std::vector<std::vector<glm::vec3>> arcs;
        glm::vec3 point,
                  point2,
                  centre,
                  point_ref;

        std::vector<Match> t_matchs = _myData->getMatchs(_teamNumber);
        int adv, y_adv, nbPoints = 30;
        int index_cyl = 0;

        float half_pi = 1.57079632679489661923132169163975144; // == (float) glm::half_pi
        float angle = 3.14159265358979323846264338327950288 / nbPoints;
        float r, theta;

        for(int day = 0; day < cst::NB_DAYS; day++)
        {
            index_cyl = day * 6 * 3; // 6 := nb cyl par day  |  3 := nb points par triangle

            point_ref = cylinder[index_cyl];
            point_ref.y -= cst::THICKNESS / 2;

            Match match = t_matchs[day];

            adv = _myData->getAdversaire(_teamNumber, day);
            y_adv = v_cyl[adv].yByDay[day];

            r = glm::abs(point_ref.y - y_adv) / 2;

            theta = half_pi;

            centre.x = point_ref.x;
            centre.y = point_ref.y > y_adv ? point_ref.y - r : y_adv - r;
            centre.z = point_ref.z;

            for(int points = 0; points < nbPoints; points++)  /// ARC
            {
                point.x = centre.x;
                point.y = centre.y + r * glm::sin(theta);
                point.z = centre.z + r * glm::cos(theta);

                theta -= angle;

                arc.push_back(point);

                point2.x = point.x + 5;
                point2.y = point.y;
                point2.z = point.z;

                arc.push_back(point2);
            }
            arcs.push_back(arc);
        }
        return arcs;
    }
}