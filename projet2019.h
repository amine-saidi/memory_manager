#ifndef _H_PROJET2019_
#define _H_PROJET2019_



typedef struct {
ptrdiff_t decalage;
size_t nb_blocs;

} tranche;



typedef union{
intmax_t a;
void *adr;
long double c;
}align_data;


typedef struct{
ptrdiff_t next;
ptrdiff_t previous;
size_t len;
align_data data[];
}node;


typedef struct{
void *memory;
//pointeur vers la memoire
ptrdiff_t first; //ptrdiff_t ou pointeur
ptrdiff_t last; //ptrdiff_t ou pointeur
ptrdiff_t libre; //ptrdiff_t ou pointeur si la liste de tranches
//toute autre information

size_t memory_size;
tranche * tab_tranches;
int node_number;
int nbr_tranches;

} head;

// ---------------------------------------------------- //
size_t nb_blocs(size_t o);
void *ld_create( size_t nboctets );
void *ld_first(void *liste);
void *ld_last(void *liste);
ptrdiff_t tranches_libre(void *liste,size_t neededblocs ,size_t *a);
void * ld_insert_first(void *liste, size_t len, void *p_data);
void * ld_insert_last(void *liste, size_t len, void *p_data);

void *ld_last(void *liste);
void *ld_next(void *liste, void *current);
void *ld_previous(void *liste, void *current);
void * ld_insert_before(void *liste, void *n, size_t len, void *p_data);
void * ld_insert_after(void *liste, void *n, size_t len, void *p_data);
void * ld_delete_node(void *liste, void *n);
// ---------------------------------------------------- //
void ld_destroy(void *liste);
void add_tranches(void *liste,size_t decalage,size_t len);
size_t ld_total_free_memory(void *liste);
void *ld_previous(void *liste, void *current);
size_t ld_total_useful_memory(void *liste);
int compare_function(const void *a,const void *b) ;
size_t ld_get(void *liste, void *current, size_t len, void *val);
void *ld_add_memory(void *liste, size_t nboctets);
void *ld_compactify(void *liste);
void afficher(void *liste);
node * seek_node2(void *liste, int index);
#endif
