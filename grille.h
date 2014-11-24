#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

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

