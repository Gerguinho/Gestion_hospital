#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"
const char *FILE_patient = "patient.csv";
const char *FILE_medecin="Medecin.csv";

void fonction_principale(){
    int a;
    printf("Qui etes vous ?\n");
    printf("1.Médecin\n2.patient\n");
    rin:
    scanf("%d",&a);
    system("cls");
    getchar();
    switch (a)
    {
    case 1:
        connection();  //il faut gerer le probleme du
        medecin();
        break;
    case 2:
        patient();
        break;
    default:
        printf("choix invalide\n choisir entre 1 et 2");
        goto rin;
        }
    
}




