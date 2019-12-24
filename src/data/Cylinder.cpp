//
// Created by paul patault on 16/12/2019.
//

#include "Cylinder.h"

namespace data {

    /**
     * constructor pour la classe cylinder
     * @param teamNumber, numéro (dans [0, 20]) de l'équipe associée a ce cylindre
     * @param data, instance de la classe loadData
     */
    Cylinder::Cylinder(int teamNumber, LoadData *data)
    {
        _teamNumber = teamNumber;
        _myData = data;
    }

    /**
     * fabrique la face arrière "plate" du cylindre
     * @param front, true si l'équipe est selectionnée, false sinon
     *               permet de mettre le cylindre au premier plan
     * @return vector des points qui décrivent les triangles constituant la backFace
     */
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
                decale = cst::DELTA_MID;
            if( day % 2 == 0 ) // new bout rec
            {
                complementaire = _myData->getComplementaryRankNormalized(_teamNumber, day/2);
                points = _myData->getPointsNormalized(_teamNumber, day/2);
                y_res = (points + complementaire) * cst::SCREEN_HEIGHT / 2.2;

                // TopLeft
                topLeft.x = cst::X_AT_0 + day * 2 * cst::DELTA_X + decale;
                topLeft.y = y_res;
                topLeft.z = 0;
                // BotLeft
                botLeft.x = topLeft.x ;
                botLeft.y = topLeft.y - cst::THICKNESS;
                botLeft.z = 0;
                // TopRight
                topRight.x = topLeft.x + 2 * cst::DELTA_X;
                topRight.y = topLeft.y ;
                topRight.z = 0;
                // BotRight
                botRight.x = topLeft.x + 2 * cst::DELTA_X;
                botRight.y = topLeft.y - cst::THICKNESS;
                botRight.z = 0;

                if(front) {
                    topLeft.z += cst::FRONT_Z;
                    botLeft.z += cst::FRONT_Z;
                    topRight.z += cst::FRONT_Z;
                    botRight.z += cst::FRONT_Z;
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

                yByDay.push_back((topLeft.y - botLeft.y) / 2) ;
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

                topMid.x = topRight.x + cst::DELTA_X;
                topMid.y = moy_y;
                topMid.z = delta_y < 0 ? cst::DELTA_Z : - cst::DELTA_Z ;


                botMid.x = botRight.x + cst::DELTA_X;
                botMid.y = moy_y - cst::THICKNESS;
                botMid.z = delta_y < 0 ? cst::DELTA_Z : - cst::DELTA_Z ;

                if(delta_y == 0) {
                    topMid.z = 0;
                    botMid.z = 0;
                }

                if(front){
                    topMid.z += cst::FRONT_Z;
                    botMid.z += cst::FRONT_Z;
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
                s_topLeft.x = cst::X_AT_0 + (float)(day + 1) * 2 * cst::DELTA_X + decale;
                s_topLeft.y = s_y_res;
                s_topLeft.z = 0;
                // BotLeft
                s_botLeft.x = s_topLeft.x ;
                s_botLeft.y = s_topLeft.y - cst::THICKNESS;
                s_botLeft.z = 0;

                if(front){
                    s_topLeft.z += cst::FRONT_Z;
                    s_botLeft.z += cst::FRONT_Z;
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

    /**
     * Fabrique les demi disques qui "fermeront" chaque bout de cylindre
     * @param backFace face arrière (plate) du demi cylindre
     * @param arc_only true si on ne veut pas remplir le disque := décris juste l'arc de cercle et non le demi disque
     *                 false sinon := on rempli le demi disque
     * @return vector des points qui décrivent les triangles constituant les demi disques
     */
    std::vector<glm::vec3> Cylinder::makeHalfCircles(std::vector<glm::vec3> backFace, bool arc_only)
    {
        std::vector<glm::vec3> halfCircle;

        float half_pi = 1.57079632679489661923132169163975144; // == (float) glm::half_pi
        float r = cst::THICKNESS / 2;
        float angle = 3.14159265358979323846264338327950288 / cst::DIV_CYLINDER; // == (float) glm::pi

        int index_mid_add = 348;
        int index_end_add = 666;

        std::vector<glm::vec3> arcs;

        for(int i = 0; i < backFace.size(); i += 6)
        {
            float theta = half_pi;
            std::vector<glm::vec3> arc;
            std::vector<glm::vec3> arc_added;
            glm::vec3 point;
            glm::vec3 centre;
            glm::vec3 centre_added;
            centre.x = backFace[i].x;
            centre.y = backFace[i].y - r;
            centre.z = backFace[i].z;

            for(int j = 0; j < cst::DIV_CYLINDER + 1; j++)  /// ARC
            {
                /// ajout de demi disque au milieu gauche (== moitié inf)
                if(i == index_mid_add)
                {
                    centre_added.x = backFace[i].x - (cst::DELTA_MID + 2 * cst::DELTA_X);
                    centre_added.y = backFace[i].y - r;
                    centre_added.z = backFace[i].z;
                    point.x = centre_added.x;
                    point.y = centre_added.y + r * glm::sin(theta);
                    point.z = centre_added.z + r * glm::cos(theta);
                    arc_added.push_back(point);
                }

                point.x = centre.x;
                point.y = centre.y + r * glm::sin(theta);
                point.z = centre.z + r * glm::cos(theta);

                arc.push_back(point);

                /// ajout de demi disque a la fin
                if(i == index_end_add)
                {
                    centre_added.x = backFace[i].x + 2 * cst::DELTA_X;
                    centre_added.y = backFace[i].y - r;
                    centre_added.z = backFace[i].z;
                    point.x = centre_added.x;
                    point.y = centre_added.y + r * glm::sin(theta);
                    point.z = centre_added.z + r * glm::cos(theta);
                    arc_added.push_back(point);
                }

                theta -= angle; // descend le cercle trigo par la droite
            }

            /// ajout de demi disque au milieu gauche (== moitié inf)
            if(i == index_mid_add)
            {
                for(int j = 0; j < cst::DIV_CYLINDER; j++)
                {
                    halfCircle.push_back(arc_added[j]);
                    halfCircle.push_back(centre_added);
                    halfCircle.push_back(arc_added[j + 1]);
                    arcs.push_back(arc_added[j]);
                }
                if(arc_only) arcs.push_back(arc_added[cst::DIV_CYLINDER]);
            }

            for(int j = 0; j < cst::DIV_CYLINDER; j++)
            {
                halfCircle.push_back(arc[j]);
                halfCircle.push_back(centre);
                halfCircle.push_back(arc[j + 1]);
                arcs.push_back(arc[j]);
            }
            if(arc_only) arcs.push_back(arc[cst::DIV_CYLINDER]);

            /// ajout de demi disque a la fin
            if(i == index_end_add)
            {
                for(int j = 0; j < cst::DIV_CYLINDER; j++)
                {
                    halfCircle.push_back(arc_added[j]);
                    halfCircle.push_back(centre_added);
                    halfCircle.push_back(arc_added[j + 1]);
                    arcs.push_back(arc_added[j]);
                }
                if(arc_only) arcs.push_back(arc_added[cst::DIV_CYLINDER]);
            }
        }

        if(arc_only) return arcs;

        return halfCircle;
    }

    /**
     * Fabrique les cylindres creux entre deux demi disques
     * @param backFace face arrière (plate) du demi cylindre
     * @return vector des points qui décrivent les cylindres creux
     */
    std::vector<glm::vec3> Cylinder::makeLinkCircles(std::vector<glm::vec3> backFace)
    {



        std::vector<glm::vec3> linkCircles;
        std::vector<glm::vec3> arcs = makeHalfCircles(backFace, true);
        std::vector<glm::vec3> tubes;


        /// SWAP ///

        for(int i = 0; i < 8; i++){
            swap(arcs[520 + i], arcs[520 + 8 + i]);
        }

        for(int i = 504; i < arcs.size(); i++){
            arcs[i] = arcs[i+1];
        }

        int nbr = arcs.size() / (cst::DIV_CYLINDER)  ;
        int total = 0;

        int mid = 65; // on veut 63
        // 58 _ 56
        for(int i = 0; i < nbr - 1; i++) // each arc
        {
            if(not (mid * cst::DIV_CYLINDER <= total and total <= (mid + 10) * cst::DIV_CYLINDER))
            {
                for(int div = total ; div < total + cst::DIV_CYLINDER; div++)
                {
                    glm::vec3 topLeft  = arcs[div + 0];
                    glm::vec3 botLeft  = arcs[div + 1];
                    glm::vec3 topRight = arcs[div + cst::DIV_CYLINDER + 0];
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
            } else {
                std::cout << i << ".x = "<< arcs[total + 0].x << " , total = " << total << std::endl;
                // inversement 66 et 65 => 520 et 528

            }
            total += cst::DIV_CYLINDER;

        }

        return tubes;
    }

    /**
     * Ajoute le vector end a la suite de begin
     * @param begin vector a compléter
     * @param end vector qui complete
     * @return le total
     */
    std::vector<glm::vec3> pusher(std::vector<glm::vec3> begin, std::vector<glm::vec3> end)
    {
        std::vector<glm::vec3> res = begin;
        for(auto point : end)
        {
            res.push_back(point);
        }
        return res;
    }

    /**
     * Combine backFace + demi disques + cylindres creux
     * @param front true si l'équipe est selectionnée, false sinon
     *               permet de mettre le cylindre au premier plan
     * @return la combinaison
     */
    std::vector<glm::vec3> Cylinder::makeCombinedCylinder(bool front)
    {
        std::vector<glm::vec3> backFace = makeBackFace(front); // backFace.size() = 672
        std::vector<glm::vec3> halfDisk = makeHalfCircles(backFace, false); // halfCyl.size() = 3360
        std::vector<glm::vec3> link = makeLinkCircles(backFace); //link.size() = 6480

        std::vector<glm::vec3> back_and_half = pusher(backFace, halfDisk);
        std::vector<glm::vec3> combined = pusher(back_and_half, link);

        return combined;
    }

    /**
     * Fabrique le vector des normals pour chaque triangle du cylindre
     * @param cylinder vector qui comprend backFace + demi disques + cylindres creux
     * @return vector des normals associées a chaque triangle
     */
    std::vector<float> Cylinder::makeNormals(std::vector<float> cylinder) {

        std::vector<float> normals;
        glm::vec3 normal;

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

            if (i < 0) { // < 224){  // Nombre de triangles pour la backface -> signe des normals différent
                glm::vec3 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);

                normal = glm::cross(C - A, B - A);
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

                normal = glm::cross(B - A, C - A);
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

        ///std::cout << normals.size() / 3 << std::endl;
            // == 10'512

        return normals;
    }

    /**
     * default destructor, non implementé
     */
    Cylinder::~Cylinder() = default;

}



