//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_LOADDATA2_H
#define MAIN_LOADDATA2_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "headers/constants.h"

class LoadData2 {
private:
    std::vector<std::vector<DayTrip>> *v_rankPoints = new std::vector<std::vector<DayTrip>>(cst::NB_TEAMS);

public:
    //explicit LoadData2(std::string& filePath);
    explicit LoadData2(std::string& filePath);
    ~LoadData2();

    std::vector<DayTrip> getTeam(unsigned int team);

};


#endif //MAIN_LOADDATA2_H
