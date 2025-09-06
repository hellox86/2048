#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int field[4][4];
    
int random_in_range(int min, int max)
{
    int rand_index = min+rand()/(RAND_MAX/(max+min+1)+1);
    return rand_index;
}

void probability(int f[4][4], int times)
{
    int output = 2;    
    int rand_col, rand_row, rand_index;
    for (int i = 0; i < times; i++)
    {	
	rand_index = random_in_range(0, 9);
	
	if (rand_index != 9)
	{
	    output = 2;
	}
	else
	{
	    output = 4;
	}
RND:
	rand_row = random_in_range(0, 3);
	rand_col = random_in_range(0, 3);

	if (f[rand_row][rand_col] != 0) goto RND; 
	f[rand_row][rand_col] = output;
    }
}

struct Pos
{
    int x, y;
};

struct Pos life_cells[16];

int get_life_cells(int f[4][4])
{
    int life_cells_count = 0;
    
    for (int y = 0; y < 4; y++)
    {
	for (int x = 0; x < 4; x++)
	{
	    if (f[y][x] != 0)
	    {
		life_cells[life_cells_count].x = x;
		life_cells[life_cells_count].y = y;
		++life_cells_count;
	    }
	}
    }
    return life_cells_count;
}

void prepare_field(int f[4][4])
{
    probability(f, 2);
}
void reverse_field(int f[4][4])
{
    
}
void move_left(int f[4][4])
{

}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    prepare_field(field); 
    for (int i = 0; i < 4; i++)
    {
	printf("\n");
	for (int j = 0; j < 4; j++)
	{	    
	    printf("%d", field[i][j]);   	   
	}
    }

    return 0;
}
