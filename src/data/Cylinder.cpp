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
    Cylinder::Cylinder(int teamNumber, const LoadData* data)
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

        for(unsigned long day = 0; day < cst::NB_DAYS * 2 - 1; day++)
        {
            if(day == 38)
                decale = cst::DELTA_MID;
            if( day % 2 == 0 ) // new bout rec
            {
                complementaire = _myData->getComplementaryRankNormalized(_teamNumber, day / 2);
                points = _myData->getPointsNormalized(_teamNumber, day / 2);
                y_res = (points + complementaire) * cst::SCREEN_HEIGHT / 2.2;

                // TopLeft
                topLeft.x = cst::X_AT_0 + (float)day * 2 * cst::DELTA_X + decale;
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

                /// TopLeft . BotLeft . BotRight => triangle bas gauche
                backFace.push_back(topLeft);
                backFace.push_back(botLeft);
                backFace.push_back(botRight);

                /// TopLeft . TopRight . BotRight => triangle haut droit
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
                topMid.z = delta_y > 0 ? cst::DELTA_Z : - cst::DELTA_Z ;

                botMid.x = botRight.x + cst::DELTA_X;
                botMid.y = moy_y - cst::THICKNESS;
                botMid.z = delta_y > 0 ? cst::DELTA_Z : - cst::DELTA_Z ;

                if(delta_y == 0) {
                    topMid.z = 0;
                    botMid.z = 0;
                }

                if(front){
                    topMid.z += cst::FRONT_Z;
                    botMid.z += cst::FRONT_Z;
                }


                 ///////////////////////////////
                 ///   Premier demi ecart    ///
                 ///////////////////////////////
                {
                    ///TopRight . BotRight . BotMid => triangle bas gauche
                    backFace.push_back(topRight);
                    backFace.push_back(botRight);
                    backFace.push_back(botMid);

                    ///TopRight . TopMid . BotMid => triangle haut droit
                    backFace.push_back(topRight);
                    backFace.push_back(topMid);
                    backFace.push_back(botMid);
                }


                //////////////////////////////
                ///   Second demi ecart    ///
                //////////////////////////////

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
                    /// TopMid . BotMid . s_BotLeft => triangle bas gauche
                    backFace.push_back(topMid);
                    backFace.push_back(botMid);
                    backFace.push_back(s_botLeft);

                    /// TopMid . s_TopLeft . s_BotLeft  => triangle haut droit
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
    std::vector<glm::vec3> Cylinder::makeHalfCircles(const std::vector<glm::vec3>& backFace, bool arc_only)
    {
        std::vector<glm::vec3> halfCircle;

        float half_pi = 1.57079632679489661923132169163975144; // == (float) glm::half_pi
        float r = cst::THICKNESS / 2;
        float angle = 3.14159265358979323846264338327950288 / cst::DIV_CYLINDER; // == (float) glm::pi
        float theta;

        int index_mid_add = 348;
        int index_end_add = 666;

        std::vector<glm::vec3> arcs;

        for(unsigned long i = 0; i < backFace.size(); i += 6)
        {
            std::vector<glm::vec3> arc;
            glm::vec3 point;
            glm::vec3 centre;

            glm::vec3 centre_added;
            std::vector<glm::vec3> arc_added;

            theta = half_pi;
            centre.x = backFace[i].x;
            centre.y = backFace[i].y - r;
            centre.z = backFace[i].z;

            for(int j = 0; j < cst::DIV_CYLINDER + 1; j++)  /// ARC
            {
                /// ajout de demi disque au milieu gauche (== moitié inf)
                if(i == index_mid_add)
                {
                    glm::vec3 point_added;
                    centre_added.x = centre.x - (cst::DELTA_MID + 2 * cst::DELTA_X);
                    centre_added.y = centre.y;
                    centre_added.z = centre.z;

                    point_added.x = centre_added.x;
                    point_added.y = centre_added.y + r * glm::sin(theta);
                    point_added.z = centre_added.z + r * glm::cos(theta);
                    arc_added.push_back(point_added);
                }

                point.x = centre.x;
                point.y = centre.y + r * glm::sin(theta);
                point.z = centre.z + r * glm::cos(theta);

                arc.push_back(point);

                /// ajout de demi disque a la fin
                if(i == index_end_add)
                {
                    glm::vec3 point_added;
                    centre_added.x = centre.x + 2 * cst::DELTA_X;
                    centre_added.y = centre.y;
                    centre_added.z = centre.z;

                    point_added.x = centre_added.x;
                    point_added.y = centre_added.y + r * glm::sin(theta);
                    point_added.z = centre_added.z + r * glm::cos(theta);
                    arc_added.push_back(point_added);
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

    std::vector<glm::vec3> p_swap(std::vector<glm::vec3> arcs, int index)
    {
        for(int i = index; i < index + cst::DIV_CYLINDER + 1; i++)
        {
            std::swap(arcs[i],arcs[i + cst::DIV_CYLINDER + 1]);
        }

        return arcs;
    }

    /**
     * Fabrique les cylindres creux entre deux demi disques
     * @param backFace face arrière (plate) du demi cylindre
     * @return vector des points qui décrivent les cylindres creux
     */
    std::vector<glm::vec3> Cylinder::makeLinkCircles(const std::vector<glm::vec3>& backFace)
    {
        std::vector<glm::vec3> linkCircles;
        std::vector<glm::vec3> arcs = makeHalfCircles(backFace, true);
        std::vector<glm::vec3> tubes;

        int nbr = arcs.size() / (cst::DIV_CYLINDER + 1);
        int mid = nbr/2;
        int total = 0;

        arcs = p_swap(arcs, mid * (cst::DIV_CYLINDER + 1) );

        for(unsigned long i = 0; i < nbr - 1; i++)
        {
            //if(not (mid * (cst::DIV_CYLINDER + 1) <= total and total < (mid + 1) * (cst::DIV_CYLINDER + 1)))
            if(total < mid * (cst::DIV_CYLINDER + 1) or (mid + 1) * (cst::DIV_CYLINDER + 1) <= total)
            {
                for(int div = total ; div < total + cst::DIV_CYLINDER + 1; div++) /// +1 ou ø
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
                    tubes.push_back(botRight);
                }
            }
            total += cst::DIV_CYLINDER + 1;
        }
        return tubes;
    }

    /**
     * Ajoute le vector end a la suite de begin
     * @param begin vector a compléter
     * @param end vector qui complete
     * @return le total
     */
    std::vector<glm::vec3> pusher(const std::vector<glm::vec3>& begin, const std::vector<glm::vec3>& end)
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
    std::vector<float> Cylinder::makeCombinedCylinder(bool front)
    {
        std::vector<glm::vec3> backFace = makeBackFace(front); // backFace.size() = 672
        std::vector<glm::vec3> halfDisk = makeHalfCircles(backFace, false); // halfCyl.size() = 3360
        std::vector<glm::vec3> link = makeLinkCircles(backFace); //link.size() = 6480

        std::vector<glm::vec3> back_and_half = pusher(backFace, halfDisk);
        std::vector<glm::vec3> combined = pusher(back_and_half, link);

        std::vector<float> cylinder;
        for(auto & point : combined)
        {
            cylinder.push_back(point.x);
            cylinder.push_back(point.y);
            cylinder.push_back(point.z);
        }

        return cylinder;
    }

    /**
     * Fabrique le vector des normals pour chaque triangle du cylindre
     * @param cylinder vector qui comprend backFace + demi disques + cylindres creux
     * @return vector des normals associées a chaque triangle
     */
    std::vector<float> Cylinder::makeNormals(const std::vector<float>& cylinder) {

        std::vector<float> normals;
        glm::vec3 normal;
        //1 triangle = 9 coordonnées
        for (unsigned long i = 0; i < cylinder.size() / 9; i++) {
            float x1 = cylinder[(9 * i) + 0],
                y1 = cylinder[(9 * i) + 1],
                z1 = cylinder[(9 * i) + 2];

            float x2 = cylinder[(9 * i) + 3],
                y2 = cylinder[(9 * i) + 4],
                z2 = cylinder[(9 * i) + 5];

            float x3 = cylinder[(9 * i) + 6],
                y3 = cylinder[(9 * i) + 7],
                z3 = cylinder[(9 * i) + 8];

            if (i < 224)  // < 224){  // Nombre de triangles pour la backface -> signe des normals différent
            {
                glm::vec3 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);

                glm::vec3 AC = C - A;
                glm::vec3 AB = B - A;
                glm::vec3 BC = C - B;
                glm::vec3 BA = -AB;
                glm::vec3 CA = -AC;
                glm::vec3 CB = -BC;

                normal = glm::cross(AC, AB);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(BA, BC);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(CB, CA);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
            } else {
                glm::vec3 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);

                glm::vec3 AC = C - A;
                glm::vec3 AB = B - A;
                glm::vec3 BC = C - B;
                glm::vec3 BA = -AB;
                glm::vec3 CA = -AC;
                glm::vec3 CB = -BC;

                normal = glm::cross(AB, AC);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(BC, BA);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

                normal = glm::cross(CA, CB);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
            }
        }
        return normals;
    }

    /**
     * default destructor, non implementé
     */
    Cylinder::~Cylinder() = default;

}



