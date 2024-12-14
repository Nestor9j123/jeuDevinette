
#include "ficher_sequentiel.h"

int verifierPseudoExiste(const char *pseudo) {
    FILE *f = fopen(FICHIER_PSEUDOS, "r");
    if (!f) return 0;

    char ligne[50];
    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = '\0'; // Supprimer le \n
        if (strcmp(ligne, pseudo) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void enregistrerPseudo(const char *pseudo) {
    FILE *f = fopen(FICHIER_PSEUDOS, "a");
    if (f) {
        fprintf(f, "%s\n", pseudo);
        fclose(f);
    }
}
