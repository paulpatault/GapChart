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

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class LoadData {
private:
    struct Match{
        string teamAtHome;
        string teamAway;
        int scoreAtHome;
        int scoreAway;
        int win; // -1 defaite, 0 égalité, 1 victoire
    };
    // rankPoints[i][j] := equipe / jour
    vector<vector<Match>> match;
    // rankPoints[i][j][k] := jour / equipe / {rang,points}
    vector<vector<vector<int>>> rankPoints;
    const int NUMBER_OF_TEAMS = 20;
    const int NUMBER_OF_DAYS = 38;
    const int NUMBER_OF_POINTS_MAX = 98;
    std::vector<float> y_Escalier(int team, float SCREEN_HEIGHT);
    void tabEscalier(float vertices[], const int NUMBER_OF_POINTS, const float epaisseur, const float dx, vector<float>  coordCenter);
    float t_vertex_data[20][(4 * (38 + 1)) * 3];
    vector<string> teamPathPng;
    vector<string> NAMES = {
        "Man City", "Liverpool", "Chelsea", "Tottenham", "Arsenal", "Man United", "Wolves", "Everton",
        "Leicester", "West Ham", "Watford", "Crystal Palace", "Newcastle", "Bournemouth",
        "Burnley", "Southampton", "Brighton", "Cardiff", "Fulham", "Huddersfield"
    };

    int getIndexByName(string nom);

public:
    LoadData(string filePath);
    void loadMatch(string filePath);
    int getRank(int team, int day);
    int getComplementaryRank(int team, int day);
    float getComplementaryRankNormalized(int team, int day);
    int getPoints(int team, int day);
    float getPointsNormalized(int team, int day);
    int cardDays();
    int cardTeams();
    int getAdversaire(int team, int day);
    string getImagesPath(int index);
    void addPathToTab(string imagesPath);
    void initVertexDataD1(float a, float b, float c);
    float getVertexDataValue(int i, int j);


};


#endif //PROJETIG_LOADDATA_H
