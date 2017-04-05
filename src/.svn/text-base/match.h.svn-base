
#ifndef __MATCH_H__
#define __MATCH_H__

#include <board.h>
#include <e2.h>
#include <random.h>

// {{{ match_get_top_id()
int match_get_top_id(e2_t *e2, int x, int y)
{
   int id = 0;

	if(y-1>=0)
      id = board_get(e2, x, y-1);

	return id;
}
// }}}

// {{{ match_get_bottom_id()
int match_get_bottom_id(e2_t *e2, int x, int y)
{
   int id = 0;

	if(y+1<e2->side)
      id = board_get(e2, x, y+1);

	return id;
}
// }}}

// {{{ match_get_left_id()
int match_get_left_id(e2_t *e2, int x, int y)
{
   int id = 0;

	if(x-1>=0)
      id = board_get(e2, x-1, y);

	return id;
}
// }}}

// {{{ match_get_right_id()
int match_get_right_id(e2_t *e2, int x, int y)
{
   int id = 0;

	if(x+1<e2->side)
      id = board_get(e2, x+1, y);

	return id;
}
// }}}

// {{{ match_top()
int match_top(e2_t *e2, int x, int y)
{
   int id  = board_get(e2, x, y);
   int mid = -1;

	if(y-1>=0)
      mid = board_get(e2, x, y-1);

   if(mid==-1)
   {
      if(e2->tiles[id].top == 0)
         return 1;
      else
         return 0;
   }


   if(e2->tiles[id].top == 0)
      return 0;


   if(e2->tiles[id].top == e2->tiles[mid].bottom)
      return 1;
   else
      return 0;
} 
// }}}

// {{{ match_bottom()
int match_bottom(e2_t *e2, int x, int y)
{
   int id  = board_get(e2, x, y);
   int mid = -1;

	if(y+1<e2->side)
      mid = board_get(e2, x, y+1);


   if(mid==-1)
   {
      if(e2->tiles[id].bottom == 0)
         return 1;
      else
         return 0;
   }

   if(e2->tiles[id].bottom == 0)
      return 0;

   if(e2->tiles[id].bottom == e2->tiles[mid].top)
      return 1;
   else
      return 0;
} 
// }}}

// {{{ match_right()
int match_right(e2_t *e2, int x, int y)
{
   int id  = board_get(e2, x, y);
   int mid = -1;

	if(x+1<e2->side)
      mid = board_get(e2, x+1, y);


   if(mid==-1)
   {
      if(e2->tiles[id].right == 0)
         return 1;
      else
         return 0;
   }


   if(e2->tiles[id].right == 0)
      return 0;

   if(e2->tiles[id].right == e2->tiles[mid].left)
      return 1;
   else
      return 0;
} 
// }}}

// {{{ match_left()
int match_left(e2_t *e2, int x, int y)
{
   int id  = board_get(e2, x, y);
   int mid = -1;

	if(x-1>=0)
      mid = board_get(e2, x-1, y);


   if(mid==-1)
   {
      if(e2->tiles[id].left == 0)
         return 1;
      else
         return 0;
   }


   if(e2->tiles[id].left == 0)
      return 0;

   if(e2->tiles[id].left == e2->tiles[mid].right)
      return 1;
   else
      return 0;
} 
// }}}

// {{{ match_get_num_errors()
int match_get_num_errors(e2_t *e2, int x, int y)
{
	if(x<0 || y<0 || x>=e2->side || y>=e2->side)
		return 0;

   int count=0;

   if(!match_top(e2, x, y)) 	count ++;
   if(!match_bottom(e2, x, y))count ++;
   if(!match_right(e2, x, y))	count ++;
   if(!match_left(e2, x, y))	count ++;

   return count;
}
// }}}

// {{{ match_get_num_total_errors() 
int match_get_num_total_errors(e2_t *e2)
{
   int count = 0;
   int x;
   int y;
   for(y=0; y<e2->side; y++)
      for(x=0; x<e2->side; x++)
         count += match_get_num_errors(e2, x, y);

   return count;
}
// }}}

// {{{ match_get_num_total_errors_in_square() 
int match_get_num_total_errors_in_square(e2_t *e2, int center_x, int center_y, int radius)
{
	int ix = center_x - radius;
	if(ix<0) ix=0;

	int iy = center_y - radius;
	if(iy<0) iy=0;

	int fx = center_x + radius;
	if(fx >= e2->side) fx = e2->side-1;

	int fy = center_y + radius;
	if(fy >= e2->side) fy = e2->side-1;


   int count = 0;
   int x;
   int y;
   for(y=iy; y<fy; y++)
      for(x=ix; x<fx; x++)
         count += match_get_num_errors(e2, x, y);

   return count;
}
// }}}

// {{{ match_get_replacement()
int match_get_replacement(e2_t *e2, int top_id, int left_id, 
							 int bottom_id, int right_id)
{
	int len=0;
	int best_tile_id;
	int found=0;

	// 4-faces (1)
	len=0;
	if(!found)
		while(t4cf[e2->tiles[top_id].bottom][e2->tiles[left_id].right]
				[e2->tiles[bottom_id].top][e2->tiles[right_id].left]
				[len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t4cf[e2->tiles[top_id].bottom][e2->tiles[left_id].right]
			[e2->tiles[bottom_id].top][e2->tiles[right_id].left]
			[random_get(len)];
		found=1;
	}

	// 3-faces r0 (2)
	len=0;
	if(!found)
		while(t3cf[e2->tiles[top_id].bottom][e2->tiles[left_id].right]
				[e2->tiles[bottom_id].top][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t3cf[e2->tiles[top_id].bottom][e2->tiles[left_id].right]
			[e2->tiles[bottom_id].top][random_get(len)];
		found=2;
	}

	// 3-faces r1 (3)
	len=0;
	if(!found)
		while(t3cf[e2->tiles[left_id].right][e2->tiles[bottom_id].top]
				[e2->tiles[right_id].left][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t3cf[e2->tiles[left_id].right][e2->tiles[bottom_id].top]
			[e2->tiles[right_id].left][random_get(len)];
		found=3;
	}

	// 3-faces r2 (4)
	len=0;
	if(!found)
		while(t3cf[e2->tiles[bottom_id].top][e2->tiles[right_id].left]
				[e2->tiles[top_id].bottom][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t3cf[e2->tiles[bottom_id].top][e2->tiles[right_id].left]
			[e2->tiles[top_id].bottom][random_get(len)];
		found=4;
	}

	// 3-faces r3 (5)
	len=0;
	if(!found)
		while(t3cf[e2->tiles[right_id].left][e2->tiles[top_id].bottom]
				[e2->tiles[left_id].right][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t3cf[e2->tiles[right_id].left][e2->tiles[top_id].bottom]
			[e2->tiles[left_id].right][random_get(len)];
		found=5;
	}

	// 2-faces r0 (6)
	len=0;
	if(!found)
		while(t2cf[e2->tiles[top_id].bottom][e2->tiles[left_id].right]
				[len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t2cf[e2->tiles[top_id].bottom][e2->tiles[left_id].right]
			[random_get(len)];
		found=6;
	}

	// 2-faces r1 (7)
	len=0;
	if(!found)
		while(t2cf[e2->tiles[left_id].right][e2->tiles[bottom_id].top]
				[len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t2cf[e2->tiles[left_id].right][e2->tiles[bottom_id].bottom]
			[random_get(len)];
		found=7;
	}

	// 2-faces r2 (8)
	len=0;
	if(!found)
		while(t2cf[e2->tiles[bottom_id].top][e2->tiles[right_id].left]
				[len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t2cf[e2->tiles[bottom_id].top][e2->tiles[right_id].left]
			[random_get(len)];
		found=8;
	}

	// 2-faces r3 (9)
	len=0;
	if(!found)
		while(t2cf[e2->tiles[right_id].left][e2->tiles[top_id].bottom]
				[len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t2cf[e2->tiles[right_id].left][e2->tiles[top_id].bottom]
			[random_get(len)];
		found=9;
	}

	// 2-faces r0 oposite (10)
	len=0;
	if(!found)
		while(t2of[e2->tiles[bottom_id].top][e2->tiles[top_id].bottom]
				[len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t2of[e2->tiles[bottom_id].top][e2->tiles[top_id].bottom]
			[random_get(len)];
		found=10;
	}

	// 2-faces r1 oposite (11)
	len=0;
	if(!found)
		while(t2of[e2->tiles[right_id].left][e2->tiles[left_id].right]
				[len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = 
			t2of[e2->tiles[right_id].left][e2->tiles[left_id].right]
			[random_get(len)];
		found=11;
	}


	// 1-face r0 (12)
	len=0;
	if(!found)
		while(t1cf[e2->tiles[top_id].bottom][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = t1cf[e2->tiles[top_id].bottom][random_get(len)];
		found=12;
	}

	// 1-face r1 (13)
	len=0;
	if(!found)
		while(t1cf[e2->tiles[left_id].right][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = t1cf[e2->tiles[left_id].right][random_get(len)];
		found=13;
	}

	// 1-face r2 (14)
	len=0;
	if(!found)
		while(t1cf[e2->tiles[bottom_id].top][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = t1cf[e2->tiles[bottom_id].top][random_get(len)];
		found=14;
	}

	// 1-face r3 (15)
	len=0;
	if(!found)
		while(t1cf[e2->tiles[right_id].left][len]!=0) len++;
	if(len!=0 && !found)
	{
		best_tile_id = t1cf[e2->tiles[right_id].left][random_get(len)];
		found=15;
	}

	if(found)
	{
		//printf("found: %d\n\n", found);
		return best_tile_id;
	}

	return 0;
}
// }}}



#endif



