//
// Created by paul patault on 06/11/2019.
//

#ifndef PROJETIG_LOADDATA_H
#define PROJETIG_LOADDATA_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "includes/constants.h"

namespace data {

    class LoadData {
    private:
        // rankPoints[i][j] := equipe / jour
        std::vector<std::vector<Match>> match;
        // rankPoints[i][j][k] := jour / equipe / {rang,points}
        std::vector<std::vector<DayTrip>> rankPoints;
        std::vector<float> y_Escalier(int team);
        void tabEscalier(float vertices[], vector<float>  coordCenter);
        float t_vertex_data[cst::NB_TEAMS][cst::NB_POINTS * 3];
        std::vector<std::string> teamPathPng;
        std::vector<std::string> NAMES = {
                "Man City", "Liverpool", "Chelsea", "Tottenham", "Arsenal", "Man United", "Wolves", "Everton",
                "Leicester", "West Ham", "Watford", "Crystal Palace", "Newcastle", "Bournemouth",
                "Burnley", "Southampton", "Brighton", "Cardiff", "Fulham", "Huddersfield"
        };

        int getIndexByName(std::string nom);

    public:

        LoadData(std::string filePath);
        void loadMatch(std::string filePath);
        std::vector<DayTrip> getTeam(unsigned int team);
        int getRank(int team, int day);
        int getComplementaryRank(int team, int day);
        float getComplementaryRankNormalized(int team, int day);
        int getPoints(int team, int day);
        float getPointsNormalized(int team, int day);

        std::vector<Match> getMatchs(int team);

        int getAdversaire(int team, int day);
        std::string getImagesPath(int index);
        void addPathToTab(std::string imagesPath);
        void initVertexDataD1();
        float getVertexDataValue(int i, int j);


    };


}


#endif //PROJETIG_LOADDATA_H
