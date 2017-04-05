
#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <e2.h>
#include <board.h>

// {{{ random_seed()
void random_seed () 
{
   /*
   int s;
   FILE *f;
   f = fopen("/dev/urandom", "r");
   fscanf(f, "%d", &s);
   fclose(f);

   printf("seed: %d\n", s);

	srand(s);
   */

   srand(time(NULL));
}
// }}}

// {{{ random_get()
int random_get(int max) 
{
	return (rand() % max );
}
// }}}

// {{{ random_get_xy() 
void random_get_xy(int side, int *x, int *y)
{
   *x = random_get(side);
   *y = random_get(side);
}
// }}}

// {{{ random_get_xy_in_square() 
void random_get_xy_in_square(int side, int *x, int *y, int center_x, int center_y, int radius)
{
	int my_x;
	int my_y;

	// random position inside square
	for(;;)
	{
	 	my_x = center_x + random_get(radius)*(random_get(2)?1:-1);
   	my_y = center_y + random_get(radius)*(random_get(2)?1:-1);
		
		if(my_x==center_x && my_y==center_y)
			continue;

		if(my_x>=0 && my_y>=0 && my_x<side && my_y<side)
			break;
	}

	*x = my_x;
	*y = my_y;
}
// }}}

// {{{ random_get_optimal_xy() 
void random_get_optimal_xy(e2_t *e2, int src_x, int src_y, int *x, int *y)
{
   int nzero=0;

   if(e2->tiles[board_get(e2, src_x, src_y)].top==0) 
      nzero ++;
   if(e2->tiles[board_get(e2, src_x, src_y)].right==0) 
      nzero ++;
   if(e2->tiles[board_get(e2, src_x, src_y)].bottom==0) 
      nzero ++;
   if(e2->tiles[board_get(e2, src_x, src_y)].left==0) 
      nzero ++;

   // corner
   if(nzero==2)
   {
      switch(random_get(4))
      {
         case 0:
            *x = 0;
            *y = 0;
         break;
         
         case 1:
            *x = e2->side-1;
            *y = 0;
         break;

         case 2:
            *x = 0;
            *y = e2->side-1;
         break;

         case 3:
            *x = e2->side-1;
            *y = e2->side-1;
         break;
      }

      return;
   }
 
   // side
   if(nzero==1)
   {
      if(random_get(2))
      {
         *x = 0;
         if(*y == 0) *y+=1;
         if(*y == e2->side-1) *y-=1;
      }
      else
      {  
         *y = 0;
         if(*x == 0) *x+=1;
         if(*x == e2->side-1) *x -=1;
      }

      return;
   }



   // inside
   do  { random_get_xy(e2->side, x, y); }
   while(*x==0 || *y==0 || *x==e2->side-1 || *y==e2->side-1);

  }
// }}}

// {{{ random_get_optimal_xy_in_square() 
void random_get_optimal_xy_in_square(e2_t *e2, int src_x, int src_y, int *x, int *y, int center_x, int center_y, int radius)
{
   int nzero=0;

   if(e2->tiles[board_get(e2, src_x, src_y)].top==0) 
      nzero ++;
   if(e2->tiles[board_get(e2, src_x, src_y)].right==0) 
      nzero ++;
   if(e2->tiles[board_get(e2, src_x, src_y)].bottom==0) 
      nzero ++;
   if(e2->tiles[board_get(e2, src_x, src_y)].left==0) 
      nzero ++;

   // corner
   if(nzero==2)
   {
      switch(random_get(4))
      {
         case 0:
            *x = 0;
            *y = 0;
         break;
         
         case 1:
            *x = e2->side-1;
            *y = 0;
         break;

         case 2:
            *x = 0;
            *y = e2->side-1;
         break;

         case 3:
            *x = e2->side-1;
            *y = e2->side-1;
         break;
      }

      return;
   }

   // side
   if(nzero==1)
   {
      if(random_get(2))
      {
         *x = 0;
         if(*y == 0) *y+=1;
         if(*y == e2->side-1) *y-=1;
      }
      else
      {  
         *y = 0;
         if(*x == 0) *x+=1;
         if(*x == e2->side-1) *x -=1;
      }

      return;
   }


   // inside
   do  
	{ 
		random_get_xy_in_square(e2->side, x, y, center_x, center_y, radius); 
		//printf("(%d,%d) - (%d,%d)\n", *x, *y, center_x, center_y);
	}
   while(*x==0 || *y==0 || *x==e2->side-1 || *y==e2->side-1);

}
// }}}

// {{{ random_get_xy_by_groups()
// return only (x,y) pairs close to center. max_d defines the maximal distance.
void random_get_xy_by_groups(e2_t *e2, int src_x, int src_y, int *x, int *y)
{
   int max_d = 3; 
   int max_it = e2->ntiles*e2->ntiles;

   static int center_x = 0;
   static int center_y = 0;
   static int it = 0;   

   if(it>max_it || (center_x==0 && center_y==0))
   {
      random_get_xy(e2->side, &center_x, &center_y);
      if(debug)
         printf("center: (%d, %d)\n", center_x, center_y);
   }
   

   random_get_optimal_xy(e2, src_x, src_y, x, y);

   if(*x > center_x)
      while(*x - center_x > max_d)
         *x -= 1;

   if(*x < center_x)
      while(center_x - *x > max_d)
         *x += 1;

   if(*y > center_y)
      while(*y - center_y > max_d)
         *y -= 1;

   if(*y < center_y)
      while(center_y - *y > max_d)
         *y += 1;
}
// }}}

#endif



