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

    std::vector<glm::vec3> Cylinder::makeBackFace(bool front)
    {
        float complementaire,
                points,
                s_complementaire, // s pour suivant
                s_points,
                y_res,
                s_y_res,
                decale = 0;

        glm::vec3 topLeft,
                botLeft,
                topRight,
                botRight;

        std::vector<glm::vec3> backFace; // tableau de triangle (non strip)

        for(int day = 0; day < cst::NB_DAYS * 2 - 1; day++)
        {
            if(day == 38)
                decale = 50;
            if( day % 2 == 0 ) // new bout rec
            {
                complementaire = _myData->getComplementaryRankNormalized(_teamNumber, day/2);
                points = _myData->getPointsNormalized(_teamNumber, day/2);
                y_res = (points + complementaire) * cst::SCREEN_HEIGHT / 2.2;

                // TopLeft
                topLeft.x = cst::x0 + day * 2 * cst::dx + decale;
                topLeft.y = y_res;
                topLeft.z = 0;
                // BotLeft
                botLeft.x = topLeft.x ;
                botLeft.y = topLeft.y - cst::THICKNESS;
                botLeft.z = 0;
                // TopRight
                topRight.x = topLeft.x + 2 * cst::dx;
                topRight.y = topLeft.y ;
                topRight.z = 0;
                // BotRight
                botRight.x = topLeft.x + 2 * cst::dx;
                botRight.y = topLeft.y - cst::THICKNESS;
                botRight.z = 0;

                if(front) {
                    topLeft.z += cst::add_z;
                    botLeft.z += cst::add_z;
                    topRight.z += cst::add_z;
                    botRight.z += cst::add_z;
                }

                /**
                * TopLeft . BotLeft . BotRight => triangle bas gauche
                **/
                backFace.push_back(topLeft);
                backFace.push_back(botLeft);
                backFace.push_back(botRight);

                /**
                 * TopLeft . TopRight . BotRight => triangle haut droit
                **/
                backFace.push_back(topLeft);
                backFace.push_back(topRight);
                backFace.push_back(botRight);
            }
            else // end bout rec => new entre deux
            {

                // regarde le jour d'après
                s_complementaire = _myData->getComplementaryRankNormalized(_teamNumber, (day + 1) / 2);
                s_points = _myData->getPointsNormalized(_teamNumber, (day + 1) / 2);
                s_y_res = (s_points + s_complementaire) * cst::SCREEN_HEIGHT / 2.2;

                float delta_y = s_y_res - y_res;
                float moy_y = (s_y_res + y_res) / 2;

                glm::vec3 topMid,
                        botMid,
                        s_topLeft,
                        s_botLeft;

                topMid.x = topRight.x + cst::dx;
                topMid.y = moy_y;
                topMid.z = delta_y < 0 ? cst::dz : - cst::dz ;


                botMid.x = botRight.x + cst::dx;
                botMid.y = moy_y - cst::THICKNESS;
                botMid.z = delta_y < 0 ? cst::dz : - cst::dz ;

                if(delta_y == 0) {
                    topMid.z = 0;
                    botMid.z = 0;
                }

                if(front){
                    topMid.z += cst::add_z;
                    botMid.z += cst::add_z;
                }

                /**
                 * ///////////////////
                 * Premier demi ecart
                 * ///////////////////
                 */

                {
                    /**
                     * TopRight . BotRight . BotMid => triangle bas gauche
                    **/
                    backFace.push_back(topRight);
                    backFace.push_back(botRight);
                    backFace.push_back(botMid);

                    /**
                     * TopRight . TopMid . BotMid => triangle haut droit
                    **/
                    backFace.push_back(topRight);
                    backFace.push_back(topMid);
                    backFace.push_back(botMid);
                }

                /**
                 * ///////////////////
                 * Second demi ecart
                 * ///////////////////
                 */

                // TopLeft
                s_topLeft.x = cst::x0 + (float)(day + 1) * 2 * cst::dx + decale;
                s_topLeft.y = s_y_res;
                s_topLeft.z = 0;
                // BotLeft
                s_botLeft.x = s_topLeft.x ;
                s_botLeft.y = s_topLeft.y - cst::THICKNESS;
                s_botLeft.z = 0;

                if(front){
                    s_topLeft.z += cst::add_z;
                    s_botLeft.z += cst::add_z;
                }

                {
                    /**
                     * TopMid . BotMid . s_BotLeft => triangle bas gauche
                    **/
                    backFace.push_back(topMid);
                    backFace.push_back(botMid);
                    backFace.push_back(s_botLeft);

                    /**
                     * TopMid . s_TopLeft . s_BotLeft  => triangle haut droit
                    **/
                    backFace.push_back(topMid);
                    backFace.push_back(s_topLeft);
                    backFace.push_back(s_botLeft);
                }
            }
        }
        return backFace;
    }

    std::vector<glm::vec3> Cylinder::makeHalfCircles(std::vector<glm::vec3> backFace, bool arc_only)
    {
        std::vector<glm::vec3> halfCircle;

        float half_pi = 1.57079632679489661923132169163975144; // == (float) glm::half_pi
        float r = cst::THICKNESS / 2;
        float angle = 3.14159265358979323846264338327950288 / cst::DIV_CYLINDER; // == (float) glm::pi

        std::vector<glm::vec3> arcs;

        for(int i = 0; i < backFace.size(); i += 6)
        {
            float theta = half_pi;
            std::vector<glm::vec3> arc;
            glm::vec3 point;
            glm::vec3 centre;
            centre.x = backFace[i].x;
            centre.y = backFace[i].y - r;
            centre.z = backFace[i].z;

            for(int j = 0; j < cst::DIV_CYLINDER + 1; j++)  /// ARC
            {
                point.x = centre.x;
                point.y = centre.y + r * glm::sin(theta);
                point.z = centre.z + r * glm::cos(theta);

                theta -= angle; // descend le cercle trigo par la droite

                arc.push_back(point);
            }

            for(int j = 0; j < cst::DIV_CYLINDER; j++)
            {
                halfCircle.push_back(arc[j]);
                halfCircle.push_back(centre);
                halfCircle.push_back(arc[j + 1]);

                arcs.push_back(arc[j]);
            }
        }

        if(arc_only) return arcs;

        return halfCircle;
    }

    std::vector<glm::vec3> Cylinder::makeLinkCircles(std::vector<glm::vec3> backFace)
    {

        std::vector<glm::vec3> linkCircles;
        std::vector<glm::vec3> arcs = makeHalfCircles(backFace, true);
        std::vector<glm::vec3> tubes;

        int nbr = arcs.size() / (cst::DIV_CYLINDER) - 1 ;
        int total = 0;
        for(int i = 0; i < nbr - 1; i++) // each arc
        {

            int div;
            if(total < 55 * cst::DIV_CYLINDER or total > 56 * cst::DIV_CYLINDER)
            {
                for(div = total ; div < total + cst::DIV_CYLINDER; div++)
                {
                    glm::vec3 topLeft = arcs[div];
                    glm::vec3 botLeft = arcs[div + 1];
                    glm::vec3 topRight = arcs[div + cst::DIV_CYLINDER];
                    glm::vec3 botRight = arcs[div + cst::DIV_CYLINDER + 1];
                    // TopLeft BotLeft BotRight
                    tubes.push_back(topLeft );
                    tubes.push_back(botLeft );
                    tubes.push_back(botRight);
                    // TopLeft TopRight BotRigth
                    tubes.push_back(topLeft );
                    tubes.push_back(topRight);
                    tubes.push_back(botRight );

                }
            }
            total += cst::DIV_CYLINDER;

        }

        return tubes;
    }

    std::vector<glm::vec3> pusher(std::vector<glm::vec3> begin, std::vector<glm::vec3> end)
    {
        for(int i = 0; i < end.size(); i++)
        {
            begin.push_back(end[i]);
        }
        return begin;
    }

    std::vector<glm::vec3> Cylinder::makeCombinedCylinder(bool front)
    {
        std::vector<glm::vec3> backFace = makeBackFace(front);

        std::vector<glm::vec3> halfCyl = makeHalfCircles(backFace, false);
        std::vector<glm::vec3> link = makeLinkCircles(backFace);

        std::vector<glm::vec3> combined = pusher(backFace, halfCyl);

        combined = pusher(combined, link);

        return combined;
        // "son message il est super et je le comprends, elle a raison"
    }

    std::vector<float> Cylinder::makeNormals(std::vector<float> cylinder) {

        std::vector<float> normals;

        //1 triangle = 9 coordonnées
        for (int i = 0; i < cylinder.size() / 9; i++) {
            float x1 = cylinder[(9 * i) + 0];
            float y1 = cylinder[(9 * i) + 1];
            float z1 = cylinder[(9 * i) + 2];

            float x2 = cylinder[(9 * i) + 3];
            float y2 = cylinder[(9 * i) + 4];
            float z2 = cylinder[(9 * i) + 5];

            float x3 = cylinder[(9 * i) + 6];
            float y3 = cylinder[(9 * i) + 7];
            float z3 = cylinder[(9 * i) + 8];

            if (i < 0){ // 224){  // Nombre de triangles pour la backface -> signe des normals différent
                glm::vec3 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);
                glm::vec3 normal = glm::cross(C - A, B - A);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(A - B, C - B);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(B - C, A - C);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
            } else {
                glm::vec3 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);
                glm::vec3 normal = glm::cross(B - A, C - A);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(C - B, A - B);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(A - C, B - C);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
            }
        }

        return normals;
    }


    Cylinder::~Cylinder() = default;

}



