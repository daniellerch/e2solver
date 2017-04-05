
#include<tile.h>

#ifndef _E2_H__
#define _E2_H__

static int debug = 0;

#define MAX_SIDES 32
#define MAX_TILES 256

typedef struct
{
   int *board;
   int side;
   int ntiles;
   tile_t *tiles;
}
e2_t;

static int t1cf[MAX_SIDES][MAX_TILES+1];
static int t2cf[MAX_SIDES][MAX_SIDES][MAX_TILES+1];
static int t2of[MAX_SIDES][MAX_SIDES][MAX_TILES+1];
static int t3cf[MAX_SIDES][MAX_SIDES][MAX_SIDES][MAX_TILES+1];
static int t4cf[MAX_SIDES][MAX_SIDES][MAX_SIDES][MAX_SIDES][MAX_TILES+1];


// {{{ e2_indexation()

#define __set_t1cf(id_side, id_tile) \
{ \
	int k=0; \
	while(k<MAX_TILES) \
		if(t1cf[id_side][k]==0) break; \
		else k++; \
	t1cf[id_side][k]=id_tile; \
}

#define __set_t2cf(id_side_1, id_side_2, id_tile) \
{ \
	int k=0; \
	while(k<MAX_TILES) \
		if(t2cf[id_side_1][id_side_2][k]==0) break; \
		else k++; \
	t2cf[id_side_1][id_side_2][k]=id_tile; \
}

#define __set_t2of(id_side_1, id_side_2, id_tile) \
{ \
	int k=0; \
	while(k<MAX_TILES) \
		if(t2of[id_side_1][id_side_2][k]==0) break; \
		else k++; \
	t2of[id_side_1][id_side_2][k]=id_tile; \
}

#define __set_t3cf(id_side_1, id_side_2, id_side_3, id_tile) \
{ \
	int k=0; \
	while(k<MAX_TILES) \
		if(t3cf[id_side_1][id_side_2][id_side_3][k]==0) break; \
		else k++; \
	t3cf[id_side_1][id_side_2][id_side_3][k]=id_tile; \
}

#define __set_t4cf(id_side_1, id_side_2, id_side_3, id_side_4, id_tile) \
{ \
	int k=0; \
	while(k<MAX_TILES) \
		if(t4cf[id_side_1][id_side_2][id_side_3][id_side_4][k]==0) break; \
		else k++; \
	t4cf[id_side_1][id_side_2][id_side_3][id_side_4][k]=id_tile; \
}



void e2_indexation(e2_t *e2)
{
	int i;

	for(i=1; i<=e2->ntiles; i++)
	{
		printf("e2_indexation: %d\n", i);

		// 1-face
		__set_t1cf(e2->tiles[i].top, i);
		printf("idx[%d]=%d\n", 0, t1cf[i][0]); \
		__set_t1cf(e2->tiles[i].left, i);
		__set_t1cf(e2->tiles[i].right, i);
		__set_t1cf(e2->tiles[i].bottom, i);

		// 2-faces
		__set_t2cf(e2->tiles[i].top, e2->tiles[i].left, i);
		__set_t2cf(e2->tiles[i].left, e2->tiles[i].bottom, i);
		__set_t2cf(e2->tiles[i].bottom, e2->tiles[i].right, i);
		__set_t2cf(e2->tiles[i].right, e2->tiles[i].top, i);

		// 2-faces (oposite)
		__set_t2of(e2->tiles[i].top, e2->tiles[i].bottom, i);
		__set_t2of(e2->tiles[i].bottom, e2->tiles[i].top, i);
		__set_t2of(e2->tiles[i].left, e2->tiles[i].right, i);
		__set_t2of(e2->tiles[i].right, e2->tiles[i].left, i);

		// 3-faces
		__set_t3cf(e2->tiles[i].top, e2->tiles[i].left, e2->tiles[i].bottom, i);
		__set_t3cf(e2->tiles[i].left, e2->tiles[i].bottom, e2->tiles[i].right, i);
		__set_t3cf(e2->tiles[i].bottom, e2->tiles[i].right, e2->tiles[i].top, i);
		__set_t3cf(e2->tiles[i].right, e2->tiles[i].top, e2->tiles[i].left, i);

		// 4-faces
		__set_t4cf(e2->tiles[i].top, e2->tiles[i].left, 
                 e2->tiles[i].bottom, e2->tiles[i].right, i);
		__set_t4cf(e2->tiles[i].left, e2->tiles[i].bottom, 
                 e2->tiles[i].right, e2->tiles[i].top, i);
		__set_t4cf(e2->tiles[i].bottom, e2->tiles[i].right, 
                 e2->tiles[i].top, e2->tiles[i].left, i);
		__set_t4cf(e2->tiles[i].right, e2->tiles[i].top, 
                 e2->tiles[i].left, e2->tiles[i].bottom, i);

	}
	puts("\ncompleted");

	/*
	int j, t;
	for(j=0; j<MAX_SIDES; j++)
		for(t=0; t<MAX_TILES; t++)
			printf("%d %d = %d\n", j, t, t1cf[j][t]);
	*/

}
// }}}


#endif

