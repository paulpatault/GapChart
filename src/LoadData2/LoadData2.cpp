//
// Created by paul patault on 16/12/2019.
//

#include "LoadData2.h"

/*
LoadData2::LoadData2(std::string& filePath)
{
    std::ifstream myfile;
    myfile.open (filePath);

    std::string value;
    char c = ',';

    /// double for 'inversé' car le fichier est organisé comme ca (i.e. 1 ligne par equipe / jours = colonnes)
    for(int k = 0; k < cst::NB_TEAMS; k++) // 2e dim := equipes
    {
        std::getline(myfile, value, c); // on passe le nom de l'équipe et le saut de ligne

        int index_for_tab = 0;

        std::vector<DayTrip, std::allocator<DayTrip>> days(cst::NB_DAYS);
        for(int idx = 0; idx < cst::NB_DAYS + 2; idx++)
        {
            DayTrip dayTrip{};

            // rank
            std::getline(myfile, value, c);
            try{
                dayTrip.rank = std::stoi(value);
            }
            catch(std::exception const& e) //On rattrape les exceptions standard de tous les types
            {
                std::cerr << "ERREUR R: " << e.what() << "  on value == " << value <<
                          " for idx == " << idx << " and k == " << k << std::endl; //On affiche la description de l'erreur
            }

            // points
            getline(myfile, value, c);
            try{
                dayTrip.points = std::stoi(value);
            }
            catch(std::exception const& e) //On rattrape les exceptions standard de tous les types
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

            days.at(index_for_tab) = dayTrip;

            index_for_tab += 1;
        }

        v_rankPoints->at(k) = days;

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

    myfile.close();

    std::cout << "Data well loaded" << std::endl;

}
*/

LoadData2::LoadData2(std::string &filePath)
{
    int rank, points;
    std::ifstream myfile;
    myfile.open (filePath);

    std::string value;
    char c = ',';

    for(int k = 0; k < cst::NB_TEAMS; k++) // 2e dim := equipes
    {
        std::getline(myfile, value, c); // on passe le nom de l'équipe et le saut de ligne

        int index_for_tab = 0;

        for(int idx = 0; idx < cst::NB_DAYS + 2; idx++)
        {

            // rank
            std::getline(myfile, value, c);
            try{
                rank = std::stoi(value);
            }
            catch(std::exception const& e) //On rattrape les exceptions standard de tous les types
            {
                std::cerr << "ERREUR R: " << e.what() << "  on value == " << value <<
                          " for idx == " << idx << " and k == " << k << std::endl; //On affiche la description de l'erreur
            }

            // points
            getline(myfile, value, c);
            try{
                points = std::stoi(value);
            }
            catch(std::exception const& e) //On rattrape les exceptions standard de tous les types
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

            v_rankPoints->at(index_for_tab)[k].rank = rank;
            v_rankPoints->at(index_for_tab)[k].points = points;

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

    myfile.close();

    std::cout << "Data2 well loaded" << std::endl;
}

LoadData2::~LoadData2() = default;

std::vector<DayTrip> LoadData2::getTeam(unsigned int team)
{
    return v_rankPoints->at(team);
}

