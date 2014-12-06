#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#include "liste.h"

/**
 * Définition de la grille de jeu.
 *
 * int ligne - numéro de la ligne (ou colonne) que la définition cible
 * int sens - indique si la définition est celle d'un chiffre dans une ligne
 *              ou dans une colonne
 * int index - index du nombre défini dans la ligne ou colonne (s'il y a
 *              plusieurs nombres dans la même ligne ou colonne)
 */
typedef struct Definition Definition;
struct Definition {
    int ligne;
    int sens;
    int index;
    
    Liste definitions;
};

/**
 * Liste des types de définitions existantes
 */
typedef enum TypeDefinition TypeDefinition;
enum TypeDefinition {
    CARRE,
    PALINDROME,
    FACTEURS
};

/**
 * Permet facilement la correspondance entre une définition de type
 * TypeDefinition et une chaîne de caractère. (Voir le début du fichier
 * definition.c pour la liste en question)
 *
 * Exemples :
 * - {"carre", CARRE}
 * - {"palindrome", PALINDROME}
 */
typedef struct TypesDefinitions TypesDefinitions;
struct TypesDefinitions {
    char* nom;
    TypeDefinition type;
};

/**
 * @TODO renommer la structure SousDefinition ou Definition parce que là...
 *              c'est vraiment pas clair...
 *
 * En gros, une définition, peut elle même être constituée de plusieurs
 * définitions (ex : carré && palindrome)
 */
typedef struct SousDefinition SousDefinition;
struct SousDefinition {
    TypeDefinition fonction;
    int parametre;
};

enum {
    HORIZONTAL,
    VERTICAL
};

Definition* definition_creer();
Definition* definition_lire(const char* chaine, int n);
void definition_liberer(Definition* definition);

SousDefinition* sous_definition_creer();
void sous_definition_liberer(SousDefinition* sousDefinition);

#endif // DEFINITION_H_INCLUDED