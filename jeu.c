#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include "jeu.h"

int genererNombre(int borneMax) {
    return rand() % borneMax + 1; // G�n�re un nombre entre 1 et borneMax
}
Niveau choisirNiveau(int *borneMax, int *tentativesMax) {
    int choix;
    printf("\nChoisissez un niveau :\n");
    printf("1. D�butant (1-10, 5 tentatives)\n");
    printf("2. Moyen (1-50, 10 tentatives)\n");
    printf("3. L�gende (1-100, 15 tentatives)\n");
    printf("4. Ultime (1-1000, 20 tentatives)\n");
    printf("5. Personnalis�\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            *borneMax = 10;
            *tentativesMax = 5;
            return NIVEAU_DEBUTANT;
        case 2:
            *borneMax = 50;
            *tentativesMax = 10;
            return NIVEAU_MOYEN;
        case 3:
            *borneMax = 100;
            *tentativesMax = 15;
            return NIVEAU_LEGENDE;
        case 4:
            *borneMax = 1000;
            *tentativesMax = 20;
            return NIVEAU_ULTIME;
        case 5:
            printf("Entrez la borne maximale : ");
            while (scanf("%d", borneMax) != 1 || *borneMax <= 0) {
                printf("Veuillez entrer un nombre valide : ");
                while (getchar() != '\n'); // Vider le buffer
            }
            printf("Entrez le nombre maximum de tentatives : ");
            while (scanf("%d", tentativesMax) != 1 || *tentativesMax <= 0) {
                printf("Veuillez entrer un nombre valide : ");
                while (getchar() != '\n'); // Vider le buffer
            }
            return NIVEAU_PERSONNALISE;
        default:
            printf("Choix invalide. Niveau d�butant s�lectionn� par d�faut.\n");
            *borneMax = 10;
            *tentativesMax = 5;
            return NIVEAU_DEBUTANT;
    }
}

void afficherMessageFelicitations(int nbTentatives) {
    if (nbTentatives <= 3) {
        printf("F�licitations ! Vous �tes un super voyant !\n");
    } else if (nbTentatives <= 6) {
        printf("Bravo ! Vous �tes un sage voyant.\n");
    } else if (nbTentatives <= 9) {
        printf("Bien jou� ! Vous �tes un apprenti voyant.\n");
    } else {
        printf("Vous �tes un voyant pusillanime. Continuez � vous entra�ner !\n");
    }
}

void jouerPartie(const char *pseudo, Niveau niveau, int borneMax, int tentativesMax) {
    Partie partie;
    strcpy(partie.pseudo, pseudo);

    time_t now = time(NULL);
    strftime(partie.dateHeure, sizeof(partie.dateHeure), "%Y-%m-%d %H:%M:%S", localtime(&now));

    int nombreADeviner = genererNombre(borneMax);
    int tentative, nbTentatives = 0;

    printf("Devinez le nombre (entre 1 et %d). Vous avez %d tentatives :\n", borneMax, tentativesMax);
    while (nbTentatives < tentativesMax) {
        printf("Tentative %d : ", nbTentatives + 1);
        if (scanf("%d", &tentative) != 1) {
            printf("Entr�e invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); // Vider le buffer
            continue;
        }

        partie.tentatives[nbTentatives++] = tentative;

        if (tentative == nombreADeviner) {
            printf("F�licitations ! Vous avez devin� le nombre en %d tentatives.\n", nbTentatives);
            afficherMessageFelicitations(nbTentatives);
            break;
        } else if (tentative < nombreADeviner) {
            printf("Plus grand !\n");
        } else {
            printf("Plus petit !\n");
        }
    }

    if (nbTentatives >= tentativesMax) {
        printf("Vous avez �puis� vos %d tentatives. Le nombre �tait %d. Bonne chance la prochaine fois !\n", tentativesMax, nombreADeviner);
    }

float calculerEcartType(int *tentatives, int n) {
    if (n == 0) return 0.0;

    float somme = 0, moyenne, variance = 0;
    for (int i = 0; i < n; i++) {
        somme += tentatives[i];
    }
    moyenne = somme / n;

    for (int i = 0; i < n; i++) {
        variance += pow(tentatives[i] - moyenne, 2);
    }
    return sqrt(variance / n);
}
    partie.nbTentatives = nbTentatives;
    partie.ecartType = calculerEcartType(partie.tentatives, nbTentatives);
    enregistrerPartie(&partie);
}
void lancerJeu() {
    setlocale(LC_ALL, "fr_FR.UTF-8");
    srand(time(NULL));

    char pseudo[50];
    printf("Entrez votre pseudo : ");
    scanf("%49s", pseudo);

    if (verifierPseudoExiste(pseudo)) {
        printf("Bienvenue de retour, %s !\n", pseudo);
    } else {
        printf("Nouveau joueur d�tect�. Enregistrement...\n");
        enregistrerPseudo(pseudo);
    }

    Niveau niveau;
    int borneMax, tentativesMax;
    char rejouer = 'y'; // Variable pour g�rer la rejouabilit�
    int choix;

    do {
        printf("\nMenu :\n");
        printf("1. Choisir un niveau et commencer une partie\n");
        printf("2. Consulter l'historique\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        fflush(stdin);
        scanf("%d", &choix);

        switch (choix) {
            case 1: // Choix d'un niveau et lancement imm�diat
                niveau = choisirNiveau(&borneMax, &tentativesMax);
                do {
                    jouerPartie(pseudo, niveau, borneMax, tentativesMax);
                    printf("Voulez-vous rejouer avec le m�me niveau ? (y/n) : ");
                    fflush(stdin);
                    scanf(" %c", &rejouer);
                } while (rejouer == 'y' || rejouer == 'Y');
                break;

            case 2: // Consultation de l'historique
                consulterHistorique(pseudo);
                break;

            case 3: // Quitter
                printf("Merci d'avoir jou� ! � bient�t !\n");
                return;

            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choix != 3);
}
