//
// Created by paul patault on 06/11/2019.
//

#include "LoadData.h"

LoadData::LoadData(string filePath) {

    this->rankPoints = vector<vector<vector<int>>>(NUMBER_OF_DAYS + 1);

    ////// INITIALISE LE VEC_3D //////
    for(int i = 0; i < NUMBER_OF_DAYS + 1; i++) // i := jours
    {
        this->rankPoints[i] = vector<vector<int>>(NUMBER_OF_TEAMS); // initialise la 2e dim du tab
        for(int j = 0; j < NUMBER_OF_TEAMS; j++) // j := equipe
        {
            this->rankPoints[i][j] = vector<int>(2); // initialise la 3e dim du tab
        }
    }


    ////// TRAVAIL SUR LE FICHIER //////   ( 6 colonnes par jour )

    int rank, points;
    // declaration
    ifstream myfile;
    // ouverture
    myfile.open (filePath);
    // string qu'on récupère avec le getline()
    string value;
    // le caractère d'arret
    char c = ',';

    /// double for 'inversé' car le fichier est organisé comme ca (i.e. 1 ligne par equipe / jours = colonnes)
    for(int k = 0; k < NUMBER_OF_TEAMS; k++) // 2e dim := equipes
    {
        getline(myfile, value, c); // on passe le nom de l'équipe et le saut de ligne

        int index_for_tab = 0;

        /* explication du NUMBER_OF_DAYS+2 dans le 'for' suivant
         * on commence a NUMBER_OF_DAYS+1 dans tous les cas car len(tab) = 39
         * on saut le doublon au milieu donc +1
         * total : NUMBER_OF_DAYS+2
         */
        for(int idx = 0; idx < NUMBER_OF_DAYS + 2; idx++) //1ere dim := jours
        {

            // value = rang
            getline(myfile, value, c);
            //rank = stoi(value);
            try{
                rank = stoi(value);
            }
            catch(exception const& e) //On rattrape les exceptions standard de tous les types
            {
                cerr << "ERREUR R: " << e.what() << "  on value == " << value <<
                     " for idx == " << idx << " and k == " << k << endl; //On affiche la description de l'erreur
            }

            // value = points
            getline(myfile, value, c);
            //points = stoi(value);
            try{
                points = stoi(value);
            }
            catch(exception const& e) //On rattrape les exceptions standard de tous les types
            {
                cerr << "ERREUR P: " << e.what() << "  on value == " << value <<
                     " for idx == " << idx << " and k == " << k << endl; //On affiche la description de l'erreur
            }

            // saut des infos sur le match expliquant la situation
            {
                getline(myfile, value, c); // value = name
                getline(myfile, value, c); // value = buts
                getline(myfile, value, c); // value = buts
                getline(myfile, value, c); // value = name
            }


            // permet de "sauter" le milieu répété
            // et le dernier, répété aussi
            if( idx == 20 )// or (idx + 1 == NUMBER_OF_DAYS + 3) )
            {
                continue;
            }


            // on réajuste l'indice de remplissage du tableau
            // pour ne pas avoir un trou causé par le saut du rang: idx == 20
            if(idx == 21)
            {
                index_for_tab = 20;
            }

            this->rankPoints[index_for_tab][k][0] = rank; // rang
            this->rankPoints[index_for_tab][k][1] = points; // points

            index_for_tab += 1;
        }

        // saut des infos sur le match expliquant la situation pour le dernier rang répété !
        {
            getline(myfile, value, c); // value = rang
            getline(myfile, value, c); // value = points
            getline(myfile, value, c); // value = name
            getline(myfile, value, c); // value = buts
            getline(myfile, value, c); // value = buts
            getline(myfile, value, c); // value = name
        }

    }

    myfile.close();
}

int LoadData::getRank(int team, int day) {
    return this->rankPoints[day][team][0];
}

int LoadData::getComplementaryRank(int team, int day) {
    return 19 - this->getRank(team, day);
}

float LoadData::getComplementaryRankNormalized(int team, int day) {
    return (float)this->getComplementaryRank(team, day) / 19;
}

int LoadData::getPoints(int team, int day) {
    return this->rankPoints[day][team][1];
}

float LoadData::getPointsNormalized(int team, int day) {
    return (float)getPoints(team, day) / (float)NUMBER_OF_POINTS_MAX;
}

int LoadData::cardDays() {
    return NUMBER_OF_DAYS;
}

int LoadData::cardTeams() {
    return NUMBER_OF_TEAMS;
}

int LoadData::getMatch(int team, int day) {
    return 0;
}

// fonction à lancer dès le début du programme
// sert simplement à ne pas écrire le chemin des images (noms des équiques )
void LoadData::addPathToTab(string imagesPath) {
    /*this->teamPathPng = {
            "Man_City.png", "Liverpool.png", "Chelsea.png", "Tottenham.png", "Arsenal.png", "Man_United.png", "Wolves.png",
            "Everton.png", "Leicester.png", "West_Ham.png", "Watford.png", "Crystal_Palace.png", "Newcastle.png", "Bournemouth.png",
            "Burnley.png", "Southampton.png", "Brighton.png", "Cardiff.png", "Fulham.png", "Huddersfield.png"
    };*/
    for(int i = 0; i < NUMBER_OF_TEAMS; i++){
        this->teamPathPng[i] = imagesPath + this->teamPathPng[i];
    }
}

string LoadData::getImagesPath(int index) {
    return this->teamPathPng[index];
}


