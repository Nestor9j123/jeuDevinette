#ifndef JEU_H
#define JEU_H

#include <time.h>
#include "ficher_random.h"
#include "ficher_sequentiel.h"

// Enumération pour les niveaux de difficulté
typedef enum {
    NIVEAU_DEBUTANT,
    NIVEAU_MOYEN,
    NIVEAU_LEGENDE,
    NIVEAU_ULTIME,
    NIVEAU_PERSONNALISE
} Niveau;

// Fonction pour jouer une partie
void jouerPartie(const char *pseudo, Niveau niveau, int borneMax, int tentativesMax);
Niveau choisirNiveau(int *borneMax, int *tentativesMax);
void lancerJeu();

#endif
