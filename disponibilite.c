#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_L 100
#define HEURE_MIN 480    // 08:00 en minutes
#define HEURE_MAX 960    // 16:00 en minutes

int heureEnMinutes(const char* heure) {
    int h, m;
    if (sscanf(heure, "%d:%d", &h, &m) != 2) return -1;
    if (h < 0 || h > 23 || m < 0 || m > 59) return -1;
    return h * 60 + m;
}

void mettreAJourDisponibilite() {
    char email[MAX_L];
    char date_dispo[20];
    char heure_debut[10], heure_fin[10];
    char ligne[200];
    int found = 0;

    printf("=== Ajouter / Modifier Disponibilité ===\n");
    printf("Entrez votre adresse e-mail : ");
    scanf("%s", email);
    getchar();

    // Validation de la date
    int date_valide = 0;
    int jj, mm, aaaa;
    while (!date_valide) {
        printf("Entrez la date de disponibilité (format jj/mm/aaaa) : ");
        if (fgets(date_dispo, sizeof(date_dispo), stdin) == NULL) continue;
        date_dispo[strcspn(date_dispo, "\n")] = '\0';

        if (sscanf(date_dispo, "%d/%d/%d", &jj, &mm, &aaaa) != 3) {
            printf("❌ Format de date invalide. Réessayez.\n");
            continue;
        }

        struct tm dateSaisie = {0};
        dateSaisie.tm_mday = jj;
        dateSaisie.tm_mon = mm - 1;
        dateSaisie.tm_year = aaaa - 1900;

        time_t tempsSaisi = mktime(&dateSaisie);
        if (tempsSaisi == -1 || difftime(tempsSaisi, time(NULL)) < 0) {
            printf("❌ Date invalide ou déjà passée. Réessayez.\n");
            continue;
        }

        date_valide = 1;
    }

    // Validation des heures
    int minutesDebut = -1, minutesFin = -1;
    while (1) {
        printf("Heure de début (entre 08:00 et 15:59) : ");
        scanf("%s", heure_debut);
        printf("Heure de fin   (entre 08:01 et 16:00) : ");
        scanf("%s", heure_fin);

        minutesDebut = heureEnMinutes(heure_debut);
        minutesFin = heureEnMinutes(heure_fin);

        if (minutesDebut == -1 || minutesFin == -1) {
            printf("❌ Format d'heure invalide. Réessayez.\n");
        } else if (minutesDebut < HEURE_MIN || minutesDebut >= HEURE_MAX) {
            printf("❌ L'heure de début doit être entre 08:00 et 15:59.\n");
        } else if (minutesFin <= HEURE_MIN || minutesFin > HEURE_MAX) {
            printf("❌ L'heure de fin doit être entre 08:01 et 16:00.\n");
        } else if (minutesDebut >= minutesFin) {
            printf("❌ L'heure de début doit être inférieure à l'heure de fin.\n");
        } else {
            break; // Tout est valide
        }
    }

    // Mise à jour du fichier
    FILE *original = fopen("disponibilite.txt", "r");
    FILE *temp = fopen("temp_dispo.txt", "w");

    if (original) {
        while (fgets(ligne, sizeof(ligne), original)) {
            char mail_fichier[MAX_L], date_fichier[20], horaire[30];
            sscanf(ligne, "%s %s %s", mail_fichier, date_fichier, horaire);

            if (strcmp(mail_fichier, email) == 0 && strcmp(date_fichier, date_dispo) == 0) {
                fprintf(temp, "%s %s %s-%s\n", email, date_dispo, heure_debut, heure_fin);
                found = 1;
            } else {
                fputs(ligne, temp);
            }
        }
        fclose(original);
    }

    if (!found) {
        fprintf(temp, "%s %s %s-%s\n", email, date_dispo, heure_debut, heure_fin);
    }

    fclose(temp);
    remove("disponibilite.txt");
    rename("temp_dispo.txt", "disponibilite.txt");

    printf("\n✅ Disponibilité enregistrée pour le %s : %s → %s\n", date_dispo, heure_debut, heure_fin);
}

