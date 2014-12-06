/*
    Fonctions permettant de gérer les listes (Source : M. Farès Belhadj)
*/

#include <stdlib.h>
#include "liste.h"

/**
 * Permet de créer un noeud de liste
 *
 * @param const void* data - pointeur vers l'objet que doit contenir ce noeud
 *
 * @return NoeudListe*
 */
NoeudListe* liste_creer(const void* data) {
    NoeudListe* noeud = malloc(sizeof(*noeud));
    
    noeud->data = (void*) data;
    noeud->suivant = NULL;
    
    return noeud;
}

/**
 * Permet de libérer tous les noeuds d'une liste
 *
 * @param NoeudListe* noeud - pointeur vers le premier noeud de la liste
 * @param void (*func)(const void *) - pointeur vers une fonction de callback
 *              permettant de libérer l'objet contenu dans le noeud si besoin
 */
void liste_liberer(NoeudListe* noeud, void (*func)(const void *)) {
    NoeudListe* tmp;
    
    // Tant que noeud pointe vers un objet existant
    while(noeud != NULL) {
        tmp = noeud->suivant;
        
        // On libère cet objet avec la fonction envoyée en paramètre
        if (func != NULL)
            func(noeud->data);
        // Puis on libère le noeud en lui-même
        free(noeud);
        
        noeud = tmp;
    }
}

/**
 * Permet d'ajouter un noeud au début d'une liste
 *
 * @param NoeudListe* nouveau_noeud - pointeur vers le noeud à ajouter
 * @param NoeudListe** liste - pointeur vers la liste à laquelle le nouveau
 *              noeud doit être ajouté
 */
void liste_ajouter(NoeudListe* nouveau_noeud, NoeudListe** liste) {
    nouveau_noeud->suivant = *liste;
    *liste = nouveau_noeud;
}