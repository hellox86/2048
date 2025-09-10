#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_W 4
#define FIELD_H 4

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

void prepare_field(int f[4][4])
{
    probability(f, 2);
}
void reverse_field(int f[4][4], int start, int end)
{
    int tmp_start, tmp_end;
    tmp_start = start;
    tmp_end = end;
    
    for (int i = 0; i < 4; i++)
    {
	while (start < end)
	{
	    int tmp = f[i][start];

	    f[i][start] = f[i][end];

	    f[i][end] = tmp;
	    start++;

	    end--;
	}
	
	start = tmp_start;
	end = tmp_end;
    }
}

void move_left(int f[4][4], int r)
{
    r %= FIELD_W;
    reverse_field(f, 0, r-1);
    reverse_field(f, r, FIELD_W-1);
    reverse_field(f, 0, FIELD_W-1);
}

void print_field(void)
{
    for (int i = 0; i < 4; i++)
    {
	printf("\n");
	for (int j = 0; j < 4; j++)
	{	    
	    printf("%d", field[i][j]);   	   
	}
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    prepare_field(field); 
    print_field();
    move_left(field, 1);
    print_field();
    return 0;
}
