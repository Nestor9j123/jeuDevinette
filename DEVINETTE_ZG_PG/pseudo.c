/**
NAME      : Pseudo.c
PURPOSE   : Fonctions permettant de v�rifier les pseudos
AUTHOR    : ZANOU F�lix Gb�do
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
    PURPOSE     : Forcer � avoir les caract�re voulu
    AUTHOR      : ZANOU F�lix Gb�do
**/
{
    do
            ///obliger � avoir le caract�re attendu (O ou N)
        {
            ///Lire instantenement le caract�re entr�
            caractere= getche();
            ///Convertir le caract�re entr� en majiscule
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
                ///Attendre la touche entr�e pour valider
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
    PURPOSE     : V�rifier si le joeur est nouveau ou pas
    AUTHOR      : ZANOU F�lix Gb�do
**/

{
    char nouveau;
    system("cls");
    printf("------------------WELCOME TO ZANOU AND PALOUKI'S NUMBER GAME-------------------\n");
    do
    {
        printf("Est-ce votre premi�re fois de jouer � ce jeu? (O/N)\n");
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
PURPOSE     : V�rifier si le pseudo existe ou pas
AUTHOR      : ZANOU F�lix Gb�do
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
        ///Remplacer le retour � la ligne par \0
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
        ///Remplacer le retour � la ligne par \0
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
        PURPOSE     : Afficher un message suivant les v�rififcation
        AUTHOR      : ZANOU F�lix Gb�do
    **/
{
        FILE* fichier;
        if (nouveau == 'O') {
            if (pseudoExiste) {
                printf("Ce pseudo existe d�j� ! Veuillez en entrer un autre.");
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
                printf("Pseudo ou mot de passe incorects! Veuillez v�rifier l'orthographe et r�essayer.");
            }
        }
        else
            ///Cas non g�r�
        {
           printf("Entr� non pris en charge! Veuillez ressayer");
        }
    return pseudoExiste;
}
