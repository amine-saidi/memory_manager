#ifndef _H_LISTESGENERIQUES_
#define _H_LISTESGENERIQUES_


/* Liste doublement chainees circulaire avec tete. 
 * (La tete - premier element de la liste, 
 * la tete ne contient pas de donnees.
 *
 * Chaque noeud possède un pointeur 
 * vers les donnees.
 */


struct elem{
  struct elem *suivant;    /* pointeur vers le suivant */
  struct elem *precedent;  /* pointeur vers le precedent */
  void *val;               /* pointeur vers les donnees */
};


typedef struct elem elem;
typedef elem *liste;


liste seek_node(liste e, int index);

/* creer_liste cree la tete de la liste */
liste creer_liste();

/* verifier si la liste vide.
 * Liste est vide quand elle ne contient
 * qua la tete.
 */
int est_vide(liste l);


/* inserer_apres( e, d) 
 * e pointe vers un element de la liste ou vers la tete.
 * d pointe vers les donnees a inserer.
 * Inserer un nouveau noeud d juste apres e.
 * Retourne le pointeur vers le nouvau noeud ou NULL
 * si l'insertion echoue.
 */
liste inserer_apres(liste e, void *d);

/* Inserer les donnees d avant le noeud 
 * pointe par e.
 */
liste inserer_avant(liste e, void *d);


int est_tete(liste l);


/* Supprimer l'element pointe par l.
 * Mais interdire la suppression de la tete.
 * Retourne le pointeur vers les donnees supprimees.
 */
void *supprimer_element(liste l);

/* supprimer tous les element de la liste,
 * sauf la tete.
 * l  pointe vers la tete.
 * Retourner la tete ou NULL si problemes.
 */
liste vider_liste(liste l);


void detruire_liste(liste l);

/* retourner la valeur du noeud l*/
void *valeur(liste l);

liste suivant(liste l);
liste precedent(liste l);


/* imprimer les donnees stockees dans la liste
 * quand les donnees sont de type double.
*/  
void imprimer_long(liste l);


#endif

