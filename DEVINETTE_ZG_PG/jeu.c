/**
NAME      : jeu.c
PURPOSE   : Fonctions permettant de jouer le jeu
AUTHOR    : ZANOU Félix Gbèdo
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "jeu.h"
#include "archives.h"


int menu()
    /**
        NAME        : menu
        PARAMETER   : --------------
        RETURN TYPE : int
        PURPOSE     : afficher un menu et permettre de choisir
        AUTHOR      : ZANOU Félix Gbèdo
**/

{
    int choix;
    system("cls");
    do {
        printf("Choisissez votre niveau :\n");
        printf("\t 1. Débutant\n");
        printf("\t 2. Moyen\n");
        printf("\t 3. Légende\n");
        printf("\t 4. Personnaliser\n");
        if (scanf("%d", &choix)!= 1) {
            ///Cas invalide
            printf("Veuillez entrer un entier.\n");
        }
        else if (choix <0 && choix >4){
            printf("Le choix doit être compris entre 1 et 4\n");
        }
        else{
            printf("Cas non géré\n");
        }
        fflush(stdin);
    } while (choix < 1 || choix > 4);
    return choix;
}

void consequenDuChoix(int choix, maxBornMaxTenta* m)

/**
NAME        : consequenceDuChoix
PARAMETER   : choix(int), m (maxBornMaxTenta)
RETURN TYPE : --------------
PURPOSE     : Initialiser les variables nécessaire au jeu en fonction du choix
AUTHOR      : ZANOU Félix Gbèdo
**/

{
    system("cls");
    switch (choix) {
        case 1:
            m->bornMax = 100;
            m->nombreMaxTentative = 10;
            break;
        case 2:
            m->bornMax = 500;
            m->nombreMaxTentative = 20;
            break;
        case 3:
            m->bornMax = 2000;
            m->nombreMaxTentative = 25;
            break;
        case 4:
            do {
                printf("Entrez la borne maximale (>=10) : ");
                if (scanf("%d", &m->bornMax) != 1 || m->bornMax < 10) {
                    printf("Entrée invalide, veuillez réessayer.\n");
                     ///Vider le tampon
                    fflush(stdin);
                }
            } while (m->bornMax < 10);

            do {
                printf("Entrez le nombre de tentatives (>=10 et <=100) : ");
                if (scanf("%d", &m->nombreMaxTentative)!= 1 || m->nombreMaxTentative < 10) {
                    printf("Entrée invalide, veuillez réessayer.\n");
                    ///Vider le tampon
                    fflush(stdin);
                }
            } while (m->nombreMaxTentative < 10 && m->nombreMaxTentative>100);
    }
}


void genrerNombre(Partie* partie, maxBornMaxTenta* m)

/**
    NAME        : genrerNombre
    PARAMETER   : partie(Partie)
    RETURN TYPE : void
    PURPOSE     : Vérifier si le joeur est nouveau ou pas
    AUTHOR      : ZANOU Félix Gbèdo
**/


{
    srand(time(NULL));
    partie->nbGenere = rand() % m->bornMax + 1;
}

void jeu(Partie* partie, maxBornMaxTenta* m)

/**
    NAME        : jeu
    PARAMETER   : partie(Partie), m(maxBornMaxTentata)
    RETURN TYPE : int
    PURPOSE     : Jouer correctemment le jeu
    AUTHOR      : ZANOU Félix Gbèdo
**/

{
    int nombreEntre, i=1, win=0;
    float moyenne = 0.0f, variance = 0.0f;
    char dateHeure[20];
    bool verifierNatureNombreEntrer;
    system("cls");
    printf("---------------QUE LE JEU COMMENCE---------------\n");
    ///Initialisation du tableau des tentatives
    printf("Le nombre mystère est prêt ! Vous pouvez commencer\n");
    recupererDateEtHeure(dateHeure, sizeof(dateHeure), partie);
     do {
            if(i<m->nombreMaxTentative)
            {
                printf("Devinez le nombre (%d/%d) : ", i, m->nombreMaxTentative);
            }
            else
            {
                printf("Dernière chance %s ! Allez mon champion, TU PEUX FAIRE : ", partie->pseudo);
            }

        verifierNatureNombreEntrer = scanf("%d", &nombreEntre);
        if (verifierNatureNombreEntrer)
        {
            i++;
            moyenne += nombreEntre;
            partie->tentatives[i-1]= nombreEntre;
            if (nombreEntre==partie->nbGenere)
                {
                    win=1;
                    verifierNatureNombreEntrer=false;
                    if (i<=3)
                    {
                    printf("Félicitation! Super voyant.\n");
                    }
                    else if (i>=4 && i<=6)
                    {
                        printf("félicitation! Sage voyant.\n");
                    }
                    else if (i>=7 && i<=9)
                    {
                        printf("Félicitations! Apprenti voyant.\n");
                    }
                    else
                    {
                        printf("Humm enfin Vous avez trouvé! voyant pusillanime.\n");
                    }
                }
                else if (nombreEntre< partie->nbGenere)
                {
                    ///Eviter de sortir prématurement de la boucle
                    if (i<=m->nombreMaxTentative)
                    {
                        verifierNatureNombreEntrer=false;
                    }
                    printf("Oops! Plus grand.\n");
                }
                else
                {
                    ///Eviter de sortir prématurement de la boucle
                    if (i<=m->nombreMaxTentative)
                    {
                        verifierNatureNombreEntrer=false;
                    }
                    printf("Oops! plus petit.\n");
                }
                fflush(stdin);
        }else
        {
            printf("Cas non gérer! Veuillez entrer un entier svp\n");
            fflush(stdin);
        }

    } while (i <= m->nombreMaxTentative && win==0 && verifierNatureNombreEntrer==false);
    if (win==0) {
        printf("GAME OVER! Le nombre était %d.\n", partie->nbGenere);
    }
    ///calculer la moyenne
    moyenne /=i;
    ///enregistrer la moyenne
    partie->moyenne = moyenne;
    ///Calculer la variance
    for (int j = 0; j < i; j++) {
        variance += pow(partie->tentatives[j] - moyenne, 2);
    }
    variance /= i;
    ///enregistrer variance
    partie->variance = variance;
    partie->ecartType = sqrt(variance);
    ///Enregistrer le nombre de tentatives
    partie->nbTentative = i;
    ///Enregistrer la partie
    enregistrerPartie(partie);
}
