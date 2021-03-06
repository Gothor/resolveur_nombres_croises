#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#include "liste.h"

/**
 * Grille de jeu, cette structure contient la taille de la grille et
 * son contenu.
 *
 * int lignes - nombre de lignes de la grille
 * int colonnes - nombre de colonnes de la grille
 * int* donnees - valeurs des cases de la grille :
 *                  - si le bit 10 est à 1, il s'agit d'une case noire
 *                  - les bits 0 à 9 sont à 1 si la case PEUT contenir le
 *                          chiffre correspondant au numéro du bit.
 *
 * Exemples de cases :
 * - 00000000 00000000 00000100 00000000 : la case est noire
 * - 00000000 00000000 00000011 11111111 : la case est vide
 * - 00000000 00000000 00000000 00100100 : la case est vide mais ne peut
 *                                              contenir que les valeurs 2 ou 5
 * - 00000000 00000000 00000000 00100000 : la case contient un 5
 */
typedef struct Grille Grille;
struct Grille {
    int lignes;
    int colonnes;
    int* donnees;
    
    Liste definitions;
};

enum {
    CASE_NOIRE = 1 << 10,
    // 00000000 00000000 00000100 00000000
    CASE_VIDE = 0x3FF
    // 00000000 00000000 00000011 11111111
};

Grille* grille_creer();
Grille* grille_lire(const char* nomDuFichier);
int grille_case_set(Grille* grille, int ligne, int colonne, int valeur);
int grille_case_get(const Grille* grille, int ligne, int colonne, int rawData);
void grille_afficher(const Grille* grille);
void grille_liberer(Grille* grille);

#endif // GRILLE_H_INCLUDED
