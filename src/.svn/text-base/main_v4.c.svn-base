
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
   printf("------------------------------------------------------------\n");
   printf("\n\n");
 
   int merror, tmp_merror;
   int src_x, src_y, dst_x, dst_y;
   int max_lock = ntiles*ntiles;   
   int lock=0;
   int nlocks=0;
   int it=0;
   int lmi_n=1;
   int lmi_me=ntiles*4;

   /* solved? */
   while((merror = match_get_num_total_errors(&e2))!=0)
   {
      src_x = random_get(e2.side);
      src_y = random_get(e2.side);

      do { random_get_optimal_xy(&e2, src_x, src_y, &dst_x, &dst_y); }
      //do { random_get_xy_by_groups(&e2, src_x, src_y, &dst_x, &dst_y); }
      while(src_x==dst_x && src_y==dst_y);

      board_swap_tiles(&e2, src_x, src_y, dst_x, dst_y); 
      rotation_auto(&e2, src_x, src_y);        
      rotation_auto(&e2, dst_x, dst_y);        

      tmp_merror = match_get_num_total_errors(&e2);
      if(tmp_merror < merror)
      {
         nlocks++;
         lock=0;
         merror = tmp_merror;
 
         printf("merror: %d, lmi_me: %d, lmi_n: %d, it: %d, nlocks: %d", 
            merror, lmi_me, lmi_n, it, nlocks);

         if(debug)
            printf("\n");
         else
            printf("\r");

     
         if(debug)
            printf("swap src:%d(%d,%d) - dst:%d(%d,%d)\n",  
               board_get(&e2, src_x, src_y), src_x, src_y, 
               board_get(&e2, dst_x, dst_y), dst_x, dst_y);

     
         if(debug)
         {
   			output_board_file(&e2, "/dev/stdout");
            printf("------------------------------------------------------\n");
         }

         if(it%100==0)
         {
   			output_board_file(&e2, "/dev/stdout");
            printf("------------------------------------------------------\n");
         }
      }
      else
      {
         // undo
         board_swap_tiles(&e2, dst_x, dst_y, src_x, src_y);
         rotation_auto(&e2, src_x, src_y);        
         rotation_auto(&e2, dst_x, dst_y);        
         lock++;
      }
   

      // local minimal
      if(lock > max_lock)
      {
         if(merror < lmi_me)
         {
            if(lmi_n>1) lmi_n --;
         }
         else
         {
            if(lmi_n<1) lmi_n ++;
         }

         lmi_me = merror;

         int i;
         for(i=0; i<lmi_n; i++)
         {
            src_x = random_get(e2.side);
            src_y = random_get(e2.side);

            do { random_get_optimal_xy(&e2, src_x, src_y, &dst_x, &dst_y); }
            //do { random_get_xy_by_groups(&e2, src_x, src_y, &dst_x, &dst_y); }
            while(src_x==dst_x && src_y==dst_y);

            board_swap_tiles(&e2, src_x, src_y, dst_x, dst_y); 
            rotation_auto(&e2, src_x, src_y);        
            rotation_auto(&e2, dst_x, dst_y);        
         }

      }



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


