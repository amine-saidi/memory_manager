#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet2019.h"

#define NTRANCHES 1024




/* calculer le nombre de bloc */
size_t nb_blocs(size_t o){
	size_t nb_blocs=(o+sizeof(align_data)-1)/sizeof(align_data);
	return nb_blocs;
}


int compare_function(const void *a,const void *b) 
{ 
tranche *tranche1 = (tranche *) a;   
tranche *tranche2 = (tranche *) b;

return tranche1->nb_blocs > tranche2->nb_blocs;
} 


void * ld_create( size_t nboctets )
{

	head *liste =malloc(sizeof(head)); 
	if(liste==NULL){ printf("erreur allocation head \n"); return NULL;}
	
	liste->memory= malloc(nb_blocs(nboctets)*sizeof(align_data));

	if(liste->memory==NULL){ printf("erreur allocation memory \n"); return NULL; }

	liste->tab_tranches  = malloc( NTRANCHES * sizeof(tranche) ) ;

	liste->first=-1;
	liste->last=-1;
	liste->memory_size=nb_blocs(nboctets)*sizeof(align_data);
	liste->node_number=0;
	liste->nbr_tranches=1;
	liste->tab_tranches[0].decalage=0;
	liste->tab_tranches[0].nb_blocs=nb_blocs(nboctets);

				                                               
	return liste;
}




void *ld_first(void *liste){

	head *new_liste=liste;

	if(new_liste->first==-1 ){
		return NULL;
	}
	return (void *) new_liste->memory + new_liste->first*sizeof(align_data) ;

}

void *ld_next(void *liste, void *current)
{	
	if(liste==current)
	{
		return ld_first(liste);
	}

	node * new_node = current;

	if(new_node->next==0)
	{
		return NULL;
	}	

	return (void *) new_node + new_node->next*sizeof(align_data)  ; 
}


// Looks for a node of a certain index in a list
node * seek_node2(void *liste, int index){
  node * current;

      current = ld_first(liste);
      while(current != NULL && index > 1)
	{
	  index--;
	  current = (void *)current + current->next*sizeof(align_data)  ;
	}


  return current;
}

void *ld_previous(void *liste, void *current)
{
	node * new_node = current;
	if(new_node->previous==0)
	{
	return NULL;
	}	
	return (char *) new_node + new_node->previous*sizeof(align_data)  ; 
}

void add_tranches(void *liste,size_t decalage,size_t len)
{

	head *new_liste=liste;
	int posbeg=-1,posend=-1;
	for(int i=0;i<new_liste->nbr_tranches;i++)
	{
		if(new_liste->tab_tranches[i].decalage +new_liste->tab_tranches[i].nb_blocs == decalage) posbeg=i;
		if(decalage+len== new_liste->tab_tranches[i].decalage) posend=i;
	}
	if(posbeg!=-1&&posend!=-1)
	{
	new_liste->tab_tranches[posbeg].nb_blocs+=len+new_liste->tab_tranches[posend].nb_blocs;
	new_liste->tab_tranches[posend].nb_blocs=SIZE_MAX;


	}
	else if(posbeg!=-1)
	{
	new_liste->tab_tranches[posbeg].nb_blocs+=len;
	}
	else if(posend!=-1)
	{
	new_liste->tab_tranches[posend].decalage-=len;
	new_liste->tab_tranches[posend].nb_blocs+=len;
	}
	else
	{	
	new_liste->tab_tranches[new_liste->nbr_tranches].decalage=decalage;
	new_liste->tab_tranches[new_liste->nbr_tranches].nb_blocs=len;
	new_liste->nbr_tranches++;
	}
	qsort(new_liste->tab_tranches,new_liste->nbr_tranches, sizeof(tranche), compare_function); 
	
	if(posbeg!=-1&&posend!=-1) new_liste->nbr_tranches--;	
	
}


void *ld_delete_node(void *liste, void *n)
{
	if(liste==NULL || n==NULL) return NULL;
	head *new_liste=liste;
	node * todelete_node = n;

	node * previous_node =ld_previous(liste, n);
	node * next_node = ld_next(liste, n);
	if(new_liste->nbr_tranches< NTRANCHES )
	{
	add_tranches(liste,( n - new_liste->memory)/sizeof(align_data),todelete_node->len);
	if(next_node==NULL&&previous_node==NULL)
	{
	 new_liste->last=-1;
	new_liste->first=-1;
	}
	else
	 {
	if(next_node==NULL) {previous_node->next =0; new_liste->last=((void *)previous_node-(void *)new_liste->memory )/sizeof(align_data);}
	else  next_node->previous  += todelete_node->	previous;
	if(previous_node==NULL) {next_node->previous=0;new_liste->first=((void *)next_node -(void *)new_liste->memory )/sizeof(align_data); }
	else previous_node->next += todelete_node->next;
	}
	new_liste->node_number--;
	return liste;
	}
	return NULL;
}


void ld_destroy(void *liste)
{

	head *new_liste=liste;
	free(new_liste->tab_tranches);
	free(new_liste->memory);
	free(liste);
	printf("\n\nMémoire libérée \n \n");
}


size_t ld_total_free_memory(void *liste)
{
	if(liste==NULL) return -1;
	head *new_liste=liste;
	size_t total_free_memory=0;
	for(int i=0;i<new_liste->nbr_tranches;i++)
	{
	total_free_memory+=new_liste->tab_tranches[i].nb_blocs*sizeof(align_data);
	}
	return total_free_memory;


}


size_t ld_total_useful_memory(void *liste)
{
	if(liste==NULL) return -1;
	head *new_liste=liste;
	size_t total_useful_memory=0;
	for(int i=0;i<new_liste->nbr_tranches;i++)
	{
	 if(new_liste->tab_tranches[i].nb_blocs>=3) total_useful_memory+= new_liste->tab_tranches[i].nb_blocs*sizeof(align_data) ;
	}
	return total_useful_memory;

}


void * ld_insert_after(void *liste, void *n, size_t len, void *p_data){

	if(liste==NULL || n==NULL) return NULL;

	head *new_liste=liste;
	node * new_node = n;
	if(new_node->next==0)
	{
	 return ld_insert_last(liste,len,p_data);
	}
	node * new_nodenxt=ld_next(liste,new_node); 
	size_t newlen=nb_blocs(len) +sizeof(node)/sizeof(align_data) ;
	size_t* a;
	size_t b=-1;
	a=&b;
	ptrdiff_t decalage=tranches_libre(liste,newlen, a);
	if(decalage==-1) {
		printf("y'en plus de memoire  !!!!! essayer avec compatify ou add memory ...merci\n");
		return NULL;
	}


	node * inserted_node=(void *) new_liste->memory + decalage*sizeof(align_data) ;
	if (new_node == NULL)return NULL;
	ptrdiff_t decalagenext= decalage -( (align_data *) new_nodenxt - (align_data *) new_liste->memory );	
	new_nodenxt->previous= decalagenext;
	((node*) inserted_node)->next= - decalagenext;


	ptrdiff_t decalageprev= decalage -( (align_data *) new_node - (align_data *) new_liste->memory );	
	((node*) inserted_node)->previous=-decalageprev;
	new_node->next= decalageprev;


	((node*) inserted_node)->len = newlen  ;



	align_data *  new_data = p_data;
	memmove(inserted_node->data,new_data,len);
	new_liste->tab_tranches[b].decalage+= newlen;
	new_liste->tab_tranches[b].nb_blocs-= newlen ;
	size_t tmp=new_liste->tab_tranches[b].nb_blocs;
	if(tmp==0) {new_liste->tab_tranches[b].nb_blocs=SIZE_MAX; }
	qsort(new_liste->tab_tranches,new_liste->nbr_tranches, sizeof(tranche), compare_function); 
	if(tmp==0) new_liste->nbr_tranches--;	
	new_liste->node_number++;
	return inserted_node;	
}

void * ld_insert_before(void *liste, void *n, size_t len, void *p_data){

	if(liste==NULL || n==NULL) return NULL;
	head *new_liste=liste;
	node * new_node = n;
	if(new_node->previous==0)
	{
		return ld_insert_first(new_liste,len,p_data);
	}

	node * new_nodeprivous=ld_previous(liste,new_node); 
	size_t newlen=nb_blocs(len) +sizeof(node)/sizeof(align_data) ;
	size_t* a;
	size_t b=-1;
	a=&b;
	ptrdiff_t decalage=tranches_libre(liste,newlen , a);
	if(decalage==-1) {
		printf("y'en plus de memoire  !!!!! essayer avec compatify ou add memory ...merci\n");
		return NULL;
	}

	node * inserted_node=(void *) new_liste->memory + decalage*sizeof(align_data) ;
	if (new_node == NULL) return NULL;
	ptrdiff_t decalageprivous= decalage -( (align_data *) new_nodeprivous - (align_data *) new_liste->memory );	
	new_nodeprivous->next= decalageprivous;
	((node*) inserted_node)->previous= -decalageprivous;


	ptrdiff_t decalagenext= decalage -( (align_data *) new_node - (align_data *) new_liste->memory );	
	((node*) inserted_node)->next= -decalagenext;
	new_node->previous= +decalagenext;


	((node*) inserted_node)->len = newlen  ;



	align_data *  new_data = p_data;
	memmove(inserted_node->data,new_data,len);
	new_liste->tab_tranches[b].decalage+=newlen;
	new_liste->tab_tranches[b].nb_blocs-=newlen ;
	size_t tmp=new_liste->tab_tranches[b].nb_blocs;
	if(tmp==0) {new_liste->tab_tranches[b].nb_blocs=SIZE_MAX; }
	qsort(new_liste->tab_tranches,new_liste->nbr_tranches, sizeof(tranche), compare_function); 
	if(tmp==0) new_liste->nbr_tranches--;
	new_liste->node_number++;
	return inserted_node;	
}


size_t ld_get(void *liste, void *current, size_t len, void *val){

	if(liste==NULL ) return -1;
	node * new_node = current;
	align_data *  new_data = current+sizeof(node);
	size_t  copied=(new_node->len*sizeof(align_data)-sizeof(node)<len)?(new_node->len*sizeof(align_data)-sizeof(node)):len;
	memmove(val,new_data, copied);	
        return copied;
}

void *ld_add_memory(void *liste, size_t nboctets)
{
	if(nboctets<0) return NULL;
	head *new_liste=liste;
	size_t new_size= new_liste->memory_size + nb_blocs(nboctets)*sizeof(align_data);
  	void * ptr = realloc(new_liste->memory ,new_size);
	if(ptr==NULL) return NULL;
	if(ptr!=new_liste->memory)
	{
	free(new_liste->memory);
	new_liste->memory=ptr;
	}
	add_tranches(liste,new_liste->memory_size/sizeof(align_data),nb_blocs(nboctets));
	new_liste->memory_size=new_size;

	return liste;
}

void afficher(void *liste){
	head *new_liste=liste;
	printf("L'adresse du hear est : %p \n",liste);
	printf("La memoire total en octave est de : %ld, en block %ld: \n",new_liste->memory_size,new_liste->memory_size/sizeof(align_data));
	printf("le nombre de tranche libre est   : %d \n",new_liste->nbr_tranches);
	printf("Espace memoire total %ld en block %ld espace memoire utilisable %ld en block %ld \n",ld_total_free_memory(liste),ld_total_free_memory(liste)/sizeof(align_data), ld_total_useful_memory(liste),ld_total_useful_memory(liste)/sizeof(align_data)  );
	node * nodei= ld_first(liste);
	int in=1;
	while(nodei!=NULL) 
	{
		int * data=(void *)nodei+sizeof(node) ;
		printf("(n%d previous  %ld next %ld  adresse %p data %d)   \n          |\n          |\n          v\n",in,nodei->previous,nodei->next, nodei,*data );
	        nodei= ld_next(liste,nodei);
		in++;
	}

printf("         end	\n");

}


void *ld_last(void *liste){
	head *new_liste=liste;
	if(new_liste->last==-1 )
	{
 	 printf("la liste est vide !!! donc pas de last ..merci ! \n");
 	 return NULL;
	}
	return (char *) new_liste->memory + new_liste->last*sizeof(align_data) ;
}



ptrdiff_t tranches_libre(void *liste,size_t neededblocs ,size_t *a)
{
head* new_liste=liste;

int nbroftranches=new_liste->nbr_tranches;
for(int i=0;i<nbroftranches;i++) 
{
	if(new_liste->tab_tranches[i].nb_blocs >= neededblocs )
	{
		*a=i;
		return new_liste->tab_tranches[i].decalage;
	}

}
return -1;

}


void *ld_compactify(void *liste)
{
	head* new_liste=liste;
	void * compactifed_memory  = malloc( new_liste->memory_size ) ;
	if(compactifed_memory==NULL){ printf("erreur allocation memory \n"); return NULL; }

	ptrdiff_t decalage=0;

	node * current_node=ld_first(liste);
	node * previous_node=current_node;

	while(current_node!=NULL){
	node * new_node= (void *)compactifed_memory+ decalage;
   	ld_get(liste, current_node,current_node->len*sizeof(align_data)- sizeof(node), compactifed_memory+ decalage + sizeof(node) );
	decalage+=current_node->len*sizeof(align_data);
	if(current_node==previous_node) new_node->previous=0;
	else  new_node->previous=-previous_node->len;
        new_node->next=current_node->len;
	previous_node=current_node;
	current_node=ld_next(liste,current_node );
	if(current_node==NULL) new_node->next=0;
	}

	if(previous_node!=NULL)
	{
	new_liste->first=0;
	new_liste->last=decalage/sizeof(align_data) -previous_node->len;
	}



	free(new_liste->memory);
	new_liste->memory=compactifed_memory;
	new_liste->nbr_tranches=1;
	new_liste->tab_tranches[0].decalage=decalage/sizeof(align_data);
	new_liste->tab_tranches[0].nb_blocs=new_liste->memory_size/sizeof(align_data)  -decalage/sizeof(align_data);

	return liste;
}


void * ld_insert_first(void *liste, size_t len, void *p_data){
     //il faut calculer le nombre de bloc 
	if(liste==NULL) return NULL;
	head* new_liste=liste;
	size_t newlen = nb_blocs(len)+ sizeof(node)/sizeof(align_data) ;
	size_t *a       ;
	size_t  b = -1  ;
	a=&b            ;
	ptrdiff_t decalage=tranches_libre(liste,newlen , a);
	if(decalage==-1) {
		printf("y'en plus de memoire  !!!!! essayer avec compatify ou add memory ...merci\n");
		return NULL;
	}


	node * new_node=((void *) new_liste->memory + decalage*sizeof(align_data) );
	if(new_node == NULL) return NULL;

	node* ld_f=ld_first(liste);


	if(ld_f==NULL)
	{
	new_liste->first=decalage;	 
	new_liste->last=decalage;
	((node*) new_node)->next=0;
	((node*) new_node)->previous=0;
	((node*) new_node)->len = newlen  ;
	}	
	else
	{

	new_liste->first=decalage;	
	
	ptrdiff_t decalagenext= decalage -( (align_data *) ld_f - (align_data *) new_liste->memory );	
	ld_f->previous=decalagenext;
	((node*) new_node)->next= - decalagenext;
	((node*) new_node)->previous=0;
	((node*) new_node)->len = newlen ;	
	}
	
	
	align_data *  new_data = p_data;
	memmove(new_node->data,new_data,len);
	new_liste->tab_tranches[b].decalage+= newlen;
	new_liste->tab_tranches[b].nb_blocs-= newlen ;
	size_t tmp=new_liste->tab_tranches[b].nb_blocs;
	if(tmp==0) {new_liste->tab_tranches[b].nb_blocs=SIZE_MAX; }
	qsort(new_liste->tab_tranches,new_liste->nbr_tranches, sizeof(tranche), compare_function); 
	if(tmp==0) new_liste->nbr_tranches--;
	new_liste->node_number++;	
	return new_node;	
}



void * ld_insert_last(void *liste, size_t len, void *p_data)
{
	if(liste==NULL) return NULL;
	head* new_liste=liste;
	size_t newlen=nb_blocs(len) +sizeof(node)/sizeof(align_data) ;
	size_t* a;
	size_t b=-1;
	a=&b;
	ptrdiff_t decalage=tranches_libre(liste,newlen , a);
	if(decalage==-1) {
		printf("y'en plus de memoire  !!!!! essayer avec compatify ou add memory ...merci\n");
		return NULL;
	}
	node * new_node=((void *) new_liste->memory + decalage*sizeof(align_data) );
	if (new_node == NULL)return NULL;

	node* ld_l=ld_last(liste);

	if(ld_l==NULL)
	{
	new_liste->first=decalage;	 
	new_liste->last=decalage;
	((node*) new_node)->next=0;
	((node*) new_node)->previous=0;
	((node*) new_node)->len = newlen ;
	}	
	else
	{
	new_liste->last=decalage;		
	ptrdiff_t decalagenext= decalage -( (align_data *) ld_l - (align_data *) new_liste->memory );	
	ld_l->next=decalagenext;
	((node*) new_node)->next= 0;
	((node*) new_node)->previous= -decalagenext;
	((node*) new_node)->len = newlen  ;
	}
	
	align_data *  new_data = p_data;
	memmove(new_node->data,new_data,len);
	new_liste->tab_tranches[b].decalage+=newlen;
	new_liste->tab_tranches[b].nb_blocs-=newlen ;
	size_t tmp=new_liste->tab_tranches[b].nb_blocs;
	if(tmp==0) {new_liste->tab_tranches[b].nb_blocs=SIZE_MAX; }
	qsort(new_liste->tab_tranches,new_liste->nbr_tranches, sizeof(tranche), compare_function); 
	if(tmp==0) new_liste->nbr_tranches--;
	new_liste->node_number++;
	return new_node;	
}
