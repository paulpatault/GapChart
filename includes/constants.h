//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_CONSTANTS_H
#define MAIN_CONSTANTS_H

#include "string"

namespace cst {

    const int NB_DAYS = 38;
    const int NB_TEAMS = 20;
    const int MAX_POINTS = 98;

    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 700;
    const int FSCREEN_WIDTH = 1000.f;
    const int FSCREEN_HEIGHT = 700.f;

    const int DIV_CYLINDER = 10;
    const int NB_POINTS = 4 * (38 + 1);
    const float THICKNESS = ( (float) FSCREEN_HEIGHT / 2 ) / 20;
    const float dx = (float) (SCREEN_WIDTH - 100) / NB_POINTS;
    const float dz = 1;
    const float x0 = 50;
    const float add_z = -dz*3;
}

struct DayTrip {
    int rank;
    int points;
};

struct Match {
    std::string teamAtHome;
    std::string teamAway;
    int scoreAtHome;
    int scoreAway;
    int win; // -1 defaite, 0 égalité, 1 victoire
};

#endif //MAIN_CONSTANTS_H
