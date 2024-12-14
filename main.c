#include <locale.h>
#include "ficher_sequentiel.h"
#include "jeu.h"
#include "ficher_random.h"

int main() {
    setlocale(LC_CTYPE, ""); // Gestion des accents
    srand(time(NULL));

    char pseudo[50];
    printf("Entrez votre pseudo : ");
    scanf("%s", pseudo);

    if (verifierPseudoExiste(pseudo)) {
        printf("Bon   retour, %s !\n", pseudo);
    } else {
        printf("Nouveau joueur détecté. Enregistrement...\n");
        enregistrerPseudo(pseudo);
    }

    char choix;
    do {
        printf("\nMenu :\n");
        printf("1. Jouer une partie\n");
        printf("2. Consulter l'historique\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        while (getchar() != '\n'); // Vider le buffer
        choix = getchar();

        switch (choix) {
            case '1':
                jouerPartie(pseudo);
                break;
            case '2':
                consulterHistorique(pseudo);
                break;
            case '3':
                printf("Merci d'avoir joué !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != '3');

    return 0;
}
