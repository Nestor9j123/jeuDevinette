/*
Titre :Entete necessaire
Authors: KPADJA & EKOM
Ecole : EPL
Filière : LP- GL
Année Academique : 2024 - 2025


*/
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

// Enumération pour les niveaux de difficulté
typedef enum {
    NIVEAU_DEBUTANT,
    NIVEAU_MOYEN,
    NIVEAU_LEGENDE,
    NIVEAU_ULTIME,
    NIVEAU_PERSONNALISE
} Niveau;
// Structure pour représenter un score
typedef struct Score Score;
struct Score{
    char pseudo[50];
    int nbTentatives;
    float ecartType;
    char dateHeure[20];
};
typedef struct Joueur Joueur;
struct Joueur {
    char pseudo[50];
    char motDePasse[50];
};

// Fonction pour jouer une partie
void jouerPartie(const char *pseudo, Niveau niveau, int borneMax, int tentativesMax);
Niveau choisirNiveau(int *borneMax, int *tentativesMax);
float calculerEcartType(int *tentatives, int n);
void lancerJeu();
void consulterHistorique(const char *pseudo);
void consulterScores(); // Nouvelle fonction pour consulter les scores
void enregistrerScore(const Score *score); // Enregistrer un score
int verifierPseudoEtMotDePasse(const char *pseudo, const char *motDePasse);
void enregistrerJoueur(const char *pseudo, const char *motDePasse);

#endif
