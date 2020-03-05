#include <stdio.h>
#include <stdlib.h>
#include "TP6.h"

// Q1
// Allocates memory for a node, initializes its fields and returns a
// pointer to it
// Returns NULL in case of failure
nodex * build_node(int val, nodex * prev, nodex * next){
  nodex * result = malloc(sizeof(nodex));
  if (result == NULL)
    return NULL;
  result->val = val;
  result->prev = prev;
  result->next = next;
  return result;
}


// Q2
// Allocates memory for a doubly linked list, initializes its fields
// and returns a pointer to it
// Returns NULL in case of failure
dl_list * build_list(nodex * first, nodex * last){
  dl_list * result = malloc(sizeof(dl_list));
  if (result == NULL)
    return NULL;
  result->first = first;
  result->last = last;
  return result;
}


// Q3
// Adds an integer at the beginning of the list
// Returns 1 for success, 0 for failure
short add_first(dl_list * target_list, int value){
  if (target_list==NULL)
    return 0;
  nodex * old_first = target_list->first;
  nodex * new_first;
  if (old_first != NULL) /* There already was a first element */
    {
      new_first = build_node(value,NULL,old_first);
      if (new_first == NULL)
	return 0;
      old_first->prev = new_first;
    }
  else /* List was empty */
    {
      new_first = build_node(value,NULL,NULL);
      if (new_first == NULL)
	return 0;
      target_list->last = new_first;
    }
  target_list->first = new_first;
    
  return 1;
};

// Adds an integer at the end of the list
// Returns 1 for success, 0 for failure
short add_last(dl_list * target_list, int value){
  if (target_list==NULL)
    return 0;
  nodex * old_last = target_list->last;
  nodex * new_last;
  if (old_last != NULL) /* There already was a last element */
    {
      new_last = build_node(value,old_last,NULL);
      if (new_last == NULL)
	return 0;
      old_last->next = new_last;
    }
  else /* List was empty */
    {
      new_last = build_node(value,NULL,NULL);
      if (new_last == NULL)
	return 0;
      target_list->first = new_last;
    }
  target_list->last = new_last;
    
  return 1;
};


// Q4
// Writes the content of the first element of the doubly linked list
// at a given address
// Returns 1 for success, 0 for failure
short read_first(dl_list * target_list, int * addr){
  if (target_list == NULL)
    return 0;
  if (target_list->first == NULL)
    return 0;
  *addr = target_list->first->val; /* we assume addr is a valid address */
  return 1;
}

// Writes the content of the first element of the doubly linked list
// at a given address
// Returns 1 for success, 0 for failure
short read_last(dl_list * target_list, int * addr){
  if (target_list == NULL)
    return 0;
  if (target_list->last == NULL)
    return 0;
  *addr = target_list->last->val; /* we assume addr is a valid address */
  return 1;
}


// Q5
// Prints a list on the standard output, in standard order if rev==0,
// in reverse order if rev==1
void print_list(dl_list * target_list, short rev){
  nodex * current;
  if (rev==0)
    {
      current = target_list->first;
      printf("[");
      while(current != NULL)
	{
	  printf(" %d",current->val);
	  current = current->next;
	}
      printf(" ]\n");
    }
  else if(rev==1)
    {
      current = target_list->last;
      printf("[");
      while(current != NULL)
	{
	  printf(" %d",current->val);
	  current = current->prev;
	}
      printf(" ]\n");
    }
}


// Q6
// Computes the size of a (non-NULL) doubly linked list by traversal
int size(dl_list * target_list){
  int result = 0;
  nodex * current = target_list->first;
  while(current != NULL)
    {
      result++;
      current = current->next;
    }
  return result;
}


// Q7
// Frees all memory associated to a given (non-NULL) doubly linked list
void clean(dl_list * target_list){
  nodex * current = target_list->first, * after;
  while(current != NULL) /* Loop frees memory node by nodex */
    {
      after = current->next;
      free(current);
      current = after;
    }
  free(target_list); /* Frees memory of the dl_list structure */
}


// Q8
// Writes the content of the last element of the doubly linked list
// at a given address and removes it from the list
// Returns 1 for success, 0 for failure 
short pop_first(dl_list * target_list, int * addr){
  if (target_list == NULL)
    return 0;
  if (target_list->first == NULL)
    return 0;
  *addr = target_list->first->val; /* we assume addr is a valid address */
  nodex * trash = target_list->first, * new_first = trash->next;
  if(new_first != NULL)
    { /* List has more than one element */
      target_list->first = new_first;
      new_first->prev = NULL;
    }
  else
    { /* List had a single element */
      target_list->first = NULL;
      target_list->last = NULL;
    }
  free(trash); /* Frees the old first element */
    
  return 1;
}

// Writes the content of the first element of the doubly linked list
// at a given address and removes it from the list
// Returns 1 for success, 0 for failure
short pop_last(dl_list * target_list, int * addr){
  if (target_list == NULL)
    return 0;
  if (target_list->last == NULL)
    return 0;
  *addr = target_list->last->val; /* we assume addr is a valid address */
  nodex * trash = target_list->last, * new_last = trash->prev;
  if(new_last != NULL)
    { /* List has more than one element */
      target_list->last = new_last;
      new_last->next = NULL;
    }
  else
    { /* List had a single element */
      target_list->last = NULL;
      target_list->first = NULL;
    }
  free(trash); /* Frees the old last element */
  
  return 1;
}


// Q9
// Looks for a node of a certain index in a list
nodex * seek_node(dl_list * target_list, int index){
  nodex * current;
  if (index >= 0)
    {
      current = target_list->first;
      while(current != NULL && index > 0)
	{
	  index--;
	  current = current->next;
	}
    }
  else /* index < 0*/
    {
      current = target_list->last;
      while(current != NULL && index < -1)
	{
	  index++;
	  current = current->prev;
	}
    }
  
  return current;
}


// Q10
// Reads a node at a given index in the list by writing its value at a
// given address
// Returns 1 for success, 0 for failure
short read_at(dl_list * target_list, int index, int * addr){
  nodex * index_node = seek_node(target_list, index);
  if (index_node == NULL)
    return 0;
  * addr = index_node->val;
  return 1;
}


// Q11
// Reads a node at a given index in the list by writing its value at a
// given address, and then remove it
// Returns 1 for success, 0 for failure
short pop_at(dl_list * target_list, int index, int * addr){
  nodex * index_node = seek_node(target_list, index);
  if (index_node == NULL)
    return 0;
  * addr = index_node->val;

  if(index_node->next != NULL)
    index_node->next->prev = index_node->prev;
  else /* popped node was the last node of the list */
    target_list->last = index_node->prev;

  if(index_node->prev != NULL)
    index_node->prev->next = index_node->next;
  else /* popped node was the first node of the list */
    target_list->first = index_node->next;
  
  free(index_node);
  return 1;
}

// Q12
// Returns 1 for success, 0 for failure
short add_at(dl_list * target_list, int index, int value){
  if (index == 0)
    return add_first(target_list, value);
  if (index == -1)
    return add_last(target_list, value);

  nodex * index_node, * new_node;
  if (index >= 0)
    {  /* We go from the start */
      index_node = seek_node(target_list, index-1);
      if (index_node == NULL)
	return 0;
      new_node = build_node(value, index_node, index_node->next);
      index_node->next = new_node;
      if (new_node->next == NULL) /* New node replaces index_node as last */
	target_list->last = new_node;
      else
	new_node->next->prev = new_node;
    }
  else
    {  /* We go from the end */
      index_node = seek_node(target_list, index+1);
      if (index_node == NULL)
	return 0;
      new_node = build_node(value, index_node->prev, index_node);
      index_node->prev = new_node;
      if (new_node->prev == NULL) /* New node replaces index_node as first */
	target_list->first = new_node;
      else
	new_node->prev->next = new_node;
    }

  return 1;
}




// Q18
// Tests for a memory leak by creating a large list many times and
// deallocating it, with stops in between, so that the user can look
// if the memory footprint of the program continues to grow when it
// shouldn't (it should stop growing after the first allocation run).
void basic_memory_leak_test(){
  dl_list * my_list;
  my_list = build_list(NULL,NULL);

  int i,j,x;
  int n,m;
  printf("How many elements do you want?\n");
  scanf("%d",&n);
  printf("How many runs do you want?\n");
  scanf("%d",&m);
  for(j = 0; j < m; j++){
    my_list = build_list(NULL,NULL);
    for(i = 0; i < n; i++)
      add_last(my_list,i);
    printf("Memory filled for the %dth time\n",j+1);
    scanf("%d",&x);
    clean(my_list);
    printf("Memory freed for the %dth time\n",j+1);
    scanf("%d",&x);
  }
  printf("End of the program\n");
  scanf("%d",&x);
}


/* ------------ Test functions ------------ */


// Interactive test for questions q9-12
void q9_12(){
  dl_list * my_list;
  my_list = build_list(NULL,NULL);
  char command = 's';

  int index, value;
  short exit_code;

  printf("Available commands: 'q'uit, 'r'ead, 'a'dd, 'p'op, 's'how\n");
  
  while (command != 'q'){
    if (command == 'a' || command == 'p' || command == 's')
      print_list(my_list,0);
    scanf("%c",&command);
    if (command == 'a') { /* add */
      scanf("%d %d",&index,&value);
      add_at(my_list,index,value);
    } else if (command == 'p') { /* pop */
      scanf("%d",&index);
      exit_code = pop_at(my_list,index,&value);
      if (exit_code)
	printf("value popped from %d: %d\n",index,value);
      else
	printf("invalid index: %d\n",index);
    } else if (command == 'r'){ /* read */
      scanf("%d",&index);
      exit_code = read_at(my_list,index,&value);
      if (exit_code)
	printf("value read at %d: %d\n",index,value);
      else
	printf("invalid index: %d\n",index);
    }
  }
}

