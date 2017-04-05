
#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include<match.h>

// {{{ output_board()
void output_board(e2_t *e2)
{
   int i;
   for(i=0; i<e2->ntiles; i++)
   {
      printf("%d\t", e2->board[i]); 
      if(i%e2->side==e2->side-1)
         printf("\n");
   }
   printf("\n");
}
// }}}

// {{{ output_board_file()
void output_board_file(e2_t *e2, const char* file)
{
   int x;
   int y;

	FILE *f = fopen(file, "w+");
	if(!f)
		return;

   for(y=0; y<e2->side; y++)
   {
      for(x=0; x<e2->side; x++)
      {
         int id = board_get(e2, x, y);
         
         if(!match_top(e2, x, y))
            fprintf(f, "  / \e[31;1m%.3d\e[m \\    ", e2->tiles[id].top);
         else
            fprintf(f, "  / %.3d \\    ", e2->tiles[id].top);
      }
      fprintf(f, "\n");

      for(x=0; x<e2->side; x++)
      {
         int id = board_get(e2, x, y);

         if(!match_left(e2, x, y))
            fprintf(f, "\e[31;1m%.3d\e[m", e2->tiles[id].left);
         else
            fprintf(f, "%.3d", e2->tiles[id].left);

			if(id==139)
         	fprintf(f, " \e[34;1m%.3d\e[m ", id);
			else
         	fprintf(f, " \e[33;1m%.3d\e[m ", id);

         if(!match_right(e2, x, y))
            fprintf(f, "\e[31;1m%.3d\e[m  ", e2->tiles[id].right);
         else
            fprintf(f, "%.3d  ", e2->tiles[id].right);
      }
      fprintf(f, "\n");

      for(x=0; x<e2->side; x++)
      {
         int id = board_get(e2, x, y);
         if(!match_bottom(e2, x, y))
            fprintf(f, "  \\ \e[31;1m%.3d\e[m /    ", e2->tiles[id].bottom);
         else
            fprintf(f, "  \\ %.3d /    ", e2->tiles[id].bottom);
      }
      fprintf(f, "\n");
   }
   fprintf(f, "\n");
   fprintf(f, "\n");
	fclose(f);
}
// }}}

// {{{ output_tiles()
void output_tiles(e2_t *e2)
{
   int i;
   for(i=1; i<=e2->ntiles; i++)
   {
      printf("%d(%d,%d,%d,%d)\n", 
      e2->tiles[i].id, e2->tiles[i].top, e2->tiles[i].right, 
      e2->tiles[i].bottom, e2->tiles[i].left);
   }
}
// }}}


#endif

