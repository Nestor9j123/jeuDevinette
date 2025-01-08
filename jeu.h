#ifndef JEU_H
#define JEU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <windows.h> // Pour Sleep()
#include <conio.h>   // Pour _kbhit()

#include <time.h>
#include "ficher_random.h"
#include "ficher_sequentiel.h"

// Enum�ration pour les niveaux de difficult�
typedef enum {
    NIVEAU_DEBUTANT,
    NIVEAU_MOYEN,
    NIVEAU_LEGENDE,
    NIVEAU_ULTIME,
    NIVEAU_PERSONNALISE
} Niveau;
// Structure pour repr�senter un score
typedef struct {
    char pseudo[50];
    int nbTentatives;
    float ecartType;
    char dateHeure[20];
} Score;

// Fonction pour jouer une partie
void jouerPartie(const char *pseudo, Niveau niveau, int borneMax, int tentativesMax);
Niveau choisirNiveau(int *borneMax, int *tentativesMax);
float calculerEcartType(int *tentatives, int n);
void lancerJeu();
void consulterHistorique(const char *pseudo);
void consulterScores(); // Nouvelle fonction pour consulter les scores
void enregistrerScore(const Score *score); // Enregistrer un score

#endif
