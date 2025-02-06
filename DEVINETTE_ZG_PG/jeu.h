#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include "archives.h"
#include "jeu.h"

///Structure pour les variable à initialiser
typedef struct maxBornMaxTenta maxBornMaxTenta;
struct maxBornMaxTenta{
    int bornMax ;
    int nombreMaxTentative;
};
///Afficher le menu en permettant à l'utilisateur de choisir
int menu ();
///Initialisation en fonction du choix
void consequenDuChoix(int choix, maxBornMaxTenta* m);
///Generer le nombre aléatoire
void genrerNombre(Partie* partie, maxBornMaxTenta* m);
///Déroulement du jeu
void jeu(Partie* partie, maxBornMaxTenta* m);


#endif // JEU_H_INCLUDED
