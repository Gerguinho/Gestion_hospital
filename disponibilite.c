
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 100

void mettreAJourDisponibilite() {
    char email[MAX_L];
    char date_dispo[20];
    char heure_debut[10], heure_fin[10];
    char ligne[200];
    int found = 0;

    printf("=== Ajouter / Modifier Disponibilité ===\n");
    printf("Entrez votre adresse e-mail : ");
    scanf("%s", email);

    printf("Entrez la date de disponibilité (format jj/mm/aaaa) : ");
    scanf("%s", date_dispo);

    printf("Heure de début (ex: 08:00) : ");
    scanf("%s", heure_debut);

    printf("Heure de fin   (ex: 16:00) : ");
    scanf("%s", heure_fin);

    // Lire les lignes existantes dans un fichier temporaire
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

    // Si aucune ligne trouvée pour cet email et cette date, on ajoute une nouvelle
    if (!found) {
        fprintf(temp, "%s %s %s-%s\n", email, date_dispo, heure_debut, heure_fin);
    }

    fclose(temp);
    remove("disponibilite.txt");
    rename("temp_dispo.txt", "disponibilite.txt");

    printf("\n✅ Disponibilité enregistrée pour le %s : %s → %s\n", date_dispo, heure_debut, heure_fin);
}

