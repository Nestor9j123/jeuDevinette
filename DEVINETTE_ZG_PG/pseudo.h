#ifndef PSEUDO_H_INCLUDED
#define PSEUDO_H_INCLUDED
#include "archives.h"

///Forcer à avoir les caractère voulu
char obligerCaractereVoulu(char caractere);
/// Fonction vérifiant si un joueur est nouveau ou pas
char nouveauOuAncien();
///Fonction vérifiant si le pseudo existe ou pas
int gererPseudo(Partie* partie);
///Fonction affichant le message correspondant aux vérifications
int afficherMessage(char nouveau, int pseudoExiste, Partie* partie);

#endif // PSEUDO_H_INCLUDED
