
#ifndef __INPUT_H__
#define __INPUT_H__

#include<stdio.h>
#include<stdlib.h>
#include<e2.h>

// {{{ input_get_ntiles(): read file and get num tiles
int input_get_ntiles(const char *input_file)
{
   int ntiles = 0;

   FILE *f = fopen(input_file, "r");
   if(!f)
   {
      perror("fopen()");
      return ntiles;
   }

   fscanf(f, "ntiles: %d", &ntiles);
   fclose(f);

   return ntiles;
}
// }}}

// {{{ input_read_tiles(): fill 'tiles' structure
void input_read_tiles(e2_t *e2, const char *input_file)
{
   int np = 0;

   FILE *f = fopen(input_file, "r");
   if(!f)
   {
      perror("fopen()");
      exit(0);
   }

   fscanf(f, "ntiles: %d", &np);
   if(np!=e2->ntiles)
   {
      printf("incorrect ntiles\n");
      exit(0);
   }
   
   int count = 1;
   while(!feof(f) || count==e2->ntiles)
   {
      fscanf(f, "%d %d %d %d %d", 
         &e2->tiles[count].id,
         &e2->tiles[count].top,
         &e2->tiles[count].left,  
         &e2->tiles[count].bottom, 
         &e2->tiles[count].right); 
      count++;
   }

	e2->tiles[0].id=0;
	e2->tiles[count].top=0;
	e2->tiles[count].left=0; 
	e2->tiles[count].bottom=0; 
	e2->tiles[count].right=0;

   fclose(f);
}
// }}}




#endif
