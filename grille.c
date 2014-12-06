#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "grille.h"
#include "liste.h"
#include "definition.h"
#include "helper.h"

#define TAILLE_MAX (256)

/**
 * @TODO Comment réagir en cas d'erreur dans le fichier ?
 */
 
Grille* grille_creer() {
    Grille* grille = malloc(sizeof(*grille));
    
    grille->lignes = 0;
    grille->colonnes = 0;
    grille->donnees = NULL;
    grille->definitions = NULL;
    
    return grille;
}

void grille_liberer(Grille* grille) {
    free(grille->donnees);
    liste_liberer(grille->definitions, (void (*)(const void *)) definition_liberer);
    free(grille);
}

/**
 * Permet de créer une structure Grille depuis un fichier
 *
 * @param const char* nomDuFichier - nom du fichier contenant la grille
 *
 * @return Grille
 */
Grille* grille_lire(const char* nomDuFichier) {
    FILE* fichier = NULL;
    Grille* grille = grille_creer();
    char chaine[TAILLE_MAX] = "";
    int i, j, k, ligne, sens;
    
    fichier = fopen(nomDuFichier, "r");

    if (fichier == NULL) {
        // Si la lecture du fichier a échoué
        fprintf(stderr, "Le fichier demandé n'existe pas.");
        exit(EXIT_FAILURE);
    }

    // Lecture du nombre de lignes
    if (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        grille->lignes = atoi(chaine);

    // Lecture du nombre de colonnes
    if (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        grille->colonnes = atoi(chaine);

    // Récupération des données
    grille->donnees = malloc(grille->lignes * grille->colonnes * sizeof(int));
    chaine[1] = '\0';
    for (i = 0; i < grille->lignes; i++) {
        for (j = 0; j < grille->colonnes; j++) {
            if ((chaine[0] = fgetc(fichier)) == 'X')
                grille_case_set(grille, i, j, CASE_NOIRE);
            else if (chaine[0] == '-')
                grille_case_set(grille, i, j, CASE_VIDE);
            else
                grille_case_set(grille, i, j, 1 << atoi(chaine));
        }
        fgetc(fichier); // On passe le saut de ligne
    }
    
    // Récupération des définitions
    while (fgets(chaine, TAILLE_MAX, fichier) != NULL) {
        // Lecture du numéro de ligne (ou lettre pour une colonne)
        if(char_est_un_chiffre(chaine[0])) {
            sens = HORIZONTAL;
            for(j = ligne = 0; char_est_un_chiffre(chaine[j]); j++) {
                ligne += chaine[j] - '0';
            }
        }
        if(char_est_une_lettre(chaine[0])) {
            sens = HORIZONTAL;
            for(j = ligne = 0; char_est_une_lettre(chaine[j]); j++) {
                ligne += char_mettre_en_majuscule(chaine[j]) - 'A';
            }
        }
        j++; // On passe l'espace entre l'identifiant de la ligne et le reste
        
        // Lecture des définitions
        Definition* def = NULL;
        do {
            for (k = j; chaine[k] != ';' && chaine[k] != '\n' && chaine[k] != '\0'; k++);
            def = definition_lire(&chaine[j], k - j);
            liste_ajouter(liste_creer(def), &grille->definitions);
            j = k + 1;
        } while(chaine[j] != '\n' && chaine[k] != '\0');
    }

    fclose(fichier);

    return grille;
}

/**
 * Permet d'affecter une valeur à une case de la grille
 *
 * @param Grille* grille - pointeur vers la grille à modifier
 * @param int ligne - la ligne de la case à modifier
 * @param int colonne - la colonne de la case à modifier
 * @param int valeur - la nouvelle valeur de la case à modifier
 *
 * @return int - 1 en cas d'erreur, 0 sinon
 */
int grille_case_set(Grille* grille, int ligne, int colonne, int valeur) {
    // Si la grille n'est pas allouée
    if (grille == NULL)
        return 1;
        
    // Si la ligne ou la colonne demandée est trop grande
    if (ligne > grille->lignes || colonne > grille->colonnes)
        return 1;
    
    grille->donnees[ligne * grille->colonnes + colonne] = valeur;
    
    return 0;
}

/**
 * Permet de récupérer la valeur d'une case de la grille
 * 
 * @param const Grille* grille - pointeur vers la grille à lire
 * @param int ligne - ligne de la case
 * @param int colonne - colonne de la case
 * @param int rawData - précise si la valeur renvoyée doit être traitée ou non
 *
 * @return int
 *      si rawData == TRUE - la valeur non-traitée de la case (voir la
 *          description de struct Grille)
 *      sinon - la valeur traitée de la case (CASE_NOIRE, CASE_VIDE ou une
 *          valeur de 0 à 9)
 */
int grille_case_get(const Grille* grille, int ligne, int colonne, int rawData) {
    int valeur, i, valeursPossibles = 0;
    
    // Si la grille n'est pas allouée
    if (grille == NULL)
        return -1;
        
    // Si la ligne ou la colonne demandée est trop grande
    if (ligne > grille->lignes || colonne > grille->colonnes)
        return -1;
    
    valeur = grille->donnees[ligne * grille->colonnes + colonne];
    
    // Si la valeur ne doit pas être traitée
    if (rawData)
        return valeur;
    
    // Si la case est noire, on renvoie CASE_NOIRE
    if (valeur & CASE_NOIRE)
        return CASE_NOIRE;
        
    for (i = 0; i <= 9; i++)
        if (valeur & 1 << i) {
            if (valeursPossibles > 0) // C'est qu'on a plusieurs valeurs possibles
                return CASE_VIDE;
            valeursPossibles = i + 1;
            // On rajoute 1 pour que si 0 est une valeur possible, on arrête
            // tout de même la boucle si une autre valeur est également possible
        }
        
    return valeursPossibles - 1; // On retire du coup le 1 ajouté précédemment
}

/**
 * Permet d'afficher la grille en ASCII sur la sortie standard
 *
 * @param const Grille* grille - pointeur vers la grille à afficher
 */
void grille_afficher(const Grille* grille) {
    int i, j, valeurCase;
    
    if (grille == NULL)
        return ;
    
    for (i = 0; i < grille->lignes; i++) {
        for (j = 0; j < grille->colonnes; j++) {
            switch (valeurCase = grille_case_get(grille, i, j, FALSE)) {
                case CASE_NOIRE :
                    printf("X");
                    break;
                case CASE_VIDE :
                    printf("-");
                    break;
                default :
                    printf("%d", valeurCase);
            }
        }
        printf("\n");
    }
}
