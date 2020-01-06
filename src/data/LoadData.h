//
// Created by paul patault on 06/11/2019.
//

#ifndef PROJETIG_LOADDATA_H
#define PROJETIG_LOADDATA_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "includes/constants.h"

namespace data {

    class LoadData {
    private:
        // match[i][j] := [equipe][jour] .{teamAtHome, teamAway, scoreAtHome, scoreAway, win}
        std::vector<std::vector<Match>> match;
        // rankPoints[i][j] := [jour][equipe] .{rang,points}
        std::vector<std::vector<DayTrip>> rankPoints;

        std::vector<std::string> NAMES = {
                "Man City", "Liverpool", "Chelsea", "Tottenham", "Arsenal", "Man United", "Wolves", "Everton",
                "Leicester", "West Ham", "Watford", "Crystal Palace", "Newcastle", "Bournemouth",
                "Burnley", "Southampton", "Brighton", "Cardiff", "Fulham", "Huddersfield"
        };

        int __getIndexByName(std::string nom) const;

        int __getRank(int team, int day) const;

        int __getPoints(int team, int day) const;

    public:
        explicit LoadData(const std::string& filePath);

        void loadMatch(const std::string& filePath);

        int getComplementaryRank(int team, int day) const;

        float getComplementaryRankNormalized(int team, int day) const;

        float getPointsNormalized(int team, int day) const;

        const char* getImagesPath(int index) const;

        static void destroy(const LoadData* pData);

    };


}


#endif //PROJETIG_LOADDATA_H
