//
// Created by paul patault on 16/12/2019.
//

#ifndef MAIN_CYLINDER_H
#define MAIN_CYLINDER_H


#include "LoadData.h"
#include "headers/constants.h"

class Cylinder {
private:
    LoadData *_myData;

    int _teamNumber;

public:
    Cylinder(int teamNumber, LoadData* data);

    ~Cylinder();

    void makeBottom();

    void makeCylinder();

    void makeNormals();



};


#endif //MAIN_CYLINDER_H
