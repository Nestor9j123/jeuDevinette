/*
Titre :Entete et prototype pour les fichier acces sequentiel
Authors: KPADJA & EKOM
Ecole : EPL
Fili�re : LP- GL
Ann�e Academique : 2024 - 2025


*/
#ifndef FICHIER_SEQUENTIEL_H
#define FICHIER_SEQUENTIEL_H

#include <stdio.h>
#include <string.h>

#define FICHIER_PSEUDOS "pseudos.txt"
#define FICHIER_SCORES "scores.txt"

int verifierPseudoExiste(const char *pseudo);
void enregistrerPseudo(const char *pseudo);
int estUnNombre(const char *chaine);

#endif
