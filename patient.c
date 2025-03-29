#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"
void patient(){
    int b,c,choix;
    printf("voulez vous vous connecter ou vous inscrire?\n 1. M'inscire  \n 2. Me connecter ");
    run:
    scanf("%d",&b);
    system("cls");
    getchar();
    switch (b)
    {
    case 1:
        inscription();
        system("cls");
        printf("choisir un abonnement ou profiter des 1 mois d'essai gratuit?");
        printf("\n 1 choisir un abonnement");
        printf("\n 2. Profiter du mois d'essai gratuit  ");
        scanf("%d",&choix);
        if(choix==1){
            abonnement();
        }
        if(choix==2){
            essai_gratuit();
        }
        break;
    case 2:
        connection_patient();
        printf("                                  ----------hello----------                                     ");
        printf("\n   ----------bienvenue chers patient j'espère que ça va pour le mieux aujourdh'hui----------");
        printf("\nvoulez vous prendre rendez vous avec un medecin ou voulez vous consulter votre ordonnance.");
        printf("\n choisir 1 pour prendre rendez vous et 2 pour consulter l'ordonnance ");
         ran:
        scanf("%d",&c);
        switch (c)
        {
        case 1:
            printf("quelle categories de médecin voulez vous rencontrer?");
            printf("choisir un medecin");// a modifier
            break;
        case 2:
            ordonnance();
        
        default:
        printf("choix invalide\n choisir entre 1 et 2");
        goto ran;
            break;
        }

        break;
    default:
        printf("choix invalide\n choisir entre 1 et 2");
        goto run;
    }
}