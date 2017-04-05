
#ifndef __F_H__
#define __F_H__


// {{{ F(): F function
void  F(e2_t *e2, int x, int y, int *x_result, int *y_result, int *rot_result)
{
   int lx, ly;
   int top_cnt, right_cnt, bottom_cnt, left_cnt;
   int board_top_f, board_right_f, board_bottom_f, board_left_f;
   int board_top_r, board_right_r, board_bottom_r, board_left_r;

   int id = board_get(e2, x, y);
   int top = e2->tiles[id].top;
   int right = e2->tiles[id].right;
   int bottom = e2->tiles[id].bottom;
   int left = e2->tiles[id].left;
   
  
   // TODO: implementar como caso especial los laterales

   // Calcular la fuerza ejercida hacia arriba y con que rotacion
   top_cnt = right_cnt = bottom_cnt = left_cnt = 0;
   for(ly=0; ly<y; ly++)
   {
      for(lx=0; lx<e2->side; lx++)
      {
         int lid = board_get(e2, lx, ly);
         if(e2->tiles[lid].top == top) top_cnt++;
         if(e2->tiles[lid].right == right) right_cnt++;
         if(e2->tiles[lid].bottom == bottom) bottom_cnt++;
         if(e2->tiles[lid].left == left) left_cnt++;
      }
   }

   board_top_f = top_cnt + right_cnt + bottom_cnt + left_cnt;

   if(top_cnt>right_cnt && top_cnt>bottom_cnt && top_cnt>left_cnt)
      board_top_r = 0;
   else if(right_cnt>top_cnt && right_cnt>bottom_cnt && right_cnt>left_cnt)
      board_top_r = 3;
   else if(bottom_cnt>right_cnt && bottom_cnt>top_cnt && bottom_cnt>left_cnt)
      board_top_r = 2;
   else if(left_cnt>top_cnt && left_cnt>bottom_cnt && left_cnt>right_cnt)
      board_top_r = 1;
   else
      board_top_r = 0;


   // Calcular la fuerza ejercida hacia abajo y con que rotacion
   top_cnt = right_cnt = bottom_cnt = left_cnt = 0;
   for(ly=y+1; ly<e2->side; ly++)
   {
      for(lx=0; lx<e2->side; lx++)
      {
         int lid = board_get(e2, lx, ly);
         if(e2->tiles[lid].top == top) top_cnt++;
         if(e2->tiles[lid].right == right) right_cnt++;
         if(e2->tiles[lid].bottom == bottom) bottom_cnt++;
         if(e2->tiles[lid].left == left) left_cnt++;
      }
   }

   board_bottom_f = top_cnt + right_cnt + bottom_cnt + left_cnt;

   if(top_cnt>right_cnt && top_cnt>bottom_cnt && top_cnt>left_cnt)
      board_bottom_r = 2;
   else if(right_cnt>top_cnt && right_cnt>bottom_cnt && right_cnt>left_cnt)
      board_bottom_r = 1;
   else if(bottom_cnt>right_cnt && bottom_cnt>top_cnt && bottom_cnt>left_cnt)
      board_bottom_r = 0;
   else if(left_cnt>top_cnt && left_cnt>bottom_cnt && left_cnt>right_cnt)
      board_bottom_r = 3;
   else
      board_bottom_r = 0;


   // Calcular la fuerza ejercida hacia la derecha y con que rotacion
   top_cnt = right_cnt = bottom_cnt = left_cnt = 0;
   for(ly=0; ly<e2->side; ly++)
   {
      for(lx=x+1; lx<e2->side; lx++)
      {
         int lid = board_get(e2, lx, ly);
         if(e2->tiles[lid].top == top) top_cnt++;
         if(e2->tiles[lid].right == right) right_cnt++;
         if(e2->tiles[lid].bottom == bottom) bottom_cnt++;
         if(e2->tiles[lid].left == left) left_cnt++;
      }
   }

   board_right_f = top_cnt + right_cnt + bottom_cnt + left_cnt;

   if(top_cnt>right_cnt && top_cnt>bottom_cnt && top_cnt>left_cnt)
      board_right_r = 1;
   else if(right_cnt>top_cnt && right_cnt>bottom_cnt && right_cnt>left_cnt)
      board_right_r = 0;
   else if(bottom_cnt>right_cnt && bottom_cnt>top_cnt && bottom_cnt>left_cnt)
      board_right_r = 3;
   else if(left_cnt>top_cnt && left_cnt>bottom_cnt && left_cnt>right_cnt)
      board_right_r = 2;
   else
      board_right_r = 0;


   // Calcular la fuerza ejercida hacia la izquierda y con que rotacion
   top_cnt = right_cnt = bottom_cnt = left_cnt = 0;
   for(ly=0; ly<e2->side; ly++)
   {
      for(lx=0; lx<x; lx++)
      {
         int lid = board_get(e2, lx, ly);
         if(e2->tiles[lid].top == top) top_cnt++;
         if(e2->tiles[lid].right == right) right_cnt++;
         if(e2->tiles[lid].bottom == bottom) bottom_cnt++;
         if(e2->tiles[lid].left == left) left_cnt++;
      }
   }

   board_left_f = top_cnt + right_cnt + bottom_cnt + left_cnt;

   if(top_cnt>right_cnt && top_cnt>bottom_cnt && top_cnt>left_cnt)
      board_left_r = 3;
   else if(right_cnt>top_cnt && right_cnt>bottom_cnt && right_cnt>left_cnt)
      board_left_r = 2;
   else if(bottom_cnt>right_cnt && bottom_cnt>top_cnt && bottom_cnt>left_cnt)
      board_left_r = 1;
   else if(left_cnt>top_cnt && left_cnt>bottom_cnt && left_cnt>right_cnt)
      board_left_r = 0;
   else
      board_left_r = 0;



   // New coords and rotations
   if(board_top_f>=board_right_f && 
      board_top_f>=board_left_f  && 
      board_top_f>=board_bottom_f)
   {
      *x_result = x;
      *y_result = y-1;
      *rot_result = board_top_r;
   }
   
   if(board_right_f>=board_top_f && 
      board_right_f>=board_left_f  && 
      board_right_f>=board_bottom_f)
   {
      *x_result = x+1;
      *y_result = y;
      *rot_result = board_right_r;
   }
 
   if(board_bottom_f>=board_top_f && 
      board_bottom_f>=board_left_f  && 
      board_bottom_f>=board_right_f)
   {
      *x_result = x;
      *y_result = y+1;
      *rot_result = board_bottom_r;
   }
  
   if(board_left_f>=board_top_f && 
      board_left_f>=board_bottom_f  && 
      board_left_f>=board_right_f)
   {
      *x_result = x-1;
      *y_result = y;
      *rot_result = board_left_r;
   }

   
}
// }}}




#endif




