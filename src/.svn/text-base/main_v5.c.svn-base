
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
#include<algo.h>


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


	/* indexation of tiles */
	e2_indexation(&e2);


   /* print data structures */
   output_board_file(&e2, "/dev/stdout");
   printf("------------------------------------------------------------\n");
   printf("\n\n");
 
   int merror, best_merror=10000;
   int it=0;
	int nlocks=0;
	int cx=7;
	int cy=8;
	
   /* solved? */
   while((merror = match_get_num_total_errors(&e2))!=0)
   {
		if(merror < best_merror)
		{
			nlocks=0;
			best_merror = merror;
   		output_board_file(&e2, "/dev/stdout");

			puts("\n\n");
      	printf("best merror: %d, it: %d\n", best_merror, it);
   		output_board_file(&e2, "/dev/stdout");
			puts("\n\n");
      	printf(" merror: %d (best: %d), it: %d \r", merror, best_merror, it);
		}
		else
			nlocks++;
	
		merror = layer_solver(&e2, 0, 10);
		printf("algo: LYS, merror: %d (best: %d), it: %d (locks: %d) \r", 
				merror, best_merror, it, nlocks);

		merror = random_optimal_solver(&e2, 100);
		printf("algo: ROS, merror: %d (best: %d), it: %d (locks: %d) \r", 
				merror, best_merror, it, nlocks);

		merror = random_solver(&e2, 100);
      printf("algo: RNS, merror: %d (best: %d), it: %d (locks: %d) \r", 
			merror, best_merror, it, nlocks);

		merror = random_square_solver(&e2, 2, 10);
		printf("algo: RSS, merror: %d (best: %d), it: %d (locks: %d) \r", 
				merror, best_merror, it, nlocks);

		merror = square_solver(&e2, 7, 8, 3, 10);
		printf("algo: SQS, merror: %d (best: %d), it: %d (locks: %d) \r", 
				merror, best_merror, it, nlocks);

		merror = neighbour_solver(&e2, 10);
		printf("algo: SPS, merror: %d (best: %d), it: %d (locks: %d) \r", 
				merror, best_merror, it, nlocks);


		if(nlocks%5000==0)	
		{
			merror = mix_solver(&e2, 50);
      	printf("algo: MXS, merror: %d (best: %d), it: %d (locks: %d) \r", 
				merror, best_merror, it, nlocks);
		}



		//merror = spiral_solver(&e2);
      //printf("algo: SPS, merror: %d (best: %d), it: %d (locks: %d) \r", 
		//	merror, best_merror, it, nlocks);

      it++;
   }
   
   printf("\n\n");
   printf("------------------------------------------------------------\n");
   printf("Solved: \n");
   printf("------------------------------------------------------------\n");
   output_board_file(&e2, "/dev/stdout");


  
   /* free data sctructures */
   free(e2.board);
   free(e2.tiles);

   return 0;
}


