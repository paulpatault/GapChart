/*
for(int team = 0; team < NB_TEAMS; team++)
{
for(int i = 0; i < NB_POINTS * 3; i += 3)
{
if(i % 2 == 0 ){
for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++)
{
if(sous_tableau < milieu)
{
t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                         // .x
t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] - (sous_tableau * delta_epaisseur);  // .y
t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2] + (sous_tableau * epaisseur / (nbDivCylindre-1) ) ; // .z
}
else if(sous_tableau == milieu)
{
t_vertex_data_dim3[team][milieu][i]     = t_vertex_data[team][i];                                         // .x
t_vertex_data_dim3[team][milieu][i + 1] = t_vertex_data[team][i + 1] - (milieu * delta_epaisseur);  // .y
t_vertex_data_dim3[team][milieu][i + 2] = t_vertex_data[team][i + 2] + epaisseur; // .z
}
else if(sous_tableau == milieu + 1)
{
t_vertex_data_dim3[team][milieu][i]     = t_vertex_data[team][i];                                         // .x
t_vertex_data_dim3[team][milieu][i + 1] = t_vertex_data[team][i + 1] - ( (milieu + 1) * delta_epaisseur);  // .y
t_vertex_data_dim3[team][milieu][i + 2] = t_vertex_data[team][i + 2] + epaisseur; // .z
}
else if(sous_tableau > milieu)
{
t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                         // .x
t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] - (sous_tableau * delta_epaisseur);  // .y
t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2] + epaisseur - (sous_tableau * epaisseur / (nbDivCylindre-1) ) ; // .z
}
}

} else {

for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++)
{
if(sous_tableau < milieu)
{
t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data_dim3[team][sous_tableau][i - 3]     ;
t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data_dim3[team][sous_tableau][i - 3 + 1] - ((float)(sous_tableau + 1) * delta_epaisseur);
t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data_dim3[team][sous_tableau][i - 3 + 2] + ((float)(sous_tableau + 1) * epaisseur / (nbDivCylindre-1));
}
else if(sous_tableau == milieu)
{
t_vertex_data_dim3[team][milieu][i]     = t_vertex_data_dim3[team][sous_tableau][i - 3]     ;
t_vertex_data_dim3[team][milieu][i + 1] = t_vertex_data_dim3[team][sous_tableau][i - 3 + 1] - ((float)(sous_tableau + 1) * delta_epaisseur);
t_vertex_data_dim3[team][milieu][i + 2] = t_vertex_data_dim3[team][sous_tableau][i - 3 + 2] ;
}
else if(sous_tableau > milieu)
{
t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data_dim3[team][sous_tableau][i - 3]     ;
t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data_dim3[team][sous_tableau][i - 3 + 1] - ((float)(sous_tableau + 1) * delta_epaisseur);
t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data_dim3[team][sous_tableau][i - 3 + 2] - ((float)(sous_tableau + 1) * epaisseur / (nbDivCylindre-1));
}

/*
if(sous_tableau < milieu)
{
    t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                                                         // .x
    t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] + ( (float)(nbDivCylindre - 1 - sous_tableau) * delta_epaisseur );   // .y
    t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2] + ( sous_tableau * epaisseur / (nbDivCylindre-1) ); // .z
}
else if(sous_tableau == milieu)
{
    t_vertex_data_dim3[team][milieu][i]     = t_vertex_data[team][i];
    t_vertex_data_dim3[team][milieu][i + 1] = t_vertex_data[team][i + 1] + (milieu * delta_epaisseur);
    t_vertex_data_dim3[team][milieu][i + 2] = t_vertex_data[team][i + 2] + epaisseur;
}
else if(sous_tableau == milieu + 1)
{
    t_vertex_data_dim3[team][milieu][i]     = t_vertex_data[team][i];
    t_vertex_data_dim3[team][milieu][i + 1] = t_vertex_data[team][i + 1] + ( (milieu + 1) * delta_epaisseur);
    t_vertex_data_dim3[team][milieu][i + 2] = t_vertex_data[team][i + 2] + epaisseur;
}
else if(sous_tableau > milieu)
{
    t_vertex_data_dim3[team][sous_tableau][i]     = t_vertex_data[team][i];                                                                         // .x
    t_vertex_data_dim3[team][sous_tableau][i + 1] = t_vertex_data[team][i + 1] + ( (float)(nbDivCylindre - 1 - sous_tableau) * delta_epaisseur );   // .y
    t_vertex_data_dim3[team][sous_tableau][i + 2] = t_vertex_data[team][i + 2] + epaisseur - ( sous_tableau * epaisseur / (nbDivCylindre-1) ); // .z
}
 */
//}
//}
//}
/*
for(int day = 0; day < NB_DAYS * 2; day++)
{
    for(int sous_tableau = 0; sous_tableau < nbDivCylindre; sous_tableau++)
    {
        normals[team][day][sous_tableau].x = t_vertex_data_dim3[team][sous_tableau][day]     - centreDecale[team][day].x;
        normals[team][day][sous_tableau].y = t_vertex_data_dim3[team][sous_tableau][day + 1] - centreDecale[team][day].y;
        normals[team][day][sous_tableau].z = t_vertex_data_dim3[team][sous_tableau][day + 2] - centreDecale[team][day].z;
    }
}
 */
//}

