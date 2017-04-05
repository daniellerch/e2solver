
#ifndef __ENERGY_H__
#define __ENERGY_H__

#include <match.h>
#include <board.h>

// {{{ energy_single() 
int energy_single(e2_t *e2)
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

// {{{ energy_count_nm_sides(): count not matched sides
int energy_count_nm_sides(e2_t *e2, int side)
{
   int lx, ly;
   int cnt=0;

   for(ly=0; ly<e2->side; ly++)
   {
      for(lx=0; lx<e2->side; lx++)
      {
         int lid = board_get(e2, lx, ly);

         if(e2->tiles[lid].top==side && !match_top(e2, lx, ly)) cnt++;
         if(e2->tiles[lid].left==side && !match_left(e2, lx, ly)) cnt++;
         if(e2->tiles[lid].bottom==side && !match_bottom(e2, lx, ly)) cnt++;
         if(e2->tiles[lid].right==side && !match_right(e2, lx, ly)) cnt++;
      }
   }

   return cnt;
}
// }}}

// {{{ energy_global()
int energy_global(e2_t *e2)
{
   
   // Not matched sides.
   int nm_cnt = 0;
   int side;
   int cnt=1;

   for(side=1;side<256;side++) // TODO: arreglame
   {
      cnt = energy_count_nm_sides(e2, side);
      nm_cnt += cnt;
   }

   return nm_cnt;
}
// }}}




#endif



