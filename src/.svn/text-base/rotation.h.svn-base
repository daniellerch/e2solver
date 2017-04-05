
#include<e2.h>
#include<match.h>
#include<board.h>

#ifndef __ROTATION_H__
#define __ROTATION_H__

// {{{ rotation_left()
void rotation_left(e2_t *e2, int x, int y)
{
   int id = board_get(e2, x, y);
   int a = e2->tiles[id].top;
   e2->tiles[id].top = e2->tiles[id].right;
   e2->tiles[id].right = e2->tiles[id].bottom;
   e2->tiles[id].bottom = e2->tiles[id].left;
   e2->tiles[id].left = a;
}
// }}}

// {{{ rotation_right()
void rotation_right(e2_t *e2, int x, int y)
{
   int id = board_get(e2, x, y);
   int a = e2->tiles[id].top;
   e2->tiles[id].top = e2->tiles[id].left;
   e2->tiles[id].left = e2->tiles[id].bottom;
   e2->tiles[id].bottom = e2->tiles[id].right;
   e2->tiles[id].right = a;
}
// }}}

// {{{ rotation_auto()
void rotation_auto(e2_t *e2, int x, int y)
{
	// force 139(2) to (7,8) 
	if(e2->ntiles == 256)
	{
		if(x==7 && y==8)
			return;
	}




   // TODO: dar mas importancia a los laterales y esquinas

   int nerrors=4;
   int tmperrors;
   int rotation=4;

   rotation_right(e2, x, y);
   tmperrors = match_get_num_errors(e2, x, y);
   if(tmperrors<nerrors)
   {
      nerrors = tmperrors;
      rotation=1;
   }

   rotation_right(e2, x, y);
   tmperrors = match_get_num_errors(e2, x, y);
   if(tmperrors<nerrors)
   {
      nerrors = tmperrors;
      rotation=2;
   }

   rotation_right(e2, x, y);
   tmperrors = match_get_num_errors(e2, x, y);
   if(tmperrors<nerrors)
   {
      nerrors = tmperrors;
      rotation=3;
   }

   rotation_right(e2, x, y);
   tmperrors = match_get_num_errors(e2, x, y);
   if(tmperrors<nerrors)
   {
      nerrors = tmperrors;
      rotation=4;
   }


   switch(rotation)
   {
      case 1:
      rotation_right(e2, x, y);
      break;

      case 2:
      rotation_right(e2, x, y);
      rotation_right(e2, x, y);
      break;

      case 3:
      rotation_right(e2, x, y);
      rotation_right(e2, x, y);
      rotation_right(e2, x, y);
      break;
   }
}
// }}}

#endif



