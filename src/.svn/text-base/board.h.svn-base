
#ifndef __BOARD_H__
#define __BOARD_H__


// {{{ board_get/_set: board get/set methods
#define board_set(e2, x, y, value) (e2)->board[(e2)->side*(y) + x]=value
#define board_get(e2, x, y) (e2)->board[(e2)->side*(y) + x]
// }}}

// {{{ board_set_tiles(): initialize board
void board_set_tiles(e2_t *e2)
{
	// force 139(2) to (7,8) 
	short is_e2_puzzle=0;
	if(e2->ntiles == 256)
	{
		board_set(e2, 7, 8, 139);
		e2->tiles[139].x=7;
		e2->tiles[139].y=8;

		int a = e2->tiles[139].top;
		e2->tiles[139].top = e2->tiles[139].bottom;
		e2->tiles[139].bottom = a;
		a = e2->tiles[139].left;
		e2->tiles[139].left = e2->tiles[139].right;
		e2->tiles[139].right = a;

		is_e2_puzzle=1;		
	}
	

   int i=1;
	int x, y;
	for(y=0; y<e2->side; y++)
	{
		for(x=0; x<e2->side; x++)
		{
			if(is_e2_puzzle && (i==139 || (x==7 && y==8)))
			{
				i++;
				continue;
			}

			board_set(e2, x, y, i);
			e2->tiles[i].x = x;
			e2->tiles[i].y = y;
			i++;
		}
	}
}
// }}}

// {{{ board_swap_tiles(): swap two tiles in board
void board_swap_tiles(e2_t *e2, int src_x, int src_y, int dst_x, int dst_y)
{
	// force 139(2) to (7,8) 
	if(e2->ntiles == 256)
	{
		if((src_x==7 && src_y==8) || (dst_x==7 && dst_y==8))
			return;
	}

   int src_id = board_get(e2, src_x, src_y);
   int dst_id = board_get(e2, dst_x, dst_y);
   board_set(e2, src_x, src_y, dst_id);
   board_set(e2, dst_x, dst_y, src_id);
	e2->tiles[src_id].x = dst_x;
	e2->tiles[src_id].y = dst_y;
	e2->tiles[dst_id].x = src_x;
	e2->tiles[dst_id].y = src_y;

//printf("board_swap_tiles: %d(%d,%d) %d(%d,%d)\n", src_id, src_x, src_y, dst_id, dst_x, dst_y);
} 
// }}}






#endif

