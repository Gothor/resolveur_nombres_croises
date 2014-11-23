#include <stdio.h>
#include "grille.h"

typedef struct grille grille;
struct grille {
	int lignes;
	int colonnes;
	int* donnees;
}

