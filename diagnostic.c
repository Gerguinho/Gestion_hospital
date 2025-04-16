#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMPTOMES 40
#define MAX_CHOIX 20
#define NB_SPECIALISTES 10

// Spécialistes
char *specialistes[NB_SPECIALISTES] = {
    "Cardiologue", "Pneumologue", "Endocrinologue", "Infectiologue", "Neurologue",
    "Gastro-entérologue", "Dermatologue", "Psychiatre", "Ophtalmologue", "Gynécologue"
};

// Symptômes
char *symptomes[MAX_SYMPTOMES] = {
    "Douleur thoracique", "Essoufflement au repos ou à l’effort", "Palpitations cardiaques",
    "Hypertension persistante", "Toux persistante avec fièvre", "Expectorations sanglantes",
    "Fièvre prolongée", "Perte de poids involontaire", "Vision floue ou altérée",
    "Faim et soif excessive", "Fatigue chronique", "Engourdissement ou picotement",
    "Convulsions", "Maux de tête fréquents", "Nausées/vomissements réguliers",
    "Diarrhée prolongée", "Douleurs abdominales intenses", "Lésions cutanées anormales",
    "Démangeaisons sévères", "Sautes d'humeur fréquentes", "Insomnie sévère",
    "Pensées suicidaires", "Déformation de la vision des couleurs", "Douleur oculaire aiguë",
    "Troubles menstruels", "Douleurs pelviennes chroniques", "Grossesse suspectée",
    "Perte de conscience", "Gonflement des jambes", "Fièvre après un voyage",
    "Saignement anormal", "Jaunisse", "Difficulté à respirer", "Taches rouges sur la peau",
    "Douleurs articulaires", "Tremblements involontaires", "Douleur intense au dos",
    "Trouble de la mémoire", "Infections urinaires fréquentes", "Sécheresse vaginale"
};

// Correspondance symptômes → spécialistes
int correspondance[MAX_SYMPTOMES] = {
    0, 1, 0, 0, 1, 1, 3, 3, 8, 2, 2, 4, 4, 0, 5, 5, 5, 6, 6, 7,
    7, 7, 8, 8, 9, 9, 9, 4, 0, 3, 5, 5, 1, 3, 4, 4, 4, 4, 5, 9
};

int symptomes_choisis[MAX_CHOIX];
int nb_choix = 0;
int scores[NB_SPECIALISTES] = {0};

// Affichage du menu principal
void afficher_menu() {
    printf("\n---- Menu Principal ----\n");
    printf("1. Afficher les symptômes\n");
    printf("2. Choisir un symptôme\n");
    printf("3. Voir les symptômes choisis\n");
    printf("4. Recommander un spécialiste\n");
    printf("5. Sauvegarder les résultats\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

// Afficher les symptômes disponibles
void afficher_symptomes() {
    for (int i = 0; i < MAX_SYMPTOMES; i++) {
        printf("%d. %s\n", i + 1, symptomes[i]);
    }
}

// Choisir un symptôme
void choisir_symptome() {
    int choix;
    printf("Entrez le numéro du symptôme (0 pour revenir) : ");
    while (scanf("%d", &choix) && choix != 0) {
        if (choix < 1 || choix > MAX_SYMPTOMES) {
            printf("Numéro invalide. Réessayez : ");
        } else if (nb_choix < MAX_CHOIX) {
            symptomes_choisis[nb_choix++] = choix - 1;
            scores[correspondance[choix - 1]]++;
            printf("Symptôme ajouté. En choisir un autre (0 pour revenir) : ");
        } else {
            printf("Limite de symptômes atteinte.\n");
            break;
        }
    }
}

// Afficher les symptômes choisis
void afficher_choix() {
    if (nb_choix == 0) {
        printf("Aucun symptôme choisi.\n");
        return;
    }
    printf("\n--- Symptômes choisis ---\n");
    for (int i = 0; i < nb_choix; i++) {
        printf("- %s\n", symptomes[symptomes_choisis[i]]);
    }
}

// Afficher les disponibilités d'un médecin donné
void afficher_disponibilite(const char *email_medecin) {
    FILE *f = fopen("disponibilite.txt", "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir disponibilite.txt\n");
        return;
    }

    char ligne[256];
    int trouve = 0;
    printf("  Disponibilités :\n");

    // Lire et afficher les disponibilités
    while (fgets(ligne, sizeof(ligne), f)) {
        char email[100], date[20], plage_horaire[20];
        sscanf(ligne, "%s %s %s", email, date, plage_horaire);

        if (strcmp(email, email_medecin) == 0) {
            printf("    - %s entre %s\n", date, plage_horaire);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("    Aucune disponibilité enregistrée pour ce médecin.\n");
    }

    fclose(f);
}

// Afficher les médecins disponibles pour une spécialité donnée
void afficher_medecins_specialiste(const char *specialite) {
    FILE *f = fopen("Medecin.csv", "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir Medecin.csv\n");
        return;
    }

    char ligne[256];
    int trouve = 0;

    printf("\nMédecins disponibles pour la spécialité \"%s\" :\n", specialite);

    while (fgets(ligne, sizeof(ligne), f)) {
        char nom[50], prenom[50], email[100], motdepasse[50], spec[50];
        sscanf(ligne, "%s %s %s %s %s", nom, prenom, email, motdepasse, spec);

        if (strcmp(spec, specialite) == 0) {
            printf("- Dr %s %s (Email : %s)\n", nom, prenom, email);
            afficher_disponibilite(email);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun médecin trouvé pour cette spécialité.\n");
    }

    fclose(f);
}

// Recommander un spécialiste en fonction des symptômes choisis
void recommander_specialiste() {
    int max = 0, index_max = -1;
    for (int i = 0; i < NB_SPECIALISTES; i++) {
        if (scores[i] > max) {
            max = scores[i];
            index_max = i;
        }
    }

    if (max == 0) {
        printf("Aucun symptôme choisi. Recommandation impossible.\n");
        return;
    }

    printf("\n--- Recommandation ---\n");
    for (int i = 0; i < nb_choix; i++) {
        int indice = symptomes_choisis[i];
        printf("Pour le symptôme \"%s\" consultez un(e) %s.\n", symptomes[indice], specialistes[correspondance[indice]]);
    }

    char reponse;
    printf("\nSouhaitez-vous prendre rendez-vous avec un(e) %s ? (o/n) : ", specialistes[index_max]);
    scanf(" %c", &reponse);

    if (reponse == 'o' || reponse == 'O') {
        afficher_medecins_specialiste(specialistes[index_max]);
    } else {
        printf("D'accord, pas de rendez-vous pour le moment.\n");
    }
}

// Sauvegarder les résultats du diagnostic
void sauvegarder() {
    FILE *f = fopen("resultat_diagnostic.txt", "w");
    if (!f) {
        printf("Erreur d'écriture du fichier.\n");
        return;
    }

    fprintf(f, "--- Symptômes choisis ---\n");
    for (int i = 0; i < nb_choix; i++) {
        fprintf(f, "- %s\n", symptomes[symptomes_choisis[i]]);
    }

    fprintf(f, "\n--- Recommandations ---\n");
    for (int i = 0; i < nb_choix; i++) {
        int indice = symptomes_choisis[i];
        fprintf(f, "Pour \"%s\" → %s\n", symptomes[indice], specialistes[correspondance[indice]]);
    }

    fclose(f);
    printf("Résultats sauvegardés dans resultat_diagnostic.txt\n");
}

// Fonction principale pour lancer l'outil de diagnostic médical
void diagnostic() {
    int option;
    printf("=== Outil de Diagnostic Médical ===\n");
    do {
        afficher_menu();
        scanf("%d", &option);
        switch (option) {
            case 1: afficher_symptomes(); break;
            case 2: choisir_symptome(); break;
            case 3: afficher_choix(); break;
            case 4: recommander_specialiste(); break;
            case 5: sauvegarder(); break;
            case 0: printf("Fermeture du programme...\n"); break;
            default: printf("Option invalide.\n"); break;
        }
    } while (option != 0);
}


