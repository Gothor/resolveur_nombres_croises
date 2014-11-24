#include<stdlib.h>
#include <stdio.h>
#include "grille.h"

#define TAILLE_MAX (256)

/**
 * Permet de cr�er une structure Grille depuis un fichier
 *
 * @param const char* nomDuFichier - nom du fichier contenant la grille
 *
 * @return Grille
 */
Grille creerGrille(const char* nomDuFichier) {
	FILE* fichier = NULL;
	Grille grille;
	char chaine[TAILLE_MAX] = "";
	int i, j;
	
	fichier = fopen(nomDuFichier, "r");

	if (fichier != NULL) {
		// Si la lecture du fichier a r�ussi

		// Lecture du nombre de lignes
		if (fgets(chaine, TAILLE_MAX, fichier) != NULL)
			grille.lignes = atoi(chaine);

		// Lecture du nombre de colonnes
		if (fgets(chaine, TAILLE_MAX, fichier) != NULL)
			grille.colonnes = atoi(chaine);

		// R�cup�ration des donn�es
		grille.donnees = malloc(grille.lignes * grille.colonnes * sizeof(int));
		chaine[1] = '\0';
		for (i = 0; i < grille.lignes; i++) {
			for (j = 0; j < grille.colonnes; j++) {
				if ((chaine[0] = fgetc(fichier)) == 'X')
					grille_case_set(&grille, i, j, CASE_NOIRE);
				else if (chaine[0] == '-')
					grille_case_set(&grille, i, j, CASE_VIDE);
				else
					grille_case_set(&grille, i, j, 1 << atoi(chaine));
			}
			fgetc(fichier); // On passe le saut de ligne
		}

		fclose(fichier);
	}
	else {
		// Si la lecture du fichier a �chou�
		fprintf(stderr, "Le fichier demand� n'existe pas.");

		exit(EXIT_FAILURE);
	}

	return grille;
}


/**
 * Permet d'affecter une valeur � une case de la grille
 *
 * @param Grille* grille - pointeur vers la grille � modifier
 * @param int ligne - la ligne de la case � modifier
 * @param int colonne - la colonne de la case � modifier
 * @param int valeur - la nouvelle valeur de la case � modifier
 *
 * @return int - 1 en cas d'erreur, 0 sinon
 */
int grille_case_set(Grille* grille, int ligne, int colonne, int valeur) {
    // Si la grille n'est pas allou�e
    if (grille == NULL)
        return 1;
        
    // Si la ligne ou la colonne demand�e est trop grande
    if (ligne > grille->lignes || colonne > grille->colonnes)
        return 1;
    
    grille->donnees[ligne * grille->colonnes + colonne] = valeur;
    
    return 0;
}
