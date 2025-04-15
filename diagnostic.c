#include <stdio.h>
#include <stdlib.h>
#include"gerer.h"
#define MAX_SYMPTOMES 59
#define MAX_CHOIX 20
#define NB_SPECIALISTES 12

// Déclaration des tableaux globaux
char *specialistes[NB_SPECIALISTES] = {
    "Cardiologue", "Pneumologue", "Nephrologue", "Chirurgien", "Anesthesiste",
    "Pediatre", "Gynecologue", "Psychiatre", "Radiologue", "Dentiste",
    "Ophtalmologue", "Sage-femme"
};

char *symptomes[MAX_SYMPTOMES] = {
    "Douleur thoracique", "Essoufflement", "Palpitations", "Hypertension", "Malaise inexplique", "Œdeme des jambes",
    "Toux persistante", "Respiration sifflante", "Douleur thoracique liee a la respiration", "Crachats sanglants",
    "Gonflement des jambes ou du visage", "Urine mousseuse ou sanglante", "Douleur lombaire", "Fatigue inexpliquee",
    "Douleur abdominale severe", "Tumeur suspecte", "Hernie", "Appendicite", "Fractures nécessitant une intervention",
    "Consultation pre-operatoire avant une chirurgie", "Allergies aux anesthesiques", "Douleur chronique necessitant une gestion",
    "Suivi médical des enfants", "Fievre persistante", "Troubles du developpement", "Infections frequentes",
    "Regles irregulieres", "Douleurs pelviennes", "Grossesse", "Infections vaginales", "Contraception", "Ménopause",
    "Dépression", "Anxiete", "Hallucinations", "Troubles du comportement", "Insomnie chronique", "Pensees suicidaires",
    "Imagerie medicale pour diagnostiquer des pathologies", "Radio", "IRM", "Scanner", "Echographie",
    "Caries", "Douleurs dentaires", "Saignement des gencives", "Dents cassees", "Mauvaise haleine persistante",
    "Baisse de vision", "Douleurs oculaires", "Rougeurs", "Infections", "Secheresse excessive", "Vision double",
    "Suivi de grossesse", "Accouchement", "Conseils en allaitement et post-partum"
};

int correspondance[MAX_SYMPTOMES] = {
    0, 0, 0, 0, 0, 0,    // Cardiologue
    1, 1, 1, 1,          // Pneumologue
    2, 2, 2, 2,          // Néphrologue
    3, 3, 3, 3, 3,       // Chirurgien
    4, 4, 4,             // Anesthésiste
    5, 5, 5, 5,          // Pédiatre
    6, 6, 6, 6, 6, 6,    // Gynécologue
    7, 7, 7, 7, 7, 7,    // Psychiatre
    8, 8, 8, 8,          // Radiologue
    9, 9, 9, 9, 9,       // Dentiste
    10, 10, 10, 10, 10, 10, // Ophtalmologue
    11, 11, 11           // Sage-femme
};

// Données utilisateur
int symptomes_choisis[MAX_CHOIX];
int nb_choix = 0;
int scores[NB_SPECIALISTES] = {0};

void afficher_menu() {
    printf("\n\n--- Menu principal ---\n\n");
    printf("1. Afficher la liste des symptomes\n\n");
    printf("2. Choisir un symptome\n\n");
    printf("3. Voir les symptomes choisis\n\n");
    printf("4. Recommander un spécialiste\n\n");
    printf("5. Sauvegarder les résultats dans un fichier\n\n");
    printf("0. Quitter\n\n");
    printf("Votre choix : ");
}

void afficher_symptomes() {
    int i;
    for (i = 0; i < MAX_SYMPTOMES; i++) {
        printf("%d. %s\n", i + 1, symptomes[i]);
    }
}

void choisir_symptome() {
    int choix;
    printf("Entrez le numero du symptome (0 pour revenir au menu) : ");
    while (scanf("%d", &choix) && choix != 0) {
        if (choix < 1 || choix > MAX_SYMPTOMES) {
            printf("Invalide. Réessayez : ");
        } else if (nb_choix < MAX_CHOIX) {
            symptomes_choisis[nb_choix++] = choix - 1;
            scores[correspondance[choix - 1]]++;
            printf("Symptome ajouté. En choisir un autre (0 pour revenir au menu) : ");
        } else {
            printf("Limite de %d symptomes atteinte.\n", MAX_CHOIX);
            break;
        }
    }
}

void afficher_choix() {
    int i;
    if (nb_choix == 0) {
        printf("Aucun symptome choisi pour l'instant.\n");
        return;
    }
    printf("\n--- Symptômes choisis ---\n");
    for (i = 0; i < nb_choix; i++) {
        printf("- %s\n", symptomes[symptomes_choisis[i]]);
    }
}

void recommander_specialiste() {
    int max = 0;
    int i;
    for ( i = 0; i < NB_SPECIALISTES; i++) {
        if (scores[i] > max) max = scores[i];
    }
    if (max == 0) {
        printf("Aucun symptome choisi. Impossible de recommander.\n");
        return;
    }
    printf("\n--- Spécialiste(s) recommandé(s) ---\n");
    for ( i = 0; i < NB_SPECIALISTES; i++) {
        if (scores[i] == max) {
            printf("- %s\n", specialistes[i]);
        }
    }
}

void sauvegarder() {
    int i;
    FILE *f = fopen("resultat_diagnostic.txt", "w");
    if (!f) {
        printf("Erreur lors de la création du fichier.\n");
        return;
    }
    fprintf(f, "--- Symptômes choisis ---\n");
    for (i = 0; i < nb_choix; i++) {
        fprintf(f, "- %s\n", symptomes[symptomes_choisis[i]]);
    }
    int max = 0;
    for ( i = 0; i < NB_SPECIALISTES; i++) {
        if (scores[i] > max) max = scores[i];
    }
    fprintf(f, "\n--- Spécialiste(s) recommandé(s) ---\n");
    for ( i = 0; i < NB_SPECIALISTES; i++) {
        if (scores[i] == max && max > 0) {
            fprintf(f, "- %s\n", specialistes[i]);
        }
    }
    fclose(f);
    printf("Résultats sauvegardés dans resultat_diagnostic.txt\n");
}

void diagnostic() {
    int option;
    printf("=== Bienvenue dans l'outil de diagnostic ===\n");

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
