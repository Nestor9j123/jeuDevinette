#include "jeu.h"
#include <locale.h>

int main() {
    system("color F2");
     setlocale(LC_CTYPE, "");

    printf("\t\t\t\t----------- OBJECTIF DU JEU-------- \n");
    printf("\tCe jeu vous permettra de choisir un niveau de votre choix ou de choisir une option \n\tpersonnalis� et vous permettra  de deviner un nombre entre une borne choisie \n");
    printf(" Bienvenue � vous et Veuillez entrer ces informations pour commencer le jeu merci et bonne chance \n");

    lancerJeu(); // Appelle la fonction principale du jeu
    return 0;
}
