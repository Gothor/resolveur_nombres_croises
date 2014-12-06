#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

/**
 * Représentation simple d'un booléen
 */
typedef enum Booleen Booleen;
enum Booleen {
    FALSE = 0,
    TRUE = 1
};

int char_est_un_chiffre(char c);
int char_est_une_lettre(char c);
char char_mettre_en_majuscule(char c);

#endif // HELPER_H_INCLUDED