#include "jeu.h"

int genererNombre(int max) {
    return rand() % max + 1;
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

void afficherMessageFelicitations(int nbTentatives) {
    if (nbTentatives <= 3) {
        printf("Félicitations ! Vous êtes un super voyant !\n");
    } else if (nbTentatives <= 6) {
        printf("Bravo ! Vous êtes un sage voyant.\n");
    } else if (nbTentatives <= 9) {
        printf("Bien joué ! Vous êtes un apprenti voyant.\n");
    } else {
        printf("Vous êtes un voyant pusillanime. Continuez à vous entraîner !\n");
    }
}

void jouerPartie(const char *pseudo) {
    Partie partie;
    strcpy(partie.pseudo, pseudo);

    time_t now = time(NULL);
    strftime(partie.dateHeure, sizeof(partie.dateHeure), "%Y-%m-%d %H:%M:%S", localtime(&now));

    int maxNombre, nombreADeviner, tentative, nbTentatives = 0;
    printf("Entrez la borne maximale pour le nombre à deviner : ");
    while (scanf("%d", &maxNombre) != 1 || maxNombre <= 0) {
        printf("Veuillez entrer un nombre valide !\n");
        while (getchar() != '\n'); // Vider le buffer
    }

    nombreADeviner = genererNombre(maxNombre);

    printf("Devinez le nombre (entre 1 et %d) : ", maxNombre);
    while (nbTentatives < MAX_TENTATIVES) {
        if (scanf("%d", &tentative) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');
            continue;
        }

        partie.tentatives[nbTentatives++] = tentative;

        if (tentative == nombreADeviner) {
            printf("Félicitations ! Vous avez deviné le nombre en %d tentatives.\n", nbTentatives);
            afficherMessageFelicitations(nbTentatives);
            break;
        } else if (tentative < nombreADeviner) {
            printf("Plus grand !\n");
        } else {
            printf("Plus petit !\n");
        }
    }

    partie.nbTentatives = nbTentatives;
    partie.ecartType = calculerEcartType(partie.tentatives, nbTentatives);
    enregistrerPartie(&partie);
}

