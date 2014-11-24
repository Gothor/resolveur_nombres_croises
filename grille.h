#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

/**
 * Grille de jeu, cette structure contient la taille de la grille et
 * son contenu.
 *
 * int lignes - nombre de lignes de la grille
 * int colonnes - nombre de colonnes de la grille
 * int* donnees - cases de la grille
 */
typedef struct Grille Grille;
struct Grille {
	int lignes;
	int colonnes;
	int* donnees;
};

enum {
	CASE_NOIRE = -1,
	CASE_VIDE = -2
};

Grille creerGrille(const char* nomDuFichier);

#endif // GRILLE_H_INCLUDED

