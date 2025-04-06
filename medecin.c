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
    printf("\n \n2.modifier votre disponibilité pour aujourd'hui?");
    printf("\n \n3.écrire à un patient?\n");
    scanf("%d",&choix);
    switch(choix){
        case 1:
            system("cls");
            printf("dossier médical");
            break;
        case 2:
            system("cls");
            printf("modifier la disponibilité");
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