
#ifndef FICHIER_SEQUENTIEL_H
#define FICHIER_SEQUENTIEL_H

#include <stdio.h>
#include <string.h>

#define FICHIER_PSEUDOS "pseudos.txt"

int verifierPseudoExiste(const char *pseudo);
void enregistrerPseudo(const char *pseudo);
int estUnNombre(const char *chaine);

#endif
