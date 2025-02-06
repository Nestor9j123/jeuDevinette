/**
NAME      : Pseudo.c
PURPOSE   : Fonctions permettant de vérifier les pseudos
AUTHOR    : ZANOU Félix Gbèdo
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "archives.h"
#include "pseudo.h"


char obligerCaractereVoulu(char caractere)
/**
    NAME        :  obligerCaractereVoulu
    PARAMETER   : --------------
    RETURN TYPE : char
    PURPOSE     : Forcer à avoir les caractère voulu
    AUTHOR      : ZANOU Félix Gbèdo
**/
{
    do
            ///obliger à avoir le caractère attendu (O ou N)
        {
            ///Lire instantenement le caractère entré
            caractere= getche();
            ///Convertir le caractère entré en majiscule
            caractere= toupper(caractere);
            if (caractere!= 'O' && caractere!='N')
            {
                //Bip sonnore (avertissement)
                printf("\a");
                //Recul
                printf("\b");
            }
            else
            {
                ///Attendre la touche entrée pour valider
                char entree;
                do
                {
                    ///Lire la touche suivantr
                    entree = getche();
                    if (entree!='\r')
                    {
                        printf("\a");
                        printf("\b \b");
                    }
                }while (entree !='\r');
            }
        }while (caractere!='O' && caractere!='N');
        return caractere;
}

char nouveauOuAncien()

/**
    NAME        : nouveauOuAncien
    PARAMETER   : --------------
    RETURN TYPE : char
    PURPOSE     : Vérifier si le joeur est nouveau ou pas
    AUTHOR      : ZANOU Félix Gbèdo
**/

{
    char nouveau;
    system("cls");
    printf("------------------WELCOME TO ZANOU AND PALOUKI'S NUMBER GAME-------------------\n");
    do
    {
        printf("Est-ce votre première fois de jouer à ce jeu? (O/N)\n");
        nouveau = obligerCaractereVoulu(nouveau);
    }while (nouveau=='O' && nouveau=='N');

    fflush(stdin);
    return nouveau;
}



int gererPseudo(Partie* partie)

/**
NAME        :   gererPseudo
PARAMETER   : partie(Partie)
RETURN TYPE : int
PURPOSE     : Vérifier si le pseudo existe ou pas
AUTHOR      : ZANOU Félix Gbèdo
**/

{
    FILE* fichier;
    char pseudo[50], verfPseudo[50], passeWord[50], verfPasseword[50], ligne[100];
    int pseudoExiste=0;
    printf("\nVeuillez entrer votre pseudo\n");
        do
        {
            fgets(pseudo, sizeof(pseudo), stdin);
            if (strcmp(pseudo, "\n")==0)
            {
                ///Bip sonnore (avertissement)
                printf("\a");
                ///Recul
                printf("\033[F");
            }
        }while(strcmp(pseudo, "\n")==0);
        ///Remplacer le retour à la ligne par \0
        pseudo[strcspn(pseudo, "\n")] = '\0';
        fflush(stdin);
        ///Copier dans la structure Partie
        strcpy(partie->pseudo, pseudo);
         printf("Veuillez entrer votre mot de passe\n");
        do
        {
            fgets(passeWord, sizeof(passeWord), stdin);
            if (strcmp(passeWord, "\n")==0)
            {
                ///Bip sonnore (avertissement)
                printf("\a");
                ///Recul
                printf("\033[F");
            }
        }while(strcmp(passeWord, "\n")==0);
        ///Remplacer le retour à la ligne par \0
        passeWord[strcspn(passeWord, "\n")] = '\0';
         strcpy(partie->passeWord, passeWord);
        fflush(stdin);
        fichier = fopen("Data.txt", "r");
        if (fichier == NULL) {
            fichier = fopen("Data.txt", "a");
            if (fichier == NULL) {
                printf("Erreur lors de l'ouverture du fichier\n");
            }
            }
        if (fichier!=NULL){

            while (fgets(ligne, sizeof(ligne), fichier) && pseudoExiste==0) {
                //Extraction du pseudo et du mot de passe
                sscanf(ligne, "%49[^\t]\t%49[^\n]", verfPseudo, verfPasseword);
                if (strcmp(pseudo, verfPseudo) == 0&& strcmp(passeWord, verfPasseword)==0) {
                    pseudoExiste = 1;
                }
            }
        }
         fclose(fichier);
         return pseudoExiste;
}


int afficherMessage(char nouveau, int pseudoExiste, Partie* partie)
    /**
        NAME        : afficherMessage
        PARAMETER   : nouveau(char), pseudoExiste(int)
        RETURN TYPE : int
        PURPOSE     : Afficher un message suivant les vérififcation
        AUTHOR      : ZANOU Félix Gbèdo
    **/
{
        FILE* fichier;
        if (nouveau == 'O') {
            if (pseudoExiste) {
                printf("Ce pseudo existe déjà ! Veuillez en entrer un autre.");
                pseudoExiste=0;
            } else if (!pseudoExiste){
                printf("Bienvenu dans notre sublime jeu %s", partie->pseudo);
                fichier = fopen("Data.txt", "a");
                fprintf(fichier, "%s\t%s\n", partie->pseudo, partie->passeWord);
                fclose(fichier);
                pseudoExiste=1;
            }
        } else if (nouveau == 'N') {
            if (pseudoExiste) {
                printf("Ravi de vous revoir, %s !\n",partie->pseudo);
            } else if (!pseudoExiste)
            {
                printf("Pseudo ou mot de passe incorects! Veuillez vérifier l'orthographe et réessayer.");
            }
        }
        else
            ///Cas non géré
        {
           printf("Entré non pris en charge! Veuillez ressayer");
        }
    return pseudoExiste;
}
