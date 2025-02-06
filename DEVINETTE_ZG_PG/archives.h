#ifndef ARCHIVES_H_INCLUDED
#define ARCHIVES_H_INCLUDED


///Structure pour jouer une partie
typedef struct partie Partie;
 struct partie {
    char pseudo[50];
    char passeWord[50];
    int nbGenere;
    int tentatives[100];
    char dateHeure[25];
    int nbTentative;
    float moyenne;
    float variance;
    float ecartType;
};
///Fonction pour recuperer l'heure et la date
void recupererDateEtHeure(char *heure, int taille, Partie *p);
///Fonction pour enregistrer un pseudo
void enregistrerPartie(Partie *p);
///Fonction pour afficher l'historiques
void afficherHistorique(const char *pseudo);
///Fonction pour afficher les statistiques
void afficherStatistiques(const char *pseudo);

void toLowercase(char *str);

int comparerPseudo(const char *pseudo1, const char *pseudo2);
#endif // ARCHIVES_H_INCLUDED
