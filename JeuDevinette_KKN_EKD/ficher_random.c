/*
Titre :fichier a accès random
Authors: KPADJA & EKOM
Ecole : EPL



*/

#include "ficher_random.h"

void enregistrerPartie(Partie *partie) {
    FILE *f = fopen(FICHIER_HISTORIQUE, "ab");
    if (f) {
        fwrite(partie, sizeof(Partie), 1, f);
        fclose(f);
    }
}

void consulterHistorique(const char *pseudo) {
    FILE *f = fopen(FICHIER_HISTORIQUE, "rb");
    if (!f) {
        printf("Erreur : le fichier historique est introuvable.\n");
        return;
    }

    Partie partie;
    int trouve = 0;

    printf("\nHistorique des parties pour le pseudo '%s' :\n", pseudo);
    while (fread(&partie, sizeof(Partie), 1, f)) {
        if (strcmp(partie.pseudo, pseudo) == 0) {
            trouve = 1;
            printf("Date/Heure : %s\n", partie.dateHeure);
            printf("Tentatives : ");
            for (int i = 0; i < partie.nbTentatives; i++) {
                printf("%d ", partie.tentatives[i]);
            }
            printf("\nNombre de tentatives : %d\n", partie.nbTentatives);
            printf("Ecart-type : %.2f\n", partie.ecartType);
            printf("------------------------------------------\n");
        }
    }

    if (!trouve) {
        printf("Aucune partie trouvée pour ce pseudo.\n");
    }

    fclose(f);
}

