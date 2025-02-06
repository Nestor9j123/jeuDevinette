#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "archives.h"
#include "jeu.h"

///Fonction affichant le menu concernant le niveau de jeu
int menuMain();
///Fonction gerant le menu selon le choix fait par l'utilisateur
char gestionMenu(int choix, Partie* partie, maxBornMaxTenta* m);

#endif // MAIN_H_INCLUDED
