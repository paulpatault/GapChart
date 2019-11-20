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


class LoadData {
private:
    // rankPoints[i][j][k] := jour / equipe / {rang,points}
    vector<vector<vector<int>>> match;
    vector<vector<vector<int>>> rankPoints;
    const int NUMBER_OF_TEAMS = 20;
    const int NUMBER_OF_DAYS = 38;
    const int NUMBER_OF_POINTS_MAX = 98;
    vector<string> teamPathPng;

public:
    LoadData(string filePath);
    int getRank(int team, int day);
    int getComplementaryRank(int team, int day);
    float getComplementaryRankNormalized(int team, int day);
    int getPoints(int team, int day);
    float getPointsNormalized(int team, int day);
    int cardDays();
    int cardTeams();
    int getMatch(int team, int day);
    string getImagesPath(int index);
    void addPathToTab(string imagesPath);
    enum nameTeam {
        Man_City = 0, Liverpool = 1, Chelsea = 3, Tottenham = 4, Arsenal = 5, Man_United = 6, Wolves = 7, Everton = 8,
        Leicester = 9, West_Ham = 10, Watford = 11, Crystal_Palace = 12, Newcastle = 13, Bournemouth = 14,
        Burnley = 15, Southampton = 16, Brighton = 17, Cardiff = 18, Fulham = 19, Huddersfield = 20
    };
};


#endif //PROJETIG_LOADDATA_H
