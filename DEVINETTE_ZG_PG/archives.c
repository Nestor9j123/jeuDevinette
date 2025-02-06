/**
NAME      : archive.c
PURPOSE   : Fonctions permettant de vérifier les pseudos
AUTHOR    : ZANOU Félix Gbèdo
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "archives.h"


void recupererDateEtHeure(char *heure, int taille, Partie *partie)

/**
    NAME        : recupererDateEtHeure
    PARAMETER   : heure (char*), taille(int), partie (*Partie)
    RETURN TYPE : ---------------
    PURPOSE     : Récuperer l'heure et la date
    AUTHOR      : ZANOU Félix Gbèdo
**/

 {
    time_t temps = time(NULL);
    struct tm *tempsLocal = localtime(&temps);
    ///Vérification de la récupération et de la conversion de la date
    if (temps == -1) {
        printf("Erreur lors de la récupération de l'heure\n");
    }else {
        if (tempsLocal == NULL) {
        printf("Erreur lors de la conversion de l'heure\n");
        }
        else
        {
            if (strftime(heure, taille, "%d-%m-%Y %H:%M:%S", tempsLocal) == 0){
            printf("Erreur lors du formatage de la date et de l'heure\n");
            }
        }
    }
    ///copier la date Date et heure de la partie dans la structure
    strncpy(partie->dateHeure, heure, taille);
    /// S'assurer que la chaîne est terminée par un '\0'
    partie->dateHeure[taille - 1] = '\0';
}



void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int comparerPseudo(const char *pseudo1, const char *pseudo2) {
    char temp1[50], temp2[50];
    strcpy(temp1, pseudo1);
    strcpy(temp2, pseudo2);
    toLowercase(temp1);
    toLowercase(temp2);
    return strcmp(temp1, temp2);
}


void enregistrerPartie(Partie *partie)

/**
    NAME        : enregistrerParti
    PARAMETER   : partie(Partie)
    RETURN TYPE : ---------
    PURPOSE     : enregistrer la partie jouer
    AUTHOR      : ZANOU Félix Gbèdo
**/

 {
    setlocale(LC_CTYPE, "");
    FILE *fichier = fopen("archive.dat", "ab"); // Append pour ne pas écraser le fichier existant
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }else{
           if (fwrite(partie, sizeof(Partie), 1, fichier) != 1) {
        printf("Erreur lors de l'enregistrement de la partie\n");
    } else {
        printf("Partie enregistrée avec succès\n");
    }
        }
    fclose(fichier);
}


void afficherHistorique(const char *pseudo)
/**
    NAME        : afficherHistorique
    PARAMETER   : pseudo (const char)
    RETURN TYPE : ------
    PURPOSE     : Afficher l'historique
    AUTHOR      : ZANOU Félix Gbèdo
**/

 {
    int existance = 0;
    setlocale(LC_CTYPE, "");
    FILE *fichier = fopen("archive.dat", "rb");
    if (fichier==NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }else
    {
        Partie partie;
        while (fread(&partie, sizeof(Partie), 1, fichier)==1) {
        ///Vérifier si les pseudo sont les mêmes
        if (comparerPseudo(partie.pseudo, pseudo) == 0) {
            existance++;
            printf("--------------- HISTORIQUE PARTIE %d ----------------\n", existance);
            printf("Date et Heure : %s\n", partie.dateHeure);
            printf("Nombre mysterieux : %d\n", partie.nbGenere);
            printf("Nombre de tentatives : %d\n", partie.nbTentative);
            if (partie.tentatives) {
                for (int i = 0; i < partie.nbTentative; i++) {
                    printf("Tentative %d : %d\n", i + 1, partie.tentatives[i]);
                }
            }
            printf("---------------------------------------------------\n");
        }
    }
    }
    fclose(fichier);
    if (existance == 0) {
        printf("Désolz, vous n'avez jamais joué à ce jeu.\n");
    } else {
        printf("\nNombre total de parties jouées : %d\n", existance);
    }
}


void afficherStatistiques(const char *pseudo)
/**
    NAME        : afficherStatistiques
    PARAMETER   : pseudo (const char)
    RETURN TYPE : -------------
    PURPOSE     : affiche les statistiques
    AUTHOR      : ZANOU Félix Gbèdo
**/
{
    int existance = 0;
    float Moyenne_globale = 0.0f, variance_globale = 0.0f, Ecartype_globale = 0.0f;
    setlocale(LC_CTYPE, "");
    FILE *fichier = fopen("archive.dat", "rb");
    if (fichier==NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }else
    {
    Partie partie;
    while (fread(&partie, sizeof(Partie), 1, fichier)==1) {
        if (comparerPseudo(partie.pseudo, pseudo) == 0) {
            existance++;
            Moyenne_globale += partie.moyenne;
            variance_globale += partie.variance;
            Ecartype_globale += partie.ecartType;

            printf("--------------- STATISTIQUES PARTIE %d ----------------\n", existance);
            printf("Moyenne       : %.2f\n", partie.moyenne);
            printf("Variance      : %.2f\n", partie.variance);
            printf("écart-Type    : %.2f\n", partie.ecartType);
            printf("------------------------------------------------------\n");
            }
        }
    }
    fclose(fichier);
    if (existance == 0) {
        printf("Désolé, vous n'avez jamais joué à ce jeu.\n");
    } else {
        printf("************ STATISTIQUES GLOBALES *****************\n");
        printf("Moyenne Globale  : %.2f\n", Moyenne_globale / existance);
        printf("Variance Globale : %.2f\n", variance_globale / existance);
        printf("écart-Type Global: %.2f\n", Ecartype_globale / existance);
        printf("Nombre total de parties jouées : %d\n", existance);
        printf("*****************************************************\n");
    }
}
