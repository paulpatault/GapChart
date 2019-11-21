//
// Created by paul patault on 20/11/2019.
//

#include "Escalier.h"



std::vector<float> y_Escalier(LoadData myData, int team, float SCREEN_HEIGHT)
{
    const int NUMBER_OF_DAYS = myData.cardDays();

    std::vector<float> res(NUMBER_OF_DAYS);

    float complementaire, points;

    for(int day = 0; day < NUMBER_OF_DAYS; day++)
    {
        complementaire = myData.getComplementaryRankNormalized(team, day);
        points = myData.getPointsNormalized(team, day);

        res[day] = (points + complementaire) * SCREEN_HEIGHT/2.2;
    }

    return res;
}

void tabEscalier(GLfloat vertices[], const int NUMBER_OF_POINTS, const float epaisseur, const float dx, vector<float>  coordCenter)
{
    vec2 tot[NUMBER_OF_POINTS];
    const float x0 = 50;
    int days = 0;
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        if(i % 4 == 0)  // i divisible par 4 => debut de nouveau rectangle (->point haut gauche)
        {
            tot[i].x = x0 + (float) i * dx;
            if( i == 0 ) // on prend y0 pour le premier sommet du premier rectangle (->point haut gauche)
            {
                tot[i].y = coordCenter[0]; // == y0 (at t = 0)
            }
            else
            {
                tot[i].y = coordCenter[days];
            }

            if(i != 0)  // on change de jour pour chaque nouveau rectangle sauf pour le premier
            {
                days += 1;
            }
        }
        else if (i % 2 == 0) // i divisible par 2 => point haut droit du rectangle
        {
            tot[i].x = x0 + (float) i * dx;
            tot[i].y = tot[i - 2].y;
        }
        else // i impair => les autres points (:= bas gauche ou bas droit)
        {
            tot[i].x = tot[i - 1].x;
            tot[i].y = tot[i - 1].y - epaisseur;
        }
    }
    /// on rempli le tableau avec les pts obtenus
    //float ecart = 0;
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        //if(i > NUMBER_OF_POINTS/2) ecart = 50;
        vertices[3*i] = tot[i].x ;//+ ecart;
        vertices[3*i+1] = tot[i].y + 35; // +40 pour que le plus bas ne touche pas le bas de la fenetre
        vertices[3*i+2] = 0.07f;
    }
}

void escalierV0(const vec3 begin, const vec3 end, float vertices[], const int NUMBER_OF_POINTS, const float epaisseur, int winloose[])
{
    vec3 tot[NUMBER_OF_POINTS];
    float dx = (end.x-begin.x)/(float)NUMBER_OF_POINTS;
    float dy = 3*(end.y-begin.y)/(float)NUMBER_OF_POINTS;

    int days = 0;
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        if(i%2 == 0) {
            tot[i].x = begin.x + (float)i * dx;
            if(i%4 == 0){
                if( i == 0 ){
                    tot[i].y = begin.y;
                }
                else if(winloose[days] == 0){
                    tot[i].y =  tot[i-2].y - dy;
                } else {
                    tot[i].y = tot[i-2].y + dy;
                }
                if(i != 0) {
                    days++;
                }
            } else{
                tot[i].y = tot[i-2].y;
            }
            tot[i].z = 0;
        } else {
            tot[i].x = tot[i-1].x;
            tot[i].y = tot[i-1].y + epaisseur;
            tot[i].z = 0;
        }
    }

    /// on rempli le tableau avec les pts obtenus
    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        vertices[3*i] = tot[i].x;
        vertices[3*i+1] = tot[i].y;
        vertices[3*i+2] = tot[i].z;
    }
}
