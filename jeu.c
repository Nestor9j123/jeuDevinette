
#include "jeu.h"

// Génère un nombre aléatoire entre 1 et borneMax
int genererNombre(int borneMax) {
    return rand() % borneMax + 1;
}

// Fonction pour choisir le niveau et les paramètres
Niveau choisirNiveau(int *borneMax, int *tentativesMax) {
    int choix;
    printf("\nChoisissez un niveau :\n");
    printf("1. Débutant (1-10, 5 tentatives)\n");
    printf("2. Moyen (1-50, 8 tentatives)\n");
    printf("3. Légende (1-100, 15 tentatives)\n");
    printf("4. Ultime (1-1000, 10 tentatives)\n");
    printf("5. Personnalisé\n");
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
            printf("Choix invalide. Niveau débutant sélectionné par défaut.\n");
            *borneMax = 10;
            *tentativesMax = 5;
            return NIVEAU_DEBUTANT;
    }
}


// Affiche un message de félicitations basé sur les tentatives
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
        printf("Tentative %d : Vous avez 10 secondes pour répondre...\n", nbTentatives + 1);
        tempsRestant = 10;

        // Gestion du temps limite avec un décompte en direct
        while (tempsRestant > 0) {
            printf("\rTemps restant : %d secondes ", tempsRestant); // Affiche sur la même ligne
            fflush(stdout); // Force l'affichage immédiat
            if (_kbhit()) { // Vérifie si une touche a été pressée
                if (scanf("%d", &tentative) == 1) {
                    break; // Quitte la boucle de temps si une tentative est valide
                } else {
                    printf("\nEntrée invalide. Veuillez entrer un nombre.\n");
                    while (getchar() != '\n'); // Vider le buffer
                }
            }
            Sleep(1000); // Attente de 1 seconde
            tempsRestant--;
        }

        // Si le temps est écoulé
        if (tempsRestant <= 0) {
            printf("\nTemps écoulé pour cette tentative !\n");
            nbTentatives++;
            continue; // Passe à la prochaine tentative
        }

        partie.tentatives[nbTentatives++] = tentative;

        if (tentative == nombreADeviner) {
            printf("\nFélicitations ! Vous avez deviné le nombre en %d tentatives.\n", nbTentatives);
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
        printf("\nVous avez épuisé vos %d tentatives. Le nombre était %d. Bonne chance la prochaine fois !\n", tentativesMax, nombreADeviner);
    }

    partie.nbTentatives = nbTentatives;
    partie.ecartType = calculerEcartType(partie.tentatives, nbTentatives);
    enregistrerPartie(&partie);
}

// Calcule l'écart type des tentatives
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
        printf("Aucun score enregistré pour l'instant.\n");
        return;
    }

    // Chargement des scores en mémoire
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
        printf("%d. %s - Tentatives : %d, Écart-type : %.2f, Date : %s\n",
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

        // Vérifiez si le pseudo est un nombre
        if (estUnNombre(pseudo)) {
            printf("Le pseudo ne peut pas être un nombre. Veuillez entrer un pseudo valide.\n");
        } else {
            break; // Le pseudo est valide, on sort de la boucle
        }
    } while (1);

    // Vérifier si le pseudo existe déjà
    if (verifierPseudoExiste(pseudo)) {
        printf("Bienvenue de retour, %s !\n", pseudo);
    } else {
        printf("Nouveau joueur détecté. Enregistrement...\n");
        enregistrerPseudo(pseudo);
    }

    Niveau niveau;
    int borneMax, tentativesMax;
    char rejouer = 'y'; // Variable pour gérer la rejouabilité
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
            case 1: // Choix d'un niveau et lancement immédiat
                niveau = choisirNiveau(&borneMax, &tentativesMax);
                do {
                    jouerPartie(pseudo, niveau, borneMax, tentativesMax);
                    printf("Voulez-vous rejouer avec le même niveau ? (y/n) : ");
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
                printf("Merci d'avoir joué ! À bientôt !\n");
                return;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 4);
}
