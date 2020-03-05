#ifndef _H_TP6_
#define _H_TP6_


struct nodex {int val; struct nodex * prev; struct nodex * next;};
typedef struct nodex nodex;

struct dl_list{nodex * first; nodex * last;};
typedef struct dl_list dl_list;

// Q1 and Q2
nodex * build_node(int val, nodex * prev, nodex * next);
dl_list * build_list(nodex * first, nodex * last);

// Q3
short add_first(dl_list * target_list, int value);
short add_last(dl_list * target_list, int value);

// Q4
short read_first(dl_list * target_list, int * addr);
short read_last(dl_list * target_list, int * addr);

// Q5
void print_list(dl_list * target_list, short rev);

// Q6
int size(dl_list * target_list);

// Q7
void clean(dl_list * target_list);

// Q8
short pop_first(dl_list * target_list, int * addr);
short pop_last(dl_list * target_list, int * addr);

// Q9
nodex * seek_node(dl_list * target_list, int index);

// Q10
short read_at(dl_list * target_list, int index, int * addr);

// Q11
short pop_at(dl_list * target_list, int index, int * addr);

// Q12
short add_at(dl_list * target_list, int index, int value);

// End of mandatory part

// Q18
void basic_memory_leak_test();

// Tests
void q9_12();

#endif
