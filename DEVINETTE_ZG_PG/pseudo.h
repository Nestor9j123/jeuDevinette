#ifndef PSEUDO_H_INCLUDED
#define PSEUDO_H_INCLUDED
#include "archives.h"

///Forcer � avoir les caract�re voulu
char obligerCaractereVoulu(char caractere);
/// Fonction v�rifiant si un joueur est nouveau ou pas
char nouveauOuAncien();
///Fonction v�rifiant si le pseudo existe ou pas
int gererPseudo(Partie* partie);
///Fonction affichant le message correspondant aux v�rifications
int afficherMessage(char nouveau, int pseudoExiste, Partie* partie);

#endif // PSEUDO_H_INCLUDED
