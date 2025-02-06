/**
    NAME      : main.c
    PURPOSE   : Fonctions permettant de vérifier les pseudos
    AUTHOR    : ZANOU Félix Gbèdo
**/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "main.h"
#include "pseudo.h"
#include "jeu.h"
#include "archives.h"

int menuMain()
/**
    NAME        :  menuMain
    PARAMETER   : ---------
    RETURN TYPE : int
    PURPOSE     : Choisir ce que l'on veut faire
    AUTHOR      : ZANOU Félix Gbèdo
**/
{
    int choix;
    char c; // Variable pour capturer les entrées invalides

    while (1) { // Boucle infinie, on sort quand l'entrée est valide
        printf("\n------------------- MENU -------------------\n");
        printf("\t 1. Nouvelle partie\n");
        printf("\t 2. Consulter les historiques\n");
        printf("\t 3. Voir les statistiques\n");
        printf("\t 4. Quitter le jeu\n");
        printf("-------------------------------------------\n");
        printf("Entrez votre choix : ");

        if (scanf("%d", &choix) == 1) {
            if (choix >= 1 && choix <= 4) {
                return choix; // Sortie de la fonction avec une valeur correcte
            }
            printf("cas non valide! Veuillez entrer un nombre entre 1 et 4.\n");
        } else {
            printf("Entrée invalide ! Veuillez entrer un nombre.\n");
        }

        // Vider le buffer pour éviter une boucle infinie
        while ((c = getchar()) != '\n' && c != EOF);
    }
}



char gestionMenu(int choix, Partie* partie, maxBornMaxTenta* m)
/**
    NAME        : gestionMenu
    PARAMETER   : int choix, Partie* partie
    RETURN TYPE : -----------
    PURPOSE     : Satisfaire le choix
    AUTHOR      : ZANOU Félix Gbèdo
**/
{
    char outorContinuPartie;
    system("cls");
     switch (choix) {
        case 1:
            do {
                    consequenDuChoix(menu(), m);
                    genrerNombre(partie, m);
                    jeu(partie, m);
                    printf("Voulez vous recommencez? (O/N) : ");
                    outorContinuPartie= obligerCaractereVoulu(outorContinuPartie);
            }while(outorContinuPartie=='O');
            break;

        case 2:
            // Afficher l'historique
            afficherHistorique(partie->pseudo);
            break;

        case 3:
            // Afficher les statistiques
            afficherStatistiques(partie->pseudo);
            break;

        case 4:
          // Quitter le jeu
              printf("Merci d'avoir joué ! A bientôt.\n");
            exit(0);
            break;
        }
        return outorContinuPartie;
}


int main
()
/**
    NAME        : main
    PARAMETER   : --------------
    RETURN TYPE : int
    PURPOSE     : fonction principale
    AUTHOR      : ZANOU Félix Gbèdo
**/
{
    Partie* partie = (Partie*)malloc(sizeof(Partie));
    maxBornMaxTenta* m= (maxBornMaxTenta*)malloc(sizeof(maxBornMaxTenta));
    memset(partie, 0, sizeof(Partie));
    int pseudoExiste, choixMenuMain;
    char nouveau, recommencer;
    /// Debut du programme
    setlocale(LC_CTYPE, "");
    printf("------------------WELCOME TO ZANOU AND PALOUKI'S NUMBER GAME-------------------\n");
    ///recevoir la lettre voulu
    nouveau = nouveauOuAncien();
    ///gerer le pseudo
    do
    {
        pseudoExiste = gererPseudo(partie);
        genrerNombre(partie, m);
        pseudoExiste=afficherMessage(nouveau, pseudoExiste,partie);
    }while(!pseudoExiste);
    ///gerer le menu
    do
    {
        setlocale(LC_CTYPE, "");
        choixMenuMain = menuMain();
        do {
         recommencer = gestionMenu(choixMenuMain, partie, m);
        } while(recommencer == 'O');
    }while (1);

    free(partie->pseudo);
    free(partie);
    free(m);
    return 0;
}
