
#ifndef __ALGO_H__
#define __ALGO_H__

#include <match.h>


// {{{ random_solver()
// Realiza sustituciones de piezas al azar durante niterationes
int random_solver(e2_t *e2, int niterations)
{
	int src_x = 0;
	int src_y = 0;
	int dst_x = 0;
	int dst_y = 0;
	int i;
	
	for(i=0; i<niterations; i++)
	{
		src_x = random_get(e2->side);
  		src_y = random_get(e2->side);

		do 
		{ 
			random_get_optimal_xy(e2, src_x, src_y, &dst_x, &dst_y); 
			//printf("(%d,%d) - (%d,%d)\n", src_x, src_y, dst_x, dst_y);
		}
      while(src_x==dst_x && src_y==dst_y);


   	int i_merror = match_get_num_total_errors(e2);

		board_swap_tiles(e2, src_x, src_y, dst_x, dst_y); 
      rotation_auto(e2, src_x, src_y);        
      rotation_auto(e2, dst_x, dst_y);        

   	int f_merror = match_get_num_total_errors(e2);

		if(i_merror > f_merror)
			continue;
		else
		{
			// undo
			board_swap_tiles(e2, dst_x, dst_y, src_x, src_y); 
	      rotation_auto(e2, src_x, src_y);        
   	   rotation_auto(e2, dst_x, dst_y);        
		}
	}
   
	return  match_get_num_total_errors(e2);
}
// }}}

// {{{ random_optimal_solver()
// Sustituye piezas aleatorias del tablero por las piezas que mejor encajan
int random_optimal_solver(e2_t *e2, int niterations)
{
	int best_tile_id = 0;
	int x;
	int y;
	int i;

	for(i=0; i<niterations; i++)
	{

		x = random_get(e2->side);
  		y = random_get(e2->side);

		if(match_get_num_errors(e2, x, y)==0)
			continue;


		// find best candidate
		int top_id = match_get_top_id(e2, x, y);
		int left_id = match_get_left_id(e2, x, y);
		int right_id = match_get_right_id(e2, x, y);
		int bottom_id = match_get_bottom_id(e2, x, y);

		best_tile_id = 
			match_get_replacement(e2, top_id, left_id, bottom_id, right_id);


		if(best_tile_id)
		{
			int src_x = x;
			int src_y = y;
			int dst_x = e2->tiles[best_tile_id].x;
			int dst_y = e2->tiles[best_tile_id].y;

   		int i_merror = match_get_num_total_errors(e2);

			board_swap_tiles(e2, src_x, src_y, dst_x, dst_y); 
			rotation_auto(e2, src_x, src_y);        
			rotation_auto(e2, dst_x, dst_y);        

			int f_merror = match_get_num_total_errors(e2);

			if(i_merror > f_merror)
				continue;
			else
			{
				// undo
				board_swap_tiles(e2, dst_x, dst_y, src_x, src_y); 
				rotation_auto(e2, src_x, src_y);        
				rotation_auto(e2, dst_x, dst_y);        
			}
		}
	}

	return  match_get_num_total_errors(e2);
}
// }}}

// {{{ square_solver()
// Se construye un cuadrado alrededor del centro.
// A continuacion, durante niterations, se buscan piezas de cualquire
// posicion del tablero que encajen dentro del cuadrado.
int  square_solver(e2_t *e2, int cx, int cy, int radius, int niterations)
{
	int center_x = cx;
   int center_y = cy;
	int src_x = 0;
	int src_y = 0;
	int dst_x = 0;
	int dst_y = 0;
	int i;
	
	for(i=0; i<niterations;)
	{

		do 
		{		
			i++;
			random_get_xy_in_square(e2->side, &src_x, &src_y, 
				center_x, center_y, radius);

			if(match_get_num_errors(e2, src_x, src_y)==0)
				continue;

			int top_id = match_get_top_id(e2, src_x, src_y);
			int left_id = match_get_left_id(e2, src_x, src_y);
			int right_id = match_get_right_id(e2, src_x, src_y);
			int bottom_id = match_get_bottom_id(e2, src_x, src_y);
			int id=match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

			if(!id) // TODO: check it
				continue;

			dst_x = e2->tiles[id].x;
			dst_y = e2->tiles[id].y;
		}
      while(src_x==dst_x && src_y==dst_y && i<niterations);



   	int i_merror = 
			match_get_num_total_errors_in_square(e2, center_x, center_y, radius);

		board_swap_tiles(e2, src_x, src_y, dst_x, dst_y); 
      rotation_auto(e2, src_x, src_y);        
      rotation_auto(e2, dst_x, dst_y);        

   	int f_merror = 
			match_get_num_total_errors_in_square(e2, center_x, center_y, radius);

		if(f_merror==0)
			break;

		if(i_merror > f_merror)
		{
			//printf("swap: (%d,%d) (%d,%d)\n", src_x, src_y, dst_x, dst_y);
			continue;
		}
		else
		{
			// undo
			board_swap_tiles(e2, dst_x, dst_y, src_x, src_y); 
	      rotation_auto(e2, src_x, src_y);        
   	   rotation_auto(e2, dst_x, dst_y);        
		}
	}
   
	return  match_get_num_total_errors(e2);
}
// }}}

// {{{ random_square_solver()
// Se busca un centro aleatorio del tablero y se construye un cuadrado.
// A continuacion, durante niterations, se buscan piezas de cualquire
// posicion del tablero que encajen dentro del cuadrado.
int  random_square_solver(e2_t *e2, int radius, int niterations)
{
	int center_x = random_get(e2->side);
   int center_y = random_get(e2->side);
	int src_x = 0;
	int src_y = 0;
	int dst_x = 0;
	int dst_y = 0;
	int i;
	
	for(i=0; i<niterations;)
	{

		do 
		{		
			i++;
			random_get_xy_in_square(e2->side, &src_x, &src_y, 
				center_x, center_y, radius);

			if(match_get_num_errors(e2, src_x, src_y)==0)
				continue;

			int top_id = match_get_top_id(e2, src_x, src_y);
			int left_id = match_get_left_id(e2, src_x, src_y);
			int right_id = match_get_right_id(e2, src_x, src_y);
			int bottom_id = match_get_bottom_id(e2, src_x, src_y);
			int id=match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

			if(!id) // TODO: check it
				continue;

			dst_x = e2->tiles[id].x;
			dst_y = e2->tiles[id].y;
		}
      while(src_x==dst_x && src_y==dst_y && i<niterations);



   	int i_merror = 
			match_get_num_total_errors_in_square(e2, center_x, center_y, radius);

		board_swap_tiles(e2, src_x, src_y, dst_x, dst_y); 
      rotation_auto(e2, src_x, src_y);        
      rotation_auto(e2, dst_x, dst_y);        

   	int f_merror = 
			match_get_num_total_errors_in_square(e2, center_x, center_y, radius);

		if(f_merror==0)
			break;

		if(i_merror > f_merror)
		{
			//printf("swap: (%d,%d) (%d,%d)\n", src_x, src_y, dst_x, dst_y);
			continue;
		}
		else
		{
			// undo
			board_swap_tiles(e2, dst_x, dst_y, src_x, src_y); 
	      rotation_auto(e2, src_x, src_y);        
   	   rotation_auto(e2, dst_x, dst_y);        
		}
	}
   
	return  match_get_num_total_errors(e2);
}
// }}}

// {{{ layer_solver()
int layer_solver(e2_t *e2, int layer, int niterations)
{
	int src_x = 0;
	int src_y = 0;
	int i;
	
	for(i=0; i<niterations; i++)
	{

		switch(random_get(4))
		{
			case 0:
			src_x = random_get(e2->side);
			src_y = layer;
			break;

			case 1:
			src_x = random_get(e2->side);
			src_y = e2->side-1-layer;
			break;

			case 2:
			src_y = random_get(e2->side);
			src_x = layer;
			break;

			case 3:
			src_y = random_get(e2->side);
			src_x = e2->side-layer;
			break;
		}


		if(match_get_num_errors(e2, src_x, src_y)==0)
			continue;

		// find best candidate
		int top_id = match_get_top_id(e2, src_x, src_y);
		int left_id = match_get_left_id(e2, src_x, src_y);
		int right_id = match_get_right_id(e2, src_x, src_y);
		int bottom_id = match_get_bottom_id(e2, src_x, src_y);

		int best_tile_id = 
			match_get_replacement(e2, top_id, left_id, bottom_id, right_id);


		if(best_tile_id)
		{
			int dst_x = e2->tiles[best_tile_id].x;
			int dst_y = e2->tiles[best_tile_id].y;

   		int i_merror = match_get_num_total_errors(e2);

			board_swap_tiles(e2, src_x, src_y, dst_x, dst_y); 
			rotation_auto(e2, src_x, src_y);        
			rotation_auto(e2, dst_x, dst_y);        

			int f_merror = match_get_num_total_errors(e2);

			if(i_merror > f_merror)
				continue;
			else
			{
				// undo
				board_swap_tiles(e2, dst_x, dst_y, src_x, src_y); 
				rotation_auto(e2, src_x, src_y);        
				rotation_auto(e2, dst_x, dst_y);        
			}
		}
	}
   
	return  match_get_num_total_errors(e2);
}
// }}}

// {{{ mix_solver()
// Mezcla 'niterations' piezas al azar
int mix_solver(e2_t *e2, int niterations)
{
	int i;
	for(i=0; i<niterations; i++)
	{
		int src_x = random_get(e2->side);
  		int src_y = random_get(e2->side);
		int dst_x = random_get(e2->side);
  		int dst_y = random_get(e2->side);

		board_swap_tiles(e2, src_x, src_y, dst_x, dst_y); 
		rotation_auto(e2, src_x, src_y);        
		rotation_auto(e2, dst_x, dst_y);        
	}

	return  match_get_num_total_errors(e2);
}
// }}}

// {{{ spiral_solver()
// Recorre el tablero en espiral, desde los bordes hasta el centro.
// Va colocando piezas que encajan hasta que no encuentre ninguna que
// coincida.
int spiral_solver(e2_t *e2)
{
	int i;
	int x;
	int y;

	// only fill the firsts layers
	for(i=0; i<e2->side/2; i++)
	{
      int top = i;
      int bottom = e2->side - i - 1;
      int left = i;
      int right = e2->side - i - 1;

      for(x=left; x<right; x++)
      {
			y=top;
			int top_id = match_get_top_id(e2, x, y);
			int left_id = match_get_left_id(e2, x, y);
			int right_id = -1;
			int bottom_id = -1;

			int best_tile_id = 
				match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

			if(best_tile_id)
			{
				int dst_x = e2->tiles[best_tile_id].x;
				int dst_y = e2->tiles[best_tile_id].y;
				board_swap_tiles(e2, x, y, dst_x, dst_y); 
				rotation_auto(e2, x, y);        
				rotation_auto(e2, dst_x, dst_y);        
			}
      }  

      for(y=top; y<bottom; y++)
      {
			x=right;
			int top_id = match_get_top_id(e2, x, y);
			int left_id = -1;
			int right_id = match_get_right_id(e2, x, y);
			int bottom_id = -1;

			int best_tile_id = 
				match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

			if(best_tile_id)
			{
				int dst_x = e2->tiles[best_tile_id].x;
				int dst_y = e2->tiles[best_tile_id].y;
				board_swap_tiles(e2, x, y, dst_x, dst_y); 
				rotation_auto(e2, x, y);        
				rotation_auto(e2, dst_x, dst_y);        
			}

      }  

      for(x=right; x>left; x--)
      {
			y=bottom;
			int top_id = -1;
			int left_id = -1;
			int right_id = match_get_right_id(e2, x, y);
			int bottom_id = match_get_bottom_id(e2, x, y);

			int best_tile_id = 
				match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

			if(best_tile_id)
			{
				int dst_x = e2->tiles[best_tile_id].x;
				int dst_y = e2->tiles[best_tile_id].y;
				board_swap_tiles(e2, x, y, dst_x, dst_y); 
				rotation_auto(e2, x, y);        
				rotation_auto(e2, dst_x, dst_y);        
			}

      }  

      for(y=bottom; y>top; y--)
      {
			x=left;
			int top_id = -1;
			int left_id = match_get_left_id(e2, x, y);
			int right_id = -1;
			int bottom_id = match_get_bottom_id(e2, x, y);

			int best_tile_id = 
				match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

			if(best_tile_id)
			{
				int dst_x = e2->tiles[best_tile_id].x;
				int dst_y = e2->tiles[best_tile_id].y;
				board_swap_tiles(e2, x, y, dst_x, dst_y); 
				rotation_auto(e2, x, y);        
				rotation_auto(e2, dst_x, dst_y);        
			}

      }

	}

	return  match_get_num_total_errors(e2);
}
// }}}

// {{{ cneighbour_solver()
// Busca una pieza aleatoria e intenta rodearse de veciones bien posicionados
int neighbour_solver(e2_t *e2, int niterations)
{
	int top_id;
	int left_id;
	int right_id;
	int bottom_id;
	int n_x;
	int n_y;
	int id;

	int i;
	for(i=0; i<niterations; i++)
	{

		int src_x = random_get(e2->side);
		int src_y = random_get(e2->side);
		int dst_x;
		int dst_y;

		int tile_top_id = match_get_top_id(e2, src_x, src_y);
		int tile_left_id = match_get_left_id(e2, src_x, src_y);
		int tile_right_id = match_get_right_id(e2, src_x, src_y);
		int tile_bottom_id = match_get_bottom_id(e2, src_x, src_y);


		// top tile
		n_x = e2->tiles[tile_top_id].x;
		n_y = e2->tiles[tile_top_id].y;
		top_id = match_get_top_id(e2, n_x, n_y);
		left_id = match_get_left_id(e2, n_x, n_y);
		right_id = match_get_right_id(e2, n_x, n_y);
		bottom_id = match_get_bottom_id(e2, n_x, n_y);
		id=match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

		if(id)
		{
			dst_x = e2->tiles[id].x;
			dst_y = e2->tiles[id].y;

			int i_merror = match_get_num_total_errors(e2);

			board_swap_tiles(e2, n_x, n_y, dst_x, dst_y); 
			rotation_auto(e2, dst_x, dst_y);        
			rotation_auto(e2, n_x, n_y);        

			int f_merror = match_get_num_total_errors(e2);

			if(i_merror > f_merror);
			else
			{
				// undo
				board_swap_tiles(e2, dst_x, dst_y, n_x, n_y); 
				rotation_auto(e2, dst_x, dst_y);        
				rotation_auto(e2, n_x, n_y);        
			}

		}

		// bottom tile
		n_x = e2->tiles[tile_bottom_id].x;
		n_y = e2->tiles[tile_bottom_id].y;
		top_id = match_get_top_id(e2, n_x, n_y);
		left_id = match_get_left_id(e2, n_x, n_y);
		right_id = match_get_right_id(e2, n_x, n_y);
		bottom_id = match_get_bottom_id(e2, n_x, n_y);
		id=match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

		if(id)
		{
			dst_x = e2->tiles[id].x;
			dst_y = e2->tiles[id].y;

			int i_merror = match_get_num_total_errors(e2);

			board_swap_tiles(e2, n_x, n_y, dst_x, dst_y); 
			rotation_auto(e2, dst_x, dst_y);        
			rotation_auto(e2, n_x, n_y);        

			int f_merror = match_get_num_total_errors(e2);

			if(i_merror > f_merror);
			else
			{
				// undo
				board_swap_tiles(e2, dst_x, dst_y, n_x, n_y); 
				rotation_auto(e2, dst_x, dst_y);        
				rotation_auto(e2, n_x, n_y);        
			}

		}

		// left tile
		n_x = e2->tiles[tile_left_id].x;
		n_y = e2->tiles[tile_left_id].y;
		top_id = match_get_top_id(e2, n_x, n_y);
		left_id = match_get_left_id(e2, n_x, n_y);
		right_id = match_get_right_id(e2, n_x, n_y);
		bottom_id = match_get_bottom_id(e2, n_x, n_y);
		id=match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

		if(id)
		{
			dst_x = e2->tiles[id].x;
			dst_y = e2->tiles[id].y;

			int i_merror = match_get_num_total_errors(e2);

			board_swap_tiles(e2, n_x, n_y, dst_x, dst_y); 
			rotation_auto(e2, dst_x, dst_y);        
			rotation_auto(e2, n_x, n_y);        

			int f_merror = match_get_num_total_errors(e2);

			if(i_merror > f_merror);
			else
			{
				// undo
				board_swap_tiles(e2, dst_x, dst_y, n_x, n_y); 
				rotation_auto(e2, dst_x, dst_y);        
				rotation_auto(e2, n_x, n_y);        
			}

		}

		// right tile
		n_x = e2->tiles[tile_right_id].x;
		n_y = e2->tiles[tile_right_id].y;
		top_id = match_get_top_id(e2, n_x, n_y);
		left_id = match_get_left_id(e2, n_x, n_y);
		right_id = match_get_right_id(e2, n_x, n_y);
		bottom_id = match_get_bottom_id(e2, n_x, n_y);
		id=match_get_replacement(e2, top_id, left_id, bottom_id, right_id);

		if(id)
		{
			dst_x = e2->tiles[id].x;
			dst_y = e2->tiles[id].y;

			int i_merror = match_get_num_total_errors(e2);

			board_swap_tiles(e2, n_x, n_y, dst_x, dst_y); 
			rotation_auto(e2, dst_x, dst_y);        
			rotation_auto(e2, n_x, n_y);        

			int f_merror = match_get_num_total_errors(e2);

			if(i_merror > f_merror);
			else
			{
				// undo
				board_swap_tiles(e2, dst_x, dst_y, n_x, n_y); 
				rotation_auto(e2, dst_x, dst_y);        
				rotation_auto(e2, n_x, n_y);        
			}

		}

	}

	return  match_get_num_total_errors(e2);
}
// }}}

#endif




