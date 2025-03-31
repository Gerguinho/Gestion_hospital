#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"
void medecin(){
    int choix;
    bin:
    printf("que souhaitez vous faire ?");
    printf("\n 1.consulter le dossier médical d'un patient?");
    printf("\n 2.modifier votre disponibilité pour aujourd'hui?");
    printf("\n 3.écrire à un patient?");
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
            printf(" selectionné entre les numero 1, 2 ou 3\n");
        goto bin;
        break;
     }
}