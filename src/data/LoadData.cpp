//
// Created by paul patault on 06/11/2019.
//

#include "LoadData.h"

namespace data {

    /**
     * Constructor
     * Chargement des rangs et des points du fichier .csv dans le vector rankPoints
     * @param filePath chemin du fichier .csv
     */
    LoadData::LoadData(const std::string& filePath)
    {
        rankPoints = std::vector<std::vector<DayTrip>>(cst::NB_DAYS + 1);

        ////// INITIALISE LE VEC_3D //////
        for(int i = 0; i < cst::NB_DAYS + 1; i++) // i := jours
        {
            rankPoints[i] = std::vector<DayTrip>(cst::NB_TEAMS);
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

    /**
     * Chargement des matchs du fichier .csv dans match ( vector de structure Match)
     * @param filePath chemin du fichier .csv
     */
    void LoadData::loadMatch(const std::string& filePath)
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

                indiceAtHome = __getIndexByName(teamAtHome);
                indiceAway = __getIndexByName(teamAway);

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

    /**
     * Getter basic
     * @param team équipe demandé
     * @param day jour demandé
     * @return le rank pour l'équipe team au jour day
     */
    int LoadData::__getRank(int team, int day) const
    {
        return rankPoints[day][team].rank;
    }

    /**
     * Getter basic
     * @param team équipe demandé
     * @param day jour demandé
     * @return le rank complémentaire pour l'équipe team au jour day
     */
    int LoadData::getComplementaryRank(int team, int day) const
    {
        return 19 - __getRank(team, day);
    }

    /**
     * Getter basic
     * @param team équipe demandé
     * @param day jour demandé
     * @return le rank complémentaire normalisé pour l'équipe team au jour day
     */
    float LoadData::getComplementaryRankNormalized(int team, int day) const
    {
        return (float)getComplementaryRank(team, day) / 19;
    }

    /**
     * Getter basic
     * @param team équipe demandé
     * @param day jour demandé
     * @return le nombre de points pour l'équipe team au jour day
     */
    int LoadData::__getPoints(int team, int day) const
    {
        return rankPoints[day][team].points;
    }

    /**
     * Getter basic
     * @param team équipe demandé
     * @param day jour demandé
     * @return le nombre de points normalisés pour l'équipe team au jour day
     */
    float LoadData::getPointsNormalized(int team, int day) const
    {
        return (float) __getPoints(team, day) / (float)cst::MAX_POINTS;
    }

    /**
     * Getter basic
     * @param nom string du nom de l'équipe
     * @return l'indice de l'équipe (dans [0, 20])
     */
    int LoadData::__getIndexByName(std::string nom) const
    {
        for(int team = 0; team < cst::NB_TEAMS; team++)
        {
            if(nom == " " + NAMES[team])
                return team;
        }
        return -1;
    }

    /**
     * Getter basic
     * @param team équipe demandé
     * @param day jour demandé
     * @return l'adversaire de l'équipe team pour le match du jour day
     */
    int LoadData::getAdversary(int team, int day) const
    {

        string res = "L'équipe";

        string askedTeam  = match[team][day].teamAtHome;
        string otherTeam = match[team][day].teamAway;
        string inOut = " à domicile";

        if(__getIndexByName(match[team][day].teamAway) == team )  // At Home
        {
            askedTeam = match[team][day].teamAway;
            otherTeam = match[team][day].teamAtHome;
            inOut = " à l'extérieur";
        }

        res += askedTeam;

        switch(match[team][day].win)
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
        res += to_string(match[team][day].scoreAtHome) + " à " + to_string(match[team][day].scoreAway);
        res += inOut + ".";
        //res += " le " + to_string(day+1) + "ième jour." ;

        //std::cout << res << std::endl;

        int adv = __getIndexByName(otherTeam);
        return adv;
    }

    /**
     * Getter basic
     * @param index de l'equipe demandée
     * @return chemin du .png de la texture
     */
    const char* LoadData::getImagesPath(int index) const
    {
        switch (index) {
            case 0:
                return "../resources/images/Man_City.png";
            case 1:
                return "../resources/images/Liverpool.png";
            case 2:
                return "../resources/images/Chelsea.png";
            case 3:
                return "../resources/images/Tottenham.png";
            case 4:
                return "../resources/images/Arsenal.png";
            case 5:
                return "../resources/images/Man_United.png";
            case 6:
                return "../resources/images/Wolves.png";
            case 7:
                return "../resources/images/Everton.png";
            case 8:
                return "../resources/images/Leicester.png";
            case 9:
                return "../resources/images/West_Ham.png";
            case 10:
                return "../resources/images/Watford.png";
            case 11:
                return "../resources/images/Crystal_Palace.png";
            case 12:
                return "../resources/images/Newcastle.png";
            case 13:
                return "../resources/images/Bournemouth.png";
            case 14:
                return "../resources/images/Burnley.png";
            case 15:
                return "../resources/images/Southampton.png";
            case 16:
                return "../resources/images/Brighton.png";
            case 17:
                return "../resources/images/Cardiff.png";
            case 18:
                return "../resources/images/Fulham.png";
            case 19 :
                return "../resources/images/Huddersfield.png";
            default:
                exit(-1);
        }
    }

    /**
     * Getter basic
     * @param team équipe demandé
     * @return l'ensemble des matchs joués par l'équipe team
     */
    std::vector<Match> LoadData::getMatchs(int team) const
    {
        return match[team];
    }

    void LoadData::destroy(const LoadData *pData)
    {
        delete pData;
    }


}

