#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"

void inscription() {

    User us;

    // Saisie des informations utilisateur
    printf("Entrez votre nom : ");
    fgets(us.nom, MAX_L, stdin);
    us.nom[strcspn(us.nom, "\n")] = '\0';  // Suppression du '\n'
     sleep(1);
    printf("Entrez votre prénom : ");
    fgets(us.prenom, MAX_L, stdin);
    us.prenom[strcspn(us.prenom, "\n")] = '\0';
    sleep(1);
    printf("Entrez votre date de naissance (JJ MM AAAA) : ");
    scanf("%d %d %d", &us.date_nais.jour, &us.date_nais.mois, &us.date_nais.annee);
    getchar();  // Éviter un problème de buffer après `scanf`
    sleep(1);
    printf("Entrez votre adresse email : ");
    fgets(us.Email,MAX_L,stdin);
    us.Email[strcspn(us.Email,"\n")]='\0';
    sleep(1);
    printf("Entrez votre mot de passe");
    fgets(us.mot_passe,MAX_L,stdin);
    us.mot_passe[strcspn(us.mot_passe,"\n")]='\0';
    sleep(1);
    printf("confirmez votre mot de passe");
    fgets(us.mot_passe_confirm,MAX_L,stdin);
    us.mot_passe_confirm[strcspn(us.mot_passe_confirm,"\n")]='\0';// confirmation du mot de passe 
    sleep(1);
    if(strcmp(us.mot_passe,us.mot_passe_confirm)!=0){
        printf("Erreur ");//modifier le message 
    }else{
        printf("✅");// ajouter un emoji de juste 
    }
    // Ouvrir le fichier en mode ajout (a+)
    FILE *f = fopen(FILE_patient, "a+");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return ;
    }

    // Écriture dans le fichier CSV
    fprintf(f, "%s %s %s %s\n",us.nom, us.prenom, /*us.date_nais.jour, us.date_nais.mois, us.date_nais.annee*/us.Email,us.mot_passe);

    printf("\n✅ Enregistrement effectué avec succès !\n");

    // Fermer le fichier
    fclose(f);
}