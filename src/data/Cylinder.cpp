//
// Created by paul patault on 16/12/2019.
//

#include "Cylinder.h"

namespace data {

    Cylinder::Cylinder(int teamNumber, LoadData *data)
    {
        _teamNumber = teamNumber;
        _myData = data;
    }

    std::vector<float> decaleZ(std::vector<float>)
    {
        std::vector<float> res;

        return res;
    }

    std::vector<glm::vec3> Cylinder::makeBottom()
    {
        float complementaire,
                points,
                s_complementaire, // s pour suivant
                s_points,
                y_res,
                s_y_res;

        glm::vec3 topLeft,
                botLeft,
                topRight,
                botRight;

        std::vector<glm::vec3> backFace; // tableau de triangle (non strip)

        for(int day = 0; day < cst::NB_DAYS * 2 - 1; day++)
        {

            if( day % 2 == 0 ) // new bout rec
            {
                complementaire = _myData->getComplementaryRankNormalized(_teamNumber, day/2);
                points = _myData->getPointsNormalized(_teamNumber, day/2);
                y_res = (points + complementaire) * cst::SCREEN_HEIGHT / 2.2;

                // TopLeft
                topLeft.x = cst::x0 + day * cst::dx;
                topLeft.y = y_res;
                topLeft.z = 0;
                // BotLeft
                botLeft.x = topLeft.x ;
                botLeft.y = topLeft.y - cst::THICKNESS;
                botLeft.z = 0;
                // TopRight
                topRight.x = topLeft.x + cst::dx;
                topRight.y = topLeft.y ;
                topRight.z = 0;
                // BotRight
                botRight.x = topLeft.x + cst::dx;
                botRight.y = topLeft.y - cst::THICKNESS;
                botRight.z = 0;

                /**
                * TopLeft . BotLeft . BotRight => triangle bas gauche
                **/
                // TopLeft {x, y, z}
                backFace.push_back(topLeft);

                // BotLeft {x, y, z}
                backFace.push_back(botLeft);

                // BotRight {x, y, z}
                backFace.push_back(botRight);

                /**
                 * TopLeft . TopRight . BotRight => triangle haut droit
                **/
                // TopLeft {x, y, z}
                backFace.push_back(topLeft);

                // TopRight {x, y, z}
                backFace.push_back(topRight);

                // BotRight {x, y, z}
                backFace.push_back(botRight);
            }
            else // end bout rec => new entre deux
            {
                // TODO ajouter des pts et relier

                // regarde le jour d'après
                s_complementaire = _myData->getComplementaryRankNormalized(_teamNumber, (day + 1) / 2);
                s_points = _myData->getPointsNormalized(_teamNumber, (day + 1) / 2);
                s_y_res = (s_points + s_complementaire) * cst::SCREEN_HEIGHT / 2.2;

                float delta_y = s_y_res - y_res;

                glm::vec3 topEntre2,
                        botEntre2,
                        s_topLeft,
                        s_botLeft;

                topEntre2.x = topRight.x + cst::dx / 2;
                topEntre2.y = topRight.y + delta_y;
                topEntre2.z = delta_y > 0 ? cst::THICKNESS : -cst::THICKNESS ;

                botEntre2.x = botRight.x + cst::dx / 2;
                botEntre2.y = botRight.y + delta_y;
                botEntre2.z = delta_y > 0 ? cst::THICKNESS : -cst::THICKNESS ;


                /**
                 * ///////////////////
                 * Premier demi ecart
                 * ///////////////////
                 */

                {
                    /**
                     * TopRight . BotRight . TopEntre2 => triangle haut gauche
                    **/
                    // TopLeft {x, y, z}
                    backFace.push_back(topRight);

                    // BotLeft {x, y, z}
                    backFace.push_back(botRight);

                    // BotRight {x, y, z}
                    backFace.push_back(topEntre2);

                    /**
                     * TopEntre2 . BotRight . BotEntre2 => triangle bas droit
                    **/
                    // TopLeft {x, y, z}
                    backFace.push_back(topEntre2);

                    // BotLeft {x, y, z}
                    backFace.push_back(botRight);

                    // BotRight {x, y, z}
                    backFace.push_back(botEntre2);
                }

                /**
                 * ///////////////////
                 * Second demi ecart
                 * ///////////////////
                 */

                // TopLeft
                s_topLeft.x = cst::x0 + day * cst::dx;
                s_topLeft.y = s_y_res;
                s_topLeft.z = 0;
                // BotLeft
                s_botLeft.x = topLeft.x ;
                s_botLeft.y = topLeft.y - cst::THICKNESS;
                s_botLeft.z = 0;

                {
                    /**
                     * s_TopLeft . s_BotLeft . TopEntre2 => triangle haut droit
                    **/
                    // TopLeft {x, y, z}
                    backFace.push_back(s_topLeft);

                    // BotLeft {x, y, z}
                    backFace.push_back(s_botLeft);

                    // BotRight {x, y, z}
                    backFace.push_back(topEntre2);

                    /**
                     * TopEntre2 . BotEntre2 . s_BotLeft  => triangle bas gauche
                    **/
                    // TopLeft {x, y, z}
                    backFace.push_back(topEntre2);

                    // BotLeft {x, y, z}
                    backFace.push_back(botEntre2);

                    // BotRight {x, y, z}
                    backFace.push_back(s_botLeft);
                }


            }


        }

        return backFace;
    }

    Cylinder::~Cylinder() = default;

}



