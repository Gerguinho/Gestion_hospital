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
    system("cls");
    printf("\n\n     ===== PROSANTE =====\n");
    printf("\n        QUI ETEZ VOUS ?\n\n");
    rin:
    printf("1.Médecin\n\n2.patient\n");
    
    scanf("%d",&a);
    system("cls");
    getchar();
    switch (a)
    {
    case 1:
        connection();  
        medecin();
        break;
    case 2:
        patient();
        break;
    default:
        printf("choix invalide\n\n    choisir entre 1 et 2\n\n");
        goto rin;
        }
    
}




