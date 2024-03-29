#include "image.h"
#include "table.h"
#include <assert.h>
#include <stdio.h>

struct color_table{
  int color_num;
  int *colors;
  boolean owner;
  int dim;
};


color_table create_color_table(image self){
  color_table tab;
  int Dim = image_give_dim(self);
  assert(Dim>0 && Dim<=3);
  tab = (color_table)malloc(sizeof(struct color_table));
  tab->owner = true;  
  tab->dim = Dim;
  tab->color_num = image_give_largeur(self)*image_give_hauteur(self);
  tab->colors = malloc(tab->color_num*Dim*sizeof(color));
 
 
  int *array = malloc(Dim * sizeof(color));
  image_debut(self);
  for (int i = 0; i < tab->color_num; i++) {
        array = image_lire_pixel(self);
	image_pixel_suivant(self);
        for (int k = 0; k < Dim; k++){
            *(tab->colors+ i*Dim + k) = *(array+k);
        }
    } 
    /*il faudrait free ici */
    return tab;
}




boolean destroy_color_table(color_table tab){
	free(tab->colors);
	if (tab->owner == true){
		free(tab);
	}
	return(tab->owner);
}




color_table color_table_duplicate(color_table tab, int offset, int len){
	color_table dup_tab;
	assert(offset>-1);
	assert(len>0);
	dup_tab->owner = false;
  dup_tab->dim = tab->dim;
	dup_tab->color_num = len;
	dup_tab->colors = tab->colors + dup_tab->dim*offset; /*l'offset dépendra de la dimension*/
	return(dup_tab);
}





void color_table_get_color(color_table tab, int i, color* color_i){
  int Dim = tab->dim;
  assert(i<tab->color_num);
  
  for (int k=0; k<3; k++)
    *(color_i+k) = *(tab->colors +(i*Dim+k));
  }
  
  
  
  
void swap_tab(color_table tab, int i){
  int temp_tab[tab->dim];
  if (tab->dim == 1){
    *temp_tab = *(tab->colors+i);
    *(tab->colors+i) = *(tab->colors+i+1);
    *(tab->colors+i+1) = *temp_tab;
    }
  else{
    *temp_tab = *(tab->colors+i);
    *(temp_tab+1) = *(tab->colors+i+1);
    *(temp_tab+2) = *(tab->colors+i+2);
    *(tab->colors+i) = *(tab->colors+i+3);
    *(tab->colors+i) = *(tab->colors+i+4);
    *(tab->colors+i) = *(tab->colors+i+5);
    *(tab->colors+i+3) = *temp_tab;
    *(tab->colors+i+4) = *(temp_tab+1);
    *(tab->colors+i+5) = *(temp_tab+2);
    }
  }
  
    
void color_table_sort(color_table tab, axis x){
  int dim = tab->dim;
  int ax;
  int swap = 1;
  int i;
  if (x == red)
    ax = 0;
  if (x == green)
    ax = 1;
  if (x == blue)
    ax = 2;
  while (swap>0){
    swap = 0;
    for (i=0;i<tab->color_num;i++){
      if (tab->colors[ax+dim*i] > tab->colors[ax+dim*(i+1)]){
        swap_tab(tab,ax+dim*i);
        swap = 1;
        }
      }
    }
  }
  
