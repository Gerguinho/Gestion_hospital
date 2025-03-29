#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"


void connection_patient(){
User pat;
char email[MAX_L], password[MAX_L],nom[MAX_L],prenom[MAX_L];
int found = 0;
T:

 FILE *file = fopen(FILE_patient, "r");// je dois creer un fichier txt pour patient
 if (file == NULL) {
     printf("Erreur : Le fichier des patients n'existe pas !\n");
     return;
 }


printf("=== Connexion patient ===\n");
printf("nom:");
scanf("%s",nom);
printf("prenom:");
scanf("%s",prenom);
printf("Email : ");
scanf("%s", email);
printf("Mot de passe : ");
scanf("%s", password);
found = 0;
// Vérifier les informations dans le fichier
while (fscanf(file, "%s %s %s %s", pat.nom, pat.prenom, pat.Email, pat.mot_passe) !=EOF) {
 if (strcmp(nom,pat.nom) == 0 && strcmp(prenom,pat.prenom) == 0 && strcmp(email, pat.Email) == 0 && strcmp(password, pat.mot_passe) == 0) {
     found = 1;
     break;
 }
}

fclose(file);

if (found) {
 printf("Connexion réussie ! Bienvenue patient %s.\n", pat.nom);
} else {
 printf("Erreur de connexion : Email ou mot de passe incorrect !\n");
 goto T;
}
}
