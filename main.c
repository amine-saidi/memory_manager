#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include"projet2019.h"
//#include"TP6.h"
#include <sys/time.h>
#include "listes_generiques.h"
#include <limits.h>


#define NTRANCHES 1024
#define NOPERATIONS 10

int main()
{

/*
char c[]="bonjour!";

head *hd=ld_create(290000000);

ld_insert_first(hd,9, c);


afficher(hd);

*/


//time_t begin ;
//time_t end ;
//double time_new_imp,time_old_imp,time_boucle_imp;

node * current;
int oper,pos,val;
int index, value,nbr_element=0;

struct timeval start, stop;
double secs = 0;



int a=6;
void * p_data=&a;
size_t len=4;


//begin = time( NULL)*1000;
gettimeofday(&start, NULL);

//dl_list * my_list;
//my_list = build_list(NULL,NULL);

liste l = creer_liste();
liste e;


srandom(0);

for(int i=0;i< NOPERATIONS;i++)
{

oper= random() % 5;
pos = random()%(nbr_element+1) ;
val = random();
int * data=malloc(sizeof(int));


switch ( oper % 5 )
{
	case 0 :
	{ 
	//printf("-------------------------------------------------------\n");
//	printf("--------operation : delete_node : position %d ---------\n",pos);	
	//printf("------------------------------------------------------\n");
    	 	 index=pos;
		 *data =val;
		 e=seek_node(l,index);
		 supprimer_element(e);		 
//     		 pop_at(my_list,index,&value);
		 nbr_element--;
		break;
	}
	case 1 :
	{ 
	//printf("------------------------------------------------------\n");
//	printf("--------          operation : insert_first   ---------\n");	
	//printf("------------------------------------------------------\n");
    	 	 index=pos;
		 *data =val;
     		 inserer_apres(l, data);
		 nbr_element++;
		break;
	}
	case 2 :
	{ 
	//printf("------------------------------------------------------\n");
//	printf("--------          operation : insert_last    ---------\n");	
//	printf("------------------------------------------------------\n");
    	 	 index=pos;
		 *data =val;
     		 inserer_avant(l, data);
  //   		 add_at(my_list,-1,value);
		 nbr_element++;
		break;
	}
	case 3 :
	{
	//printf("------------------------------------------------------\n");
//	printf("--------operation : insert_after : position %d---------\n",pos);	
	//printf("------------------------------------------------------\n");

    	 	 index=pos;
		 *data =val;
		 e=seek_node(l,index);
		 inserer_apres(e, data);
  //   		 add_at(my_list,index+1,value);
		 nbr_element++;
   		 break;
	}
	case 4 :
	{ 
	//printf("------------------------------------------------------\n");
//	printf("------ operation : insert_before: position %d---------\n",pos);	
	//printf("------------------------------------------------------\n");
    	 	 index=pos;
		 *data =val;
		 nbr_element++;
		 e=seek_node(l,index);
		 inserer_apres(e, data);
		 
   //  		 add_at(my_list,index-1,value);
		 
		break;
	}
	
}   

}
///imprimer_long(l);
//end = time( NULL)*1000;
//time_old_imp  =  difftime( end, begin );

//detruire_liste(l);

gettimeofday(&stop, NULL);
secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
printf("Temps de l'implémentation classique %.10f sec\n",secs);



srandom(0); 
//time_new_imp=0;

//begin = time( NULL );
gettimeofday(&start, NULL);


head *hd=ld_create(2900000);

 
for(int i=0;i< NOPERATIONS;i++)
{

oper= random() % 5;
pos = random()%(hd->node_number+1) ;
val = random();


switch ( oper )
{
	case 0 :
	{ 
//	printf("------------------------------------------------------\n");
//	printf("--------operation : delete_node : position %d   %d---------\n",pos,hd->node_number);	
//	printf("------------------------------------------------------\n");
		current=seek_node2(hd,pos);
		ld_delete_node(hd, current);
		break;
	}
	case 1 :
	{ 
//	printf("------------------------------------------------------\n");
//	printf("--------          operation : insert_first   ---------\n");	
//	printf("------------------------------------------------------\n");
		a=val;			
		ld_insert_first(hd, len, p_data);
		break;
	}
	case 2 :
	{ 
//	printf("------------------------------------------------------\n");
//	printf("--------          operation : insert_last    ---------\n");	
//	printf("------------------------------------------------------\n");
		a=val;			
		ld_insert_last(hd, len, p_data);
		break;
	}
	case 3 :
	{
//	printf("------------------------------------------------------\n");
//	printf("--------operation : insert_after : position %d---------\n",pos);	
//	printf("------------------------------------------------------\n");

		current=seek_node2(hd,pos);
		a=val;			
		ld_insert_after(hd, current, len, p_data);
		break;
	}
	case 4 :
	{ 
//		printf("------------------------------------------------------\n");
//	printf("------ operation : insert_before: position %d---------\n",pos);		
//	printf("------------------------------------------------------\n");
		a=val;			
		current=seek_node2(hd,pos);
		ld_insert_before(hd, current, len, p_data);
		break;
	}
	
}   

	//afficher(hd);

}
gettimeofday(&stop, NULL);
secs =  (double)(stop.tv_sec - start.tv_sec)+ (double)(stop.tv_usec - start.tv_usec) / 1000000 ;
printf("Temps de la nouvelle implémentation %.10f sec\n",secs);

//end = time( NULL);
//time_new_imp =  difftime( end, begin );

//afficher(hd);
ld_destroy(hd);
size_t ok=SIZE_MAX;
printf("%zu",ok);
//printf("La nouvelle implimentation à fini en %.24lf milsec, L'ancien en %.24lf milsec\n", time_new_imp,time_old_imp);
//printf( " l'ancien en %.24lf \n",time_old_imp );  
//print_list(my_list,0);




return 0;
}
