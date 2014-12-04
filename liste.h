#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

/**
 * Liste générique pouvant contenir n'importe quel type d'objet (mais le même
 * type d'objet dans toute la liste)
 *
 * void* data - pointeur vers l'objet contenu dans le noeud
 * struct NoeudListe* suivant - pointeur vers le prochain objet de la liste
 */
typedef struct NoeudListe NoeudListe;
typedef struct NoeudListe * Liste;
struct NoeudListe {
    void* data;
    struct NoeudListe* suivant;
};

NoeudListe* liste_creer(const void* data);
void liste_liberer(NoeudListe* noeud, void (*func)(const void *));
void liste_ajouter(NoeudListe* nouveau_noeud, NoeudListe** liste);

#endif // LISTE_H_INCLUDED