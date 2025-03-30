#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ecrirePatient() {
    FILE *filePatients = fopen("patient.csv", "r");
    if (filePatients == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des patients !\n");
        return;
    }

    char ligne[100], patientNom[50], patientPrenom[50];
    int patientID, choix, found = 0;

    // Affichage de la liste des patients
    printf("\n=== Liste des Patients ===\n");
    printf("ID | Nom | Prénom\n");
    printf("----------------------\n");

    while (fgets(ligne, sizeof(ligne), filePatients)) {
        sscanf(ligne, "%d %s %s", &patientID, patientNom, patientPrenom);
        printf("%d | %s | %s\n", patientID, patientNom, patientPrenom);
    }
    
    rewind(filePatients); // Revenir au début du fichier
    
    // Sélection du patient
   
    printf("\nEntrez l'ID du patient à qui vous voulez écrire : ");
    scanf("%d", &choix);
    getchar(); // Éviter les problèmes de buffer

    while (fgets(ligne, sizeof(ligne), filePatients)) {
        sscanf(ligne, "%d %s %s", &patientID, patientNom, patientPrenom);
        if (patientID == choix) {
            found = 1;
            break;
        }
    }
    fclose(filePatients);

    if (!found) {
        printf("Patient introuvable !\n");
        printf("vérifier encore ");
        return;
    }

    // Création du fichier de messages pour ce patient
    char fichierMessages[50];
    sprintf(fichierMessages, "messages_patient_%d.txt", patientID);
    FILE *fileMessages = fopen(fichierMessages, "a");
    if (fileMessages == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des messages !\n");
        return;
    }

    // Saisie du message
    char message[200];
    printf("Entrez votre message : ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Supprimer le '\n'

    // Enregistrer le message
    fprintf(fileMessages, "Message du médecin : %s\n", message);
    fclose(fileMessages);

    printf("Message envoyé à %s %s avec succès !\n", patientPrenom, patientNom);
}




