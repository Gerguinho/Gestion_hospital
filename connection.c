#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"

void connection(){
    User med;
   char email[MAX_L], password[MAX_L],nom[MAX_L],prenom[MAX_L];
    int found = 0;
T:
    FILE *file = fopen(FILE_medecin, "r");
    if (file == NULL) {
        printf("Erreur : Le fichier des médecins n'existe pas !\n");
        exit(0);
    }

printf("=== Connexion Médecin ===\n\n");
printf("nom : ");
scanf("%s",nom);
printf("prenom : ");
scanf("%s",prenom);
printf("Email : ");
scanf("%s", email);
printf("Mot de passe : ");
scanf("%s", password);
 found = 0;
// Vérifier les informations dans le fichier
while (fscanf(file, "%s %s %s %s %s ", med.nom, med.prenom, med.Email, med.mot_passe, med.specialite) == 5) {
    if (strcmp(nom,med.nom) == 0 && strcmp(prenom,med.prenom) == 0 && strcmp(email, med.Email) == 0 && strcmp(password, med.mot_passe) == 0) {
        found = 1;
        break;
    }
}

fclose(file);

if (found) {
    system("cls");
    printf("Connexion réussie \n  \n  --------- Bienvenue Dr. %s----------", med.nom);
    printf("\n      Spécialité : %s\n", med.specialite);
} else {
    system("cls");
    printf("Erreur sur l'identifiant :Réessayez !\n");
     goto T;
}
}








   

    