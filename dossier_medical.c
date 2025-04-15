#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"gerer.h"
#define MAX_L 100

void consulter_ou_creer_dossier() {
    char id[10], ligne[256];
    char nom[MAX_L], prenom[MAX_L], email[MAX_L], motdepasse[MAX_L];
    int age;
    FILE *f_patient = fopen("patient.csv", "r");

    if (!f_patient) {
        printf("Erreur : fichier patient.csv introuvable.\n");
        return;
    }

    printf("Entrez l'identifiant (id) du patient : ");
    scanf("%s", id);

    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), f_patient)) {
        char id_f[10], nom_f[MAX_L], prenom_f[MAX_L], mail[MAX_L], mdp[MAX_L];
        sscanf(ligne, "%s %s %s %s %s", id_f, nom_f, prenom_f, mail, mdp);
        if (strcmp(id, id_f) == 0) {
            strcpy(nom, nom_f);
            strcpy(prenom, prenom_f);
            trouve = 1;
            break;
        }
    }
    fclose(f_patient);

    if (!trouve) {
        printf("Aucun patient trouvé avec cet identifiant.\n");
        return;
    }

    char nomFichier[50];
    sprintf(nomFichier, "dossier_%s.txt", nom);
    FILE *dossier = fopen(nomFichier, "r");

    if (dossier) {
        printf("\n--- Dossier médical actuel de %s %s ---\n", nom, prenom);
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), dossier)) {
            printf("%s", ligne);
        }
        fclose(dossier);
    } else {
        printf("\nAucun dossier trouvé pour %s %s. Création du dossier...\n", nom, prenom);
        printf("Entrez l'âge du patient : ");
        scanf("%d", &age);

        dossier = fopen(nomFichier, "w");
        if (!dossier) {
            printf("Erreur lors de la création du dossier médical.\n");
            return;
        }

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        fprintf(dossier, "Nom : %s\n", nom);
        fprintf(dossier, "Prénom : %s\n", prenom);
        fprintf(dossier, "Âge : %d\n", age);
        fprintf(dossier, "Date de création du dossier médical: %02d/%02d/%04d %02d:%02d\n\n",
                tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

        fprintf(dossier, "Historique médical :\n");
        fclose(dossier);

        printf("Dossier médical créé.\n");
    }

    // Mise à jour de l'historique
    dossier = fopen(nomFichier, "a");
    if (!dossier) {
        printf("Erreur lors de l'ouverture du dossier pour mise à jour.\n");
        return;
    }

    char historique[1000];
    printf("\nAjoutez des informations à l'historique médical :\n");
    getchar(); // vider le buffer
    fgets(historique, sizeof(historique), stdin);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(dossier, "\n[Mise à jour du %02d/%02d/%04d %02d:%02d]\n%s",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, historique);

    fclose(dossier);
    printf("Historique mis à jour avec succès.\n");
}

