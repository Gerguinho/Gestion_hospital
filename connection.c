#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"
#include <conio.h>

void connection() {
    User med;
    char email[MAX_L], password[MAX_L], nom[MAX_L], prenom[MAX_L];
    int found = 0, choix = 0;
T:
    FILE *file = fopen(FILE_medecin, "r");
    if (file == NULL) {
        printf("Erreur : Le fichier des médecins n'existe pas !\n");
        exit(0);
    }
    nom[0] = '\0';
    prenom[0] = '\0';
    email[0] = '\0';
    password[0] = '\0';

    do {
        system("cls"); // Effacer l'écran pour rendre propre
        printf("=== Connexion Médecin ===\n\n");

        printf("1. Nom : %s\n",nom);
        printf("2. Prénom : %s\n",prenom);
        printf("3. Email : %s\n",email);
        //printf("4. Mot de passe : %s\n",password);
        printf("4. Mot de passe : ");
for (int j = 0; j < strlen(password); j++) {
    printf("*");
}
printf("\n");

        printf("5. Valider et se connecter\n");
        printf("NB: vous devez obligatoirement remplir tous les champs pour vous connecter et si une information est incorrecte vous n'arriverez pas à vous  connecter\n");
        printf("\nChoisissez un champ à remplir/modifier (1-5) : ");
        scanf("%d", &choix);
        getchar(); // Pour consommer le \n après scanf

        switch (choix) {
            case 1:
                printf("Entrez votre Nom : ");
                scanf("%s", nom);
                break;
            case 2:
                printf("Entrez votre Prénom : ");
                scanf("%s", prenom);
                break;
            case 3:
                printf("Entrez votre Email : ");
                scanf("%s", email);
                break;
            case 4:
                printf("Entrez votre Mot de passe : ");
                printf("Mot de passe : \n     ");
int i = 0;
char ch;
while ((ch = getch()) != '\r') {  // '\r' correspond à Entrée
    if (ch == 8) { // touche retour arrière
        if (i > 0) {
            i--;
            printf("\b \b");
        }
    } else if (i < MAX_L - 1) {
        password[i++] = ch;
        printf("*");
    }
}
password[i] = '\0';

                //scanf("%s", password);
                break;
                case 5: {
                    rewind(file); // Revenir au début du fichier
                
                    int nom_ok = 0, prenom_ok = 0, email_ok = 0, mdp_ok = 0;
                
                    while (fscanf(file, "%s %s %s %s %s", med.nom, med.prenom, med.Email, med.mot_passe, med.specialite) == 5) {
                        if (!nom_ok && strcmp(nom, med.nom) == 0) nom_ok = 1;
                        if (!prenom_ok && strcmp(prenom, med.prenom) == 0) prenom_ok = 1;
                        if (!email_ok && strcmp(email, med.Email) == 0) email_ok = 1;
                        if (!mdp_ok && strcmp(password, med.mot_passe) == 0) mdp_ok = 1;
                    }
                
                    // Si tous les champs sont valides ensemble, valider la connexion
                    rewind(file);
                    found = 0;
                    while (fscanf(file, "%s %s %s %s %s", med.nom, med.prenom, med.Email, med.mot_passe, med.specialite) == 5) {
                        if (strcmp(nom, med.nom) == 0 &&
                            strcmp(prenom, med.prenom) == 0 &&
                            strcmp(email, med.Email) == 0 &&
                            strcmp(password, med.mot_passe) == 0) {
                            found = 1;
                            break;
                        }
                    }
                
                    if (found) {
                        system("cls");
                        printf("Connexion réussie \n\n--------- Bienvenue Dr. %s ----------", med.nom);
                        printf("\n      Spécialité : %s\n", med.specialite);
                        fclose(file);
                        return;
                    } else {
                        if (!nom_ok) {
                            printf("❌ Nom incorrect. Veuillez le ressaisir.\n");
                            nom[0] = '\0';
                        }
                        if (!prenom_ok) {
                            printf("❌ Prénom incorrect. Veuillez le ressaisir.\n");
                            prenom[0] = '\0';
                        }
                        if (!email_ok) {
                            printf("❌ Email incorrect. Veuillez le ressaisir.\n");
                            email[0] = '\0';
                        }
                        if (!mdp_ok) {
                            printf("❌ Mot de passe incorrect. Veuillez le ressaisir.\n");
                            password[0] = '\0';
                        }
                        system("pause");
                    }
                    break;
                }
                
            default:
                printf("Choix invalide. Réessayez.\n");
                break;
        }
    } while (choix != 5); // Tant qu'on n'a pas validé

    found = 0;

    // Vérifier les informations dans le fichier
    while (fscanf(file, "%s %s %s %s %s", med.nom, med.prenom, med.Email, med.mot_passe, med.specialite) == 5) {
        if (strcmp(nom, med.nom) == 0 && strcmp(prenom, med.prenom) == 0 &&
            strcmp(email, med.Email) == 0 && strcmp(password, med.mot_passe) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        system("cls");
        printf("Connexion réussie \n\n--------- Bienvenue Dr. %s ----------", med.nom);
        printf("\n      Spécialité : %s\n", med.specialite);
    } else {
        system("cls");
        printf("Erreur sur l'identifiant : Réessayez !\n");
        goto T;
    }
}











   

    