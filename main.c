#include "jeu.h"
#include <locale.h>

int main() {
    setlocale(LC_CTYPE, "");
    lancerJeu(); // Appelle la fonction principale du jeu depuis menu.c
    return 0;
}
