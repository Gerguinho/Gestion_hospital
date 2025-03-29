#ifndef Gerer_H
#define Gerer_H
#define MAX_L 100  // Taille max des chaînes de caractères

//void register_user_connect();// enregeristrer un patient pour la 1er connection

void inscription();//personnes possèdant deja un compte
void medecin();//liste des médecins
void fonction_principale();// où la grande partie du code se passe 
void ordonnance();
void connection();
//void choix_medecin1();// fonction où se retrouve l'utilisateur après avoir choisi l'option médecin
void medecin();// après que le médecin se soit connecté a son compte
void patient();// fonction où se retrouve l'utilisateur après avoir choisi l'option patient 
void essai_gratuit();
void abonnement();
void connection_patient();
extern const char *FILE_patient;
extern const char *FILE_medecin;

// Définition d'une structure pour stocker les infos d'un utilisateur
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    char nom[MAX_L];
    char prenom[MAX_L];
    Date date_nais;
    char Email[MAX_L];
    char mot_passe[MAX_L];
    char mot_passe_confirm[MAX_L];
} User;

#endif