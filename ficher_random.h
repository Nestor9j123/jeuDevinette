/*
Titre :Entete et prototype  pour les fichier acces random
Authors: KPADJA & EKOM
Ecole : EPL
Filière : LP- GL
Année Academique : 2024 - 2025


*/
#ifndef FICHIER_RANDOM_H
#define FICHIER_RANDOM_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_TENTATIVES 100
#define FICHIER_HISTORIQUE "historique.dat"

typedef struct {
    char pseudo[50];
    char dateHeure[50];
    int tentatives[MAX_TENTATIVES];
    int nbTentatives;
    float ecartType;
} Partie;

void enregistrerPartie(Partie *partie);
void consulterHistorique(const char *pseudo);

#endif
