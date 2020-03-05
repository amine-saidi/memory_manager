#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "listes_generiques.h"




liste seek_node(liste e, int index){

    while(e != NULL && index > 0)
	{
	  e=e->suivant;
	  index--;
	}


  return e;
}

/* creer_liste cree la tete de la liste */
liste creer_liste(){
  liste p = malloc( sizeof(elem) );
  if(p == NULL){
    return NULL;
  }
  p->suivant = p->precedent = p;
  p->val = NULL;
  return p;
}

/* verifier si la liste vide.
 * Liste est vide quand elle ne contient
 * qua la tete.
 */
int est_vide(liste l){
  return l->suivant == l;
}


/* inserer_apres( e, d) 
 * e pointe vers un element de la liste ou vers la tete.
 * d pointe vers les donnees a inserer.
 * Inserer un nouveau noeud d juste apres e.
 * Retourne le pointeur vers le nouvau noeud ou NULL
 * si l'insertion echoue.
 */
liste inserer_apres(liste e, void *d){
  if (d == NULL) /* interdiction d'inserer NULL*/
    return NULL;
  liste nouveau = malloc(sizeof(elem));
  if(nouveau == NULL)
    return NULL;
  liste next = e->suivant;
  e->suivant = next->precedent = nouveau;
  nouveau->precedent = e;
  nouveau->suivant = next;
  nouveau->val = d;
  return nouveau;
}

/* Inserer les donnees d avant le noeud 
 * pointe par e.
 */
liste inserer_avant(liste e, void *d){
  return inserer_apres(e->precedent, d);
}

int est_tete(liste l){
  return l->val == NULL; /* val est NULL uniquement dans la tete */
}

/* Supprimer l'element pointe par l.
 * Mais interdire la suppression de la tete.
 * Retourne le pointeur vers les donnees supprimees.
 */
void *supprimer_element(liste l){
  if ( est_tete(l) )
    return NULL;
  liste p = l->precedent;
  liste s = l->suivant;
  p->suivant = s;
  s->precedent = p;
  void *q = l->val;
  free(l);
  return q;
}

/* supprimer tous les element de la liste,
 * sauf la tete.
 * l  pointe vers la tete.
 * Retourner la tete ou NULL si problemes.
 */
liste vider_liste(liste l){
  if( !est_tete(l) )
    return NULL;
  for( liste q = l->suivant; !est_tete(q) ; q = q->suivant ){
    supprimer_element(q);
  }
  return l;
}

void detruire_liste(liste l){
  vider_liste(l);
  free(l);
}

/* retourner la valeur du noeud l*/
void *valeur(liste l){
  return l->val;
}

liste suivant(liste l){
  return l->suivant;
}

liste precedent(liste l){
  return l->precedent;
} 

/* imprimer les donnees stockees dans la liste
 * quand les donnees sont de type double.
*/ 
 
 
void imprimer_long(liste l){
  liste q;  
  q = l->suivant;
  while( !est_tete(q) ){
    printf("%ld ", *((long *)valeur(q)));
    q = suivant(q);
  }
  printf("\n"); 
}

/*

int main(void){
  long t[] = {6, 9, -5, 123, -78, 56, -45, 1, -11, 56, 9, 6, 9};
  size_t n = sizeof(t)/sizeof(t[0]);
  liste l = creer_liste();
  if(l == NULL)
    exit(1);
  for(int i=0; i<n; i++){
    inserer_apres(l, &t[i]);
  }


  imprimer_long(l);

  liste q = l;
  for(int i=0; i<4; i++){
    q=suivant(q);
  }
  liste m = q->suivant;
  supprimer_element(q);

  supprimer_element(m->suivant);

  imprimer_long(l);

  detruire_liste(l);


  exit(0);
}

*/
