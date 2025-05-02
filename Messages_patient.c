#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include"gerer.h"
void Messages(int patientID){
   
        char fichierMessages[50];
        sprintf(fichierMessages, "messages_patient_%d.txt", patientID);
    
        FILE *fileMessages = fopen(fichierMessages, "r");
        if (fileMessages == NULL) {
            printf("Vous n'avez encore reçu aucun message.\n");
            return;
        }
    
        char ligne[256];
        printf("\n        === Vos messages reçus ===  \n\n\n");
        while (fgets(ligne, sizeof(ligne), fileMessages)) {
            printf("%s", ligne);
        }
    
        fclose(fileMessages);
    }

   
    
    

