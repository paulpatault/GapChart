//
// Created by paul patault on 06/11/2019.
//

#include "LoadData.h"

namespace data {

    LoadData::LoadData(std::string filePath)
    {
        this->rankPoints = std::vector<std::vector<DayTrip>>(cst::NB_DAYS + 1);

        ////// INITIALISE LE VEC_3D //////
        for(int i = 0; i < cst::NB_DAYS + 1; i++) // i := jours
        {
            this->rankPoints[i] = std::vector<DayTrip>(cst::NB_TEAMS);
        }


        ////// TRAVAIL SUR LE FICHIER //////   ( 6 colonnes par jour )

        int rank, points;
        std::ifstream myfile;
        myfile.open (filePath);

        std::string value;
        char c = ',';

        /// double for 'inversé' car le fichier est organisé comme ca (i.e. 1 ligne par equipe / jours = colonnes)
        for(int k = 0; k < cst::NB_TEAMS; k++) // 2e dim := equipes
        {
            std::getline(myfile, value, c); // on passe le nom de l'équipe et le saut de ligne

            int index_for_tab = 0;

            /* explication du cst::NB_DAYS+2 dans le 'for' suivant
             * on commence a cst::NB_DAYS+1 dans tous les cas car len(tab) = 39
             * on saut le doublon au milieu donc +1
             * total : cst::NB_DAYS+2
             */
            for(int idx = 0; idx < cst::NB_DAYS + 2; idx++)
            {

                // rank
                std::getline(myfile, value, c);
                try{
                    rank = std::stoi(value);
                }
                catch(exception const& e) //On rattrape les exceptions standard de tous les types
                {
                    std::cerr << "ERREUR R: " << e.what() << "  on value == " << value <<
                              " for idx == " << idx << " and k == " << k << std::endl; //On affiche la description de l'erreur
                }

                // points
                getline(myfile, value, c);
                try{
                    points = std::stoi(value);
                }
                catch(exception const& e) //On rattrape les exceptions standard de tous les types
                {
                    std::cerr << "ERREUR P: " << e.what() << "  on value == " << value <<
                              " for idx == " << idx << " and k == " << k << std::endl; //On affiche la description de l'erreur
                }

                // saut des infos sur le match expliquant la situation
                {
                    std::getline(myfile, value, c); // value = name
                    std::getline(myfile, value, c); // value = buts
                    std::getline(myfile, value, c); // value = buts
                    std::getline(myfile, value, c); // value = name
                }


                // permet de "sauter" le milieu répété
                // et le dernier, répété aussi
                if( idx == 20 )// or (idx + 1 == cst::NB_DAYS + 3) )
                {
                    continue;
                }


                // on réajuste l'indice de remplissage du tableau
                // pour ne pas avoir un trou causé par le saut du rang: idx == 20
                if(idx == 21)
                {
                    index_for_tab = 20;
                }

                rankPoints[index_for_tab][k].rank = rank; // rang
                rankPoints[index_for_tab][k].points = points; // points

                index_for_tab += 1;
            }

            // saut des infos sur le match expliquant la situation pour le dernier rang répété !
            {
                std::getline(myfile, value, c); // value = rang
                std::getline(myfile, value, c); // value = points
                std::getline(myfile, value, c); // value = name
                std::getline(myfile, value, c); // value = buts
                std::getline(myfile, value, c); // value = buts
                std::getline(myfile, value, c); // value = name
            }

        }
        loadMatch(filePath);

        myfile.close();

        std::cout << "Data well loaded" << std::endl;
    }

    void LoadData::loadMatch(std::string filePath)
    {
        match = vector<vector<Match>>(cst::NB_TEAMS); // 38


        ////// TRAVAIL SUR LE FICHIER //////   ( 6 colonnes par jour )

        string teamAtHome, teamAway;
        int scoreAtHome, scoreAway, indiceAway, indiceAtHome, win;
        // declaration
        ifstream myfile;
        // ouverture
        myfile.open (filePath);
        // string qu'on récupère avec le getline()
        string value;
        // le caractère d'arret
        char c = ',';

        /// double for 'inversé' car le fichier est organisé comme ca (i.e. 1 ligne par equipe / jours = colonnes)
        for(int team = 0; team < cst::NB_TEAMS; team++) // 2e dim := equipes
        {
            match[team] = vector<Match>(cst::NB_DAYS);
            getline(myfile, value, c); // on passe le nom de l'équipe et le saut de ligne
            getline(myfile, value, c); // value = rang
            getline(myfile, value, c); // value = points
            getline(myfile, value, c); // value = name
            getline(myfile, value, c); // value = buts
            getline(myfile, value, c); // value = buts
            getline(myfile, value, c); // value = name

            int index_for_match = -1;

            for(int day = 0; day < cst::NB_DAYS; day++) //1ere dim := jours
            {
                if(day == 19)
                {
                    getline(myfile, value, c); // value = rang
                    getline(myfile, value, c); // value = points
                    getline(myfile, value, c); // value = name
                    getline(myfile, value, c); // value = buts
                    getline(myfile, value, c); // value = buts
                    getline(myfile, value, c); // value = name
                }
                getline(myfile, value, c); // rank
                getline(myfile, value, c); // points

                // infos sur le match expliquant la situation
                getline(myfile, value, c); // value = name
                teamAtHome = value;
                getline(myfile, value, c); // value = buts
                scoreAtHome = stoi(value);
                getline(myfile, value, c); // value = buts
                scoreAway = stoi(value);
                getline(myfile, value, c); // value = name
                teamAway = value;

                indiceAtHome = getIndexByName(teamAtHome);
                indiceAway = getIndexByName(teamAway);

                match[team][day] = {teamAtHome, teamAway, scoreAtHome, scoreAway};

                if(indiceAtHome == team)
                {
                    if(scoreAtHome > scoreAway) win = 1;        // victoire
                    else if(scoreAtHome < scoreAway) win = -1;  // défaite
                    else win = 0;                               // égalité
                }
                else if (indiceAway == team)
                {
                    if(scoreAtHome < scoreAway) win = 1;        // victoire
                    else if(scoreAtHome > scoreAway) win = -1;  // défaite
                    else win = 0;                               // égalité
                }
                else {
                    std::cerr << "problem w/ index of teams ::" << teamAtHome << " " << teamAway << std::endl;
                }

                match[team][day].win = win;

                if( day == 21 )
                {
                    continue;
                }

                index_for_match += 1;
            }

            // saut des infos sur le match expliquant la situation pour le dernier rang répété !
            getline(myfile, value, c); // value = rang
            getline(myfile, value, c); // value = points
            getline(myfile, value, c); // value = name
            getline(myfile, value, c); // value = buts
            getline(myfile, value, c); // value = buts
            getline(myfile, value, c); // value = name

        }

        myfile.close();
    }

    std::vector<DayTrip> LoadData::getTeam(unsigned int team)
    {
        return rankPoints[team];
    }

    int LoadData::getRank(int team, int day)
    {
        return rankPoints[day][team].rank;
    }

    int LoadData::getComplementaryRank(int team, int day)
    {
        return 19 - getRank(team, day);
    }

    float LoadData::getComplementaryRankNormalized(int team, int day)
    {
        return (float)getComplementaryRank(team, day) / 19;
    }

    int LoadData::getPoints(int team, int day)
    {
        return rankPoints[day][team].points;
    }

    float LoadData::getPointsNormalized(int team, int day)
    {
        return (float)getPoints(team, day) / (float)cst::MAX_POINTS;
    }

    int LoadData::getIndexByName(std::string name)
    {
        for(int i = 0; i < cst::NB_TEAMS; i++)
        {
            if(name == " " + NAMES[i])
                return i;
        }
        return -1;
    }

    int LoadData::getAdversaire(int team, int day)
    {

        string res = "L'équipe";

        string askedTeam  = this->match[team][day].teamAtHome;
        string otherTeam = this->match[team][day].teamAway;
        string inOut = " à domicile";

        if(getIndexByName(this->match[team][day].teamAway) == team )  // At Home
        {
            askedTeam = this->match[team][day].teamAway;
            otherTeam = this->match[team][day].teamAtHome;
            inOut = " à l'extérieur";
        }

        res += askedTeam;

        switch(this->match[team][day].win)
        {
            case 1:
                res += " a gagné";
                break;
            case 0:
                res += " a fait égalité";
                break;
            case -1:
                res += " a perdu";
                break;
            default:
                break;
        }
        res += " contre l'équipe" + otherTeam + " avec le score de ";
        res += to_string(this->match[team][day].scoreAtHome) + " à " + to_string(this->match[team][day].scoreAway);
        res += inOut + ".";
        //res += " le " + to_string(day+1) + "ième jour." ;
        std::cout << res << std::endl;

        int adv = getIndexByName(otherTeam);
        return adv;
    }

    void LoadData::addPathToTab(std::string imagesPath)
    {
        // fonction à lancer dès le début du programme
        // sert simplement à ne pas écrire le chemin des images (noms des équiques )

        /*this->teamPathPng = {
                "Man_City.png", "Liverpool.png", "Chelsea.png", "Tottenham.png", "Arsenal.png", "Man_United.png", "Wolves.png",
                "Everton.png", "Leicester.png", "West_Ham.png", "Watford.png", "Crystal_Palace.png", "Newcastle.png", "Bournemouth.png",
                "Burnley.png", "Southampton.png", "Brighton.png", "Cardiff.png", "Fulham.png", "Huddersfield.png"
        };*/
        for(int i = 0; i < cst::NB_TEAMS; i++){
            this->teamPathPng[i] = imagesPath + this->teamPathPng[i];
        }
    }

    std::string LoadData::getImagesPath(int index)
    {
        return this->teamPathPng[index];
    }

    void LoadData::initVertexDataD1()
    {
        std::vector<float> tabY(cst::NB_DAYS);

        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            tabY = y_Escalier(team);
            tabEscalier(this->t_vertex_data[team], (tabY));
        }
    }

    std::vector<float> LoadData::y_Escalier(int team)
    {
        std::vector<float> res(cst::NB_DAYS);

        float complementaire, points;

        for(int day = 0; day < cst::NB_DAYS; day++)
        {
            complementaire = this->getComplementaryRankNormalized(team, day);
            points = this->getPointsNormalized(team, day);

            res[day] = (points + complementaire) * cst::SCREEN_HEIGHT/2.2;
        }

        return res;
    }

    void LoadData::tabEscalier(float vertices[], vector<float>  coordCenter)
    {
        vec2 tot[cst::NB_POINTS];
        const float x0 = 50;
        int days = 0;
        for(int i = 0; i < cst::NB_POINTS; i++)
        {
            if(i % 4 == 0)  // i divisible par 4 => debut de nouveau rectangle (->point haut gauche)
            {
                tot[i].x = x0 + (float) i * cst::dx;
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
                tot[i].x = x0 + (float) i * cst::dx;
                tot[i].y = tot[i - 2].y;
            }
            else // i impair => les autres points (:= bas gauche ou bas droit)
            {
                tot[i].x = tot[i - 1].x;
                tot[i].y = tot[i - 1].y - cst::THICKNESS;
            }
        }
        /// on rempli le tableau avec les pts obtenus
        //float ecart = 0;
        for(int i = 0; i < cst::NB_POINTS; i++)
        {
            //if(i > NUMBER_OF_POINTS/2) ecart = 50;
            vertices[3*i] = tot[i].x ;//+ ecart;
            vertices[3*i+1] = tot[i].y + 35; // +40 pour que le plus bas ne touche pas le bas de la fenetre
            if(i != cst::NB_POINTS -1 ){
                if(tot[i].y > tot[i + 1].y)
                    vertices[3*i+2] = -2.f * (tot[i].y - tot[i + 1].y);
                else
                    vertices[3*i+2] = 0;
            }
            vertices[3*i+2] = 0.08f;

        }
    }

    float LoadData::getVertexDataValue(int i, int j)
    {
        return this->t_vertex_data[i][j];
    }


}

