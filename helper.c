/*
    Fonctions utilitaires pouvant être nécessaires à différents endroits.
*/

#include "helper.h"

/**
 * Permet de vérifier si un char envoyé correspond à un chiffre
 *
 * @param char c - char à vérifier
 *
 * @return int - 1 si le char est un chiffre, 0 sinon
 */
int char_est_un_chiffre(char c) {
    if (c >= '0' && c <= '9')
        return 1;
    
    return 0;
}

/**
 * Permet de vérifier si un char envoyé correspond à une lettre
 *
 * @param char c - char à vérifier
 *
 * @return int - 1 si le char est une lettre, 0 sinon
 */
int char_est_une_lettre(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 1;
    
    return 0;
}

/**
 * Permet de mettre un char en majuscule s'il s'agit d'une lettre
 *
 * @param char c - char à mettre en minuscule
 *
 * @return char - char mis en majuscule
 */
char char_mettre_en_majuscule(char c) {
    if (c >= 'a' && c <= 'z')
        c = c - 'a' + 'A';
    
    return c;
}