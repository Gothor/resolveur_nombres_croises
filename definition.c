#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "liste.h"
#include "definition.h"

const static TypesDefinitions LISTE_TYPES_DEFINITIONS[] = {
    {"carre", CARRE},
    {"palindrome", PALINDROME},
    {"fact", FACTEURS}
};

/**
 * Permet de créer une définition
 *
 * @return Definition* - pointeur vers la Definition créée
 */
Definition* definition_creer() {
    Definition* definition = malloc(sizeof(*definition));
    
    definition->ligne = 0;
    definition->sens = 0;
    definition->index = 0;
    definition->definitions = NULL;
    
    return definition;
}

/**
 * Permet d'initialiser une définition en fonction d'une chaîne de caractères
 *
 * @param const char* chaine - chaine à analyser de la forme :
 *      "%FUNC%=%PARAM%,%FUNC%=%PARAM%,..."
 *      - %FUNC% correspond à une fonction connue (voir LISTE_TYPES_DEFINITIONS)
 *      - %PARAM% correspond au paramètre de cette fonction
 *      Exemples :
 *          "carre=0"
 *          "facteurs=12,carre=0"
 * @param int taille - taille de la chaine à analyser
 *
 * @return Definition* - pointeur vers la definition créée
 */
Definition* definition_lire(const char* chaine, int taille) {
    Definition* definition = definition_creer();
    SousDefinition *sousDefinition = NULL;
    char *intitule = NULL, *token = NULL;
    const char separator[2] = ",";
    int i, j;
    TypeDefinition type;
    char* test = strdup(chaine);
    test[taille] = '\0';
    
    token = strtok(test, separator);
    
    while (token != NULL) {
        for (i = 0; i < taille && token[i] != '='; i++);
        
        if (i >= taille) {
            fprintf(stderr, "Définition incorrecte : caractère '=' manquant");
            exit(EXIT_FAILURE);
        }
        
        intitule = strdup(token);
        intitule[i] = '\0';
        
        for (j = 0; j < sizeof(LISTE_TYPES_DEFINITIONS)/sizeof(TypesDefinitions);
                                                                                j++)
            if (!strcmp(intitule, LISTE_TYPES_DEFINITIONS[j].nom)) {
                type = LISTE_TYPES_DEFINITIONS[j].type;
                break;
            }
        
        if (j >= sizeof(LISTE_TYPES_DEFINITIONS)/sizeof(TypesDefinitions)) {
            fprintf(stderr, "Définition incorrecte : fonction '%s' inconnue", intitule);
            free(intitule);
            exit(EXIT_FAILURE);
        }
        free(intitule);
        
        if (strlen(token) <= i + 1) {
            fprintf(stderr, "Definition incorrecte : paramètre manquant");
            exit(EXIT_FAILURE);
        }
        
        sousDefinition = sous_definition_creer();
        sousDefinition->fonction = type;
        sousDefinition->parametre = strtod(&token[i+1], NULL);
        liste_ajouter(liste_creer(sousDefinition), &definition->definitions);
        
        token = strtok(NULL, separator);
    }
    
    return definition;
}

/**
 * Permet de libérer en mémoire une Définition
 *
 * @param Definition* definition - pointeur vers la Définition à libérer en
 * mémoire
 */
void definition_liberer(Definition* definition) {
    liste_liberer(definition->definitions, (void (*)(const void *)) sous_definition_liberer);
    free(definition);
}

/**
 * Permet de créer une SousDefinition
 *
 * @return SousDefinition* - pointeur vers la SousDefinition créée
 */
SousDefinition* sous_definition_creer() {
    SousDefinition* sousDefinition = malloc(sizeof *sousDefinition);
    
    sousDefinition->parametre = 0;
    
    return sousDefinition;
}

/**
 * Permet de libérer en mémoire une SousDefinition
 *
 * @param SousDefinition* sousDefinition - pointeur vers la SousDefinition à
 * libérer en mémoire
 */
void sous_definition_liberer(SousDefinition* sousDefinition) {
    free(sousDefinition);
}
