#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"
void medecin(){
    int choix;
    bin:
    printf("\n \n        que souhaitez vous faire ?");
    printf("\n \n1.consulter le dossier médical d'un patient?");
    printf("\n \n2.mettre ou modifier votre disponibilité ?");
    printf("\n \n3.écrire à un patient?\n");
    scanf("%d",&choix);
    switch(choix){
        case 1:
            system("cls");
            consulter_ou_creer_dossier();
            break;
        case 2:
            system("cls");
            mettreAJourDisponibilite();
            break;
        case 3:
            system("cls");
            ecrirePatient();
            break;
        
        default:
            system("cls");
            printf(" \n       selectionnez entre les numeros 1, 2 ou 3\n\n");
        goto bin;
        break;
     }
}