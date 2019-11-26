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
    loadMatch(filePath);

    myfile.close();
}

void LoadData::loadMatch(string filePath) {

    this->match = vector<vector<Match>>(NUMBER_OF_TEAMS); // 38


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
    for(int team = 0; team < NUMBER_OF_TEAMS; team++) // 2e dim := equipes
    {
        this->match[team] = vector<Match>(NUMBER_OF_DAYS);
        getline(myfile, value, c); // on passe le nom de l'équipe et le saut de ligne
        getline(myfile, value, c); // value = rang
        getline(myfile, value, c); // value = points
        getline(myfile, value, c); // value = name
        getline(myfile, value, c); // value = buts
        getline(myfile, value, c); // value = buts
        getline(myfile, value, c); // value = name

        int index_for_match = -1;

        for(int day = 0; day < NUMBER_OF_DAYS; day++) //1ere dim := jours
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

            this->match[team][day] = {teamAtHome, teamAway, scoreAtHome, scoreAway};

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

            this->match[team][day].win = win;

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

int LoadData::getIndexByName(string name){
    for(int i = 0; i < NUMBER_OF_TEAMS; i++)
    {
        if(name == " " + NAMES[i])
            return i;
    }
    return -1;
}

int LoadData::cardDays() {
    return NUMBER_OF_DAYS;
}

int LoadData::cardTeams() {
    return NUMBER_OF_TEAMS;
}

int LoadData::getAdversaire(int team, int day) {

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

void LoadData::initVertexDataD1(float FSCREEN_HEIGHT, float epaisseur, float dx) {
    std::vector<float> tabY(NUMBER_OF_DAYS);
    std::vector<vector<float>> yEscBis(NUMBER_OF_TEAMS);
    for(int team = 0; team < NUMBER_OF_TEAMS; team++)
    {
        tabY = y_Escalier(team, FSCREEN_HEIGHT);
        yEscBis[team] = y_Escalier(team, FSCREEN_HEIGHT);
        tabEscalier(this->t_vertex_data[team], (4 * (NUMBER_OF_DAYS + 1)), epaisseur, dx, tabY);
    }
}

std::vector<float> LoadData::y_Escalier(int team, float SCREEN_HEIGHT)
{

    std::vector<float> res(NUMBER_OF_DAYS);

    float complementaire, points;

    for(int day = 0; day < NUMBER_OF_DAYS; day++)
    {
        complementaire = this->getComplementaryRankNormalized(team, day);
        points = this->getPointsNormalized(team, day);

        res[day] = (points + complementaire) * SCREEN_HEIGHT/2.2;
    }

    return res;
}

void LoadData::tabEscalier(float vertices[], const int NUMBER_OF_POINTS, const float epaisseur, const float dx, vector<float>  coordCenter)
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
        if(i != NUMBER_OF_POINTS -1 ){
            if(tot[i].y > tot[i + 1].y)
                vertices[3*i+2] = -2.f * (tot[i].y - tot[i + 1].y);
            else
                vertices[3*i+2] = 0;
        }
        vertices[3*i+2] = 0.08f;

    }
}

float LoadData::getVertexDataValue(int i, int j) {
    return this->t_vertex_data[i][j];
}


void LoadData::initVertexDataD2(float FSCREEN_HEIGHT, float epaisseur, float dx) {
    std::vector<float> tabY(NUMBER_OF_DAYS);
    std::vector<float> tabY_double(NUMBER_OF_DAYS);
    for(int team = 0; team < NUMBER_OF_TEAMS; team++)
    {
        tabY = y_Escalier(team, FSCREEN_HEIGHT);
        tabY_double = y_Escalier_double(tabY);
        tabEscalier_double(this->t_vertex_data_double[team], epaisseur, dx, tabY_double);
    }
    for(int i = 0; i < (4 * (38 + 1))  + (2*37) ; i+= 3)
    {
        cout << this->t_vertex_data_double[0][i] << " ";
        cout << this->t_vertex_data_double[0][i + 1] << " ";
        cout << this->t_vertex_data_double[0][i + 2] << endl;
    }
}

std::vector<float> LoadData::y_Escalier_double(std::vector<float> nonDouble)
{
    std::vector<float> res(NUMBER_OF_DAYS + NUMBER_OF_DAYS - 1);

    for(int day = 0; day < NUMBER_OF_DAYS + NUMBER_OF_DAYS - 1; day += 2)
    {
        res[day] = nonDouble[day];
        if(day == (NUMBER_OF_DAYS + NUMBER_OF_DAYS - 1) - 1)
            break;
        res[day + 1] = (nonDouble[day/2] + nonDouble[(day + 1)/2]) / 2;
    }

    return res;
}

void LoadData::tabEscalier_double(float vertices[], const float epaisseur, const float dx, vector<float>  coordCenter)
{
    const int NUMBER_OF_POINTS = (4 * (NUMBER_OF_DAYS + 1));
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


    vec2 ajoutPoints[(2 * NUMBER_OF_DAYS) - 1];

    int ktab = 0;
    for(int i = 0; i < (2 * NUMBER_OF_DAYS) - 1; i++)
    {
        if( i % 2 == 0 )
        {
            ajoutPoints[i].x = tot[ktab + ktab + 1].x + (tot[ktab + ktab + 1 + 3].x - tot[ktab + ktab + 1].x) / 2;
            ajoutPoints[i].y = tot[ktab + ktab + 1].y + (tot[ktab + ktab + 1 + 3].y - tot[ktab + ktab + 1].y) / 2;
        }
        else
        {
            ajoutPoints[i].x = ajoutPoints[i - 1].x ;
            ajoutPoints[i].y = ajoutPoints[i - 1].y - epaisseur;
        }

        ktab += 1;
    }

    cout << "______" << ajoutPoints[2 * NUMBER_OF_DAYS].x << endl;

    /// on rempli le tableau avec les pts obtenus
    //float ecart = 0;
    /*for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        //if(i > NUMBER_OF_POINTS/2) ecart = 50;
        vertices[3*i] = tot[i].x ;//+ ecart;
        vertices[3*i+1] = tot[i].y + 35; // +40 pour que le plus bas ne touche pas le bas de la fenetre
        if(i != NUMBER_OF_POINTS -1 ){
            if(tot[i].y > tot[i + 1].y)
                vertices[3*i+2] = -2.f * (tot[i].y - tot[i + 1].y);
            else
                vertices[3*i+2] = 0;
        }
        vertices[3*i+2] = 0.08f;

    }*/

    int kGdTab = 0;
    int kPtTab = 0;

    for(int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        if( (i - 4) % 6 == 0)
        {
            vertices[3*i]   = ajoutPoints[kPtTab].x ;
            cout << ajoutPoints[kPtTab].x << " " << ajoutPoints[kPtTab + 1].x << endl;
            vertices[3*i+1] = ajoutPoints[kPtTab].y + 35;
            if(i != NUMBER_OF_POINTS -1 ){
                if(tot[kGdTab].y > tot[kGdTab + 2].y)
                    vertices[3*i+2] = -20;
                else
                    vertices[3*i+2] = 20.f;
            }
            i++ ;

            vertices[3*i]   = ajoutPoints[kPtTab + 1].x ;
            vertices[3*i+1] = ajoutPoints[kPtTab + 1].y + 35;
            if(i != NUMBER_OF_POINTS -1 ){
                if(tot[kGdTab].y > tot[kGdTab + 2].y)
                    vertices[3*i+2] = -20;
                else
                    vertices[3*i+2] = 20.f;
            }

            kPtTab += 2;
        }
        else
        {
            vertices[3*i]   = tot[kGdTab].x ;
            vertices[3*i+1] = tot[kGdTab].y + 35;
            vertices[3*i+2] = 0.f;
            kGdTab ++;
        }
    }
    cout << endl << endl << endl;
}

float LoadData::getVertexDataValue_double(int i, int j){
    return this->t_vertex_data_double[i][j];
}




