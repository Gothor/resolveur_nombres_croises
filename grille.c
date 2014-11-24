#include<stdlib.h>
#include <stdio.h>
#include "grille.h"

#define TAILLE_MAX 256

/**
 * Permet de créer une structure Grille depuis un fichier
 *
 * @param const char* nomDuFichier
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
		// Si la lecture du fichier a réussi

		// Lecture du nombre de lignes
		if (fgets(chaine, TAILLE_MAX, fichier) != NULL)
			grille.lignes = atoi(chaine);

		// Lecture du nombre de colonnes
		if (fgets(chaine, TAILLE_MAX, fichier) != NULL)
			grille.colonnes = atoi(chaine);

		// Récupération des données
		grille.donnees = malloc(grille.lignes * grille.colonnes * sizeof(int));
		chaine[1] = '\0';
		for (i = 0; i < grille.lignes; i++) {
			for (j = 0; j < grille.colonnes; j++) {
				if ((chaine[0] = fgetc(fichier)) == 'X')
					grille.donnees[i * grille.colonnes + j] = CASE_NOIRE;
				else if (chaine[0] == '-')
					grille.donnees[i * grille.colonnes + j] = CASE_VIDE;
				else
					grille.donnees[i * grille.colonnes + j] = atoi(chaine);
			}
			fgetc(fichier); // On passe le saut de ligne
		}

		fclose(fichier);
	}
	else {
		// Si la lecture du fichier a échoué
		fprintf(stderr, "Le fichier demandé n'existe pas.");

		exit(EXIT_FAILURE);
	}

	return grille;
}

