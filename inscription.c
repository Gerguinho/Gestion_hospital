#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include"gerer.h"

int getLastID() {
    FILE *f = fopen(FILE_patient, "r");
    if (f == NULL) return 0;  // Si le fichier n'existe pas, on commence à ID 1

    char ligne[300];
    int lastID = 0, tempID=0;
    
    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%*[^,],%*[^,],%*d/%*d/%*d,%*[^,],%*s", &tempID);
        lastID = tempID;
    }
    
    fclose(f);
    return lastID;
}





void saisir_mot_de_passe(char *mot_de_passe, int taille_max) {
    int i = 0;
    char c;

    printf("Mot de passe : ");

    while (1) {
        c = getch(); // Lire un caractère sans l'afficher

        if (c == 13) { // Entrée
            break;
        }

        if (c == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (i < taille_max - 1) {
            mot_de_passe[i++] = c;
            printf("*");
        }
    }

    mot_de_passe[i] = '\0';
    printf("\n");
}

void inscription() {
    User us;
    us.id = getLastID() + 1;

    // Saisie des informations utilisateur
    printf("Entrez votre nom : ");
    fgets(us.nom, MAX_L, stdin);
    us.nom[strcspn(us.nom, "\n")] = '\0';
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
    fgets(us.Email, MAX_L, stdin);
    us.Email[strcspn(us.Email, "\n")] = '\0';
    sleep(1);

M:
    printf("Entrez votre mot de passe\n");
    saisir_mot_de_passe(us.mot_passe, MAX_L);
    sleep(1);
    printf("Confirmez votre mot de passe\n");
    saisir_mot_de_passe(us.mot_passe_confirm, MAX_L);
    sleep(1);

    if (strcmp(us.mot_passe, us.mot_passe_confirm) != 0) {
        printf("Erreur : Les mots de passe ne correspondent pas.\n");
        goto M;
    } else {
        system("cls");
        printf("✅ mot de passe confirmé\n");
    }

    // Ouvrir le fichier en mode ajout (a+)
    FILE *f = fopen(FILE_patient, "a+");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    // Écriture dans le fichier CSV (format d'origine conservé)
    fprintf(f, "%d %s %s %s %s\n", us.id, us.nom, us.prenom, us.Email, us.mot_passe);

    printf("\n✅ Enregistrement effectué avec succès !\n");

    fclose(f);
}
