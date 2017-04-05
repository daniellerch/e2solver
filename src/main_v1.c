
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include<e2.h>
#include<tile.h>
#include<board.h>
#include<input.h>
#include<output.h>
#include<match.h>
#include<random.h>
#include<rotation.h>
#include<f.h>




int main(int argc, char *argv[])
{
   if(argc<2)
   {
      printf("Usage: %s [puzzle file] \n\n", argv[0]);
      return 0;
   }  

   if(argc==3 && strcmp(argv[2], "debug")==0)
      debug=1;


   /* seed random number generator */
   random_seed();

   /* read num tiles */
   int ntiles = input_get_ntiles(argv[1]);
   if(ntiles==0)
   {
      printf("input file error: %s\n", argv[1]);
      return 0;
   }

   

   /* create data structures */
   e2_t e2;
   e2.board = malloc(ntiles*sizeof(int));
   e2.tiles = malloc((ntiles+1)*sizeof(tile_t)); // ignore zero position
   e2.ntiles = ntiles;
   e2.side = sqrt(ntiles);


   printf("ntiles: %d\n", e2.ntiles);
   printf("side: %d\n", e2.side);


   /* set data */
   input_read_tiles(&e2, argv[1]);
   board_set_tiles(&e2);

   /* print data structures */
   //output_tiles(&e2);
   output_board_file(&e2, "/dev/stdout");
 

   int merror;
   int x, y, i;
   int x_result, y_result, rot_result;
   
   /* solved? */
   while((merror = match_get_num_total_errors(&e2))!=0)
   {
      printf("merror: %d\n", merror);

      x = random_get(e2.side);
      y = random_get(e2.side);
      F(&e2, x, y, &x_result, &y_result, &rot_result);
      board_swap_tiles(&e2, x, y, x_result, y_result);
        
      for(i=0; i<rot_result; i++)
         rotation_right(&e2, x_result, y_result);

      printf("swap (%d,%d) - (%d,%d)r%d\n", 
         x, y, x_result, y_result, rot_result);
 
   	output_board_file(&e2, "/dev/stdout");
      printf("------------------------------------------------------------\n");
   }
   
   printf("------------------------------------------------------------\n");
   printf("Solved: \n");
   printf("------------------------------------------------------------\n");
   output_board_file(&e2, "/dev/stdout");


  
   /* free data sctructures */
   free(e2.board);
   free(e2.tiles);
   

   return 0;
}


