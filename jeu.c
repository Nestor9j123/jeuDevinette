
#include "jeu.h"

// G�n�re un nombre al�atoire entre 1 et borneMax
int genererNombre(int borneMax) {
    return rand() % borneMax + 1;
}

// Fonction pour choisir le niveau et les param�tres
Niveau choisirNiveau(int *borneMax, int *tentativesMax) {
    int choix;
    printf("\nChoisissez un niveau :\n");
    printf("1. D�butant (1-10, 5 tentatives)\n");
    printf("2. Moyen (1-50, 8 tentatives)\n");
    printf("3. L�gende (1-100, 15 tentatives)\n");
    printf("4. Ultime (1-1000, 10 tentatives)\n");
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
            *tentativesMax = 8;
            return NIVEAU_MOYEN;
        case 3:
            *borneMax = 100;
            *tentativesMax = 15;
            return NIVEAU_LEGENDE;
        case 4:
            *borneMax = 1000;
            *tentativesMax = 10;
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


// Affiche un message de f�licitations bas� sur les tentatives
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

// Fonction principale pour jouer une partie
void jouerPartie(const char *pseudo, Niveau niveau, int borneMax, int tentativesMax) {
    Partie partie;
    strcpy(partie.pseudo, pseudo);

    time_t now = time(NULL);
    strftime(partie.dateHeure, sizeof(partie.dateHeure), "%Y-%m-%d %H:%M:%S", localtime(&now));

    int nombreADeviner = genererNombre(borneMax);
    int tentative = -1, nbTentatives = 0;
    int tempsRestant;

    printf("Devinez le nombre (entre 1 et %d). Vous avez %d tentatives :\n", borneMax, tentativesMax);
    while (nbTentatives < tentativesMax) {
        printf("Tentative %d : Vous avez 10 secondes pour r�pondre...\n", nbTentatives + 1);
        tempsRestant = 10;

        // Gestion du temps limite avec un d�compte en direct
        while (tempsRestant > 0) {
            printf("\rTemps restant : %d secondes ", tempsRestant); // Affiche sur la m�me ligne
            fflush(stdout); // Force l'affichage imm�diat
            if (_kbhit()) { // V�rifie si une touche a �t� press�e
                if (scanf("%d", &tentative) == 1) {
                    break; // Quitte la boucle de temps si une tentative est valide
                } else {
                    printf("\nEntr�e invalide. Veuillez entrer un nombre.\n");
                    while (getchar() != '\n'); // Vider le buffer
                }
            }
            Sleep(1000); // Attente de 1 seconde
            tempsRestant--;
        }

        // Si le temps est �coul�
        if (tempsRestant <= 0) {
            printf("\nTemps �coul� pour cette tentative !\n");
            nbTentatives++;
            continue; // Passe � la prochaine tentative
        }

        partie.tentatives[nbTentatives++] = tentative;

        if (tentative == nombreADeviner) {
            printf("\nF�licitations ! Vous avez devin� le nombre en %d tentatives.\n", nbTentatives);
            afficherMessageFelicitations(nbTentatives);
             // Enregistrer le score
            Score score;
            strcpy(score.pseudo, pseudo);
            score.nbTentatives = nbTentatives;
            score.ecartType = calculerEcartType(partie.tentatives, nbTentatives);
            strcpy(score.dateHeure, partie.dateHeure);
            enregistrerScore(&score);
            break;
        } else if (tentative < nombreADeviner) {
            printf("Plus grand !\n");
        } else {
            printf("Plus petit !\n");
        }
    }

    if (nbTentatives >= tentativesMax) {
        printf("\nVous avez �puis� vos %d tentatives. Le nombre �tait %d. Bonne chance la prochaine fois !\n", tentativesMax, nombreADeviner);
    }

    partie.nbTentatives = nbTentatives;
    partie.ecartType = calculerEcartType(partie.tentatives, nbTentatives);
    enregistrerPartie(&partie);
}

// Calcule l'�cart type des tentatives
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
void enregistrerScore(const Score *score) {
    FILE *f = fopen(FICHIER_SCORES, "a");
    if (!f) {
        printf("Erreur lors de l'ouverture du fichier des scores.\n");
        return;
    }
    fprintf(f, "%s;%d;%.2f;%s\n", score->pseudo, score->nbTentatives, score->ecartType, score->dateHeure);
    fclose(f);
}

void consulterScores() {
    FILE *f = fopen(FICHIER_SCORES, "r");
    if (!f) {
        printf("Aucun score enregistr� pour l'instant.\n");
        return;
    }

    // Chargement des scores en m�moire
    Score scores[100];
    int nbScores = 0;

    while (fscanf(f, "%[^;];%d;%f;%[^\n]\n",
                  scores[nbScores].pseudo,
                  &scores[nbScores].nbTentatives,
                  &scores[nbScores].ecartType,
                  scores[nbScores].dateHeure) == 4) {
        nbScores++;
    }
    fclose(f);

    // Tri des scores du meilleur au moins bon (par nombre de tentatives)
    for (int i = 0; i < nbScores - 1; i++) {
        for (int j = i + 1; j < nbScores; j++) {
            if (scores[i].nbTentatives > scores[j].nbTentatives) {
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // Affichage des scores
    printf("\n \t\t--- Classement des scores ---\n");
    for (int i = 0; i < nbScores; i++) {
        printf("%d. %s - Tentatives : %d, �cart-type : %.2f, Date : %s\n",
               i + 1, scores[i].pseudo, scores[i].nbTentatives, scores[i].ecartType, scores[i].dateHeure);
    }
}


// Lancer le jeu (menu principal)
void lancerJeu() {
    srand(time(NULL));

    char pseudo[50];
    do {
        printf("Entrez votre pseudo : ");
        scanf("%49s", pseudo);

        // V�rifiez si le pseudo est un nombre
        if (estUnNombre(pseudo)) {
            printf("Le pseudo ne peut pas �tre un nombre. Veuillez entrer un pseudo valide.\n");
        } else {
            break; // Le pseudo est valide, on sort de la boucle
        }
    } while (1);

    // V�rifier si le pseudo existe d�j�
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
        printf("3. Consulter les scores\n"); // Nouvelle option
        printf("4. Quitter\n");
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

            case 3: // Consultation des scores
                consulterScores();
                break;

            case 4: // Quitter
                printf("Merci d'avoir jou� ! � bient�t !\n");
                return;

            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choix != 4);
}
