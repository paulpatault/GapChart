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

    std::vector<glm::vec3> Arc::makeArcs(std::vector<glm::vec3> cylinder)
    {
        std::vector<glm::vec3> arcs;
        std::vector<Match> t_matchs = _myData->getMatchs(_teamNumber);

        int adv, y_adv, y_team, nbPoints = 30;
        int index_cyl = 0;

        float half_pi = 1.57079632679489661923132169163975144; // == (float) glm::half_pi
        float angle = 3.14159265358979323846264338327950288 / nbPoints;
        float r = 50;

        for(int day = 0; day < cst::NB_DAYS; day++)
        {
            index_cyl = day * 6 * 3; // 6 := nb cyl par day  |  3 := nb points par triangle

            glm::vec3 point_ref = cylinder[index_cyl];

            Match match = t_matchs[day];

            adv = _myData->getAdversaire(_teamNumber, day);



            float theta = half_pi;
            std::vector<glm::vec3> arc;
            glm::vec3 point;
            glm::vec3 centre;
            centre.x = point_ref.x;
            centre.y = point_ref.y - r;
            centre.z = point_ref.z;

            for(int points = 0; points < nbPoints; points++)  /// ARC
            {
                point.x = centre.x;
                point.y = centre.y + r * glm::sin(theta);
                point.z = centre.z + r * glm::cos(theta);

                theta -= angle;

                arc.push_back(point);
            }

            for(int points = 0; points < nbPoints; points++)
            {
                arcs.push_back(arc[points]);
                arcs.push_back(centre);
                arcs.push_back(arc[points + 1]);
            }

        }

        return arcs;
    }
}