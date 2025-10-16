#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int field[4][4];

size_t size_field = sizeof(int)*4*4;

int random_in_range(int min, int max)
{
    int rand_index = ((double)rand() / RAND_MAX)*(max-min+1)+min;
    return rand_index;
}

void generate_num(int f[4][4], int times)
{
    int output = 2;   
    int rand_col, rand_row, rand_index;

    for (int i = 0; i < times; i++)
    {	
	rand_index = random_in_range(0, 9);
	
	if (rand_index != 9) output = 2;

	else output = 4;
	
	do
	{
		rand_row = random_in_range(0, 3);
		rand_col = random_in_range(0, 3);
	} while (f[rand_row][rand_col] != 0); 
	f[rand_row][rand_col] = output;
    }
}

void prepare_field(int f[4][4])
{
    generate_num(f, 2);
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

void print_field(int f[4][4])
{
    for (int i = 0; i < 4; i++)
    {
	printf("\n");
	for (int j = 0; j < 4; j++)
	{	    
	    printf("%d", f[i][j]);   	   
	}
    }
    printf("\n");
}

void rotate_matrix(int f[4][4])
{
    int tmp[4][4] = {0};
    int n = 4;
    
    for (int i = 0; i < n; i++)
    {
	for (int j = 0; j < n; j++)
	{
	    tmp[i][j] = f[n-i-1][n-j-1];
	}
    }
    memcpy(f, tmp, size_field);
}
void rotate_matrix_90_ccw(int f[4][4])
{
    int tmp[4][4] = {0};
    int n = 4;
    
    for (int i = 0; i < n; i++)
    {
	for (int j = 0; j < n; j++)
	{
	    tmp[n-j-1][i] = f[i][j];
	}
    }
    memcpy(f, tmp, size_field);
}

void rotate_matrix_90_cw(int f[4][4])
{
    int tmp[4][4];
    int n = 4;
    
    for (int i = 0; i < n; i++)
    {
	for (int j = 0; j < n; j++)
	{
	    tmp[j][n-i-1] = f[i][j];
	}
    }
    memcpy(f, tmp, size_field);
}
void move_left(int f[4][4])
{
    // left shift, merge if exists pairs, and left shift one more time   
    int arr[4][4] = {0};
    int element_counter = 0;
    
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    if (f[i][j] != 0)
	    {
		arr[i][element_counter] = f[i][j];
		element_counter++;
	    }
	}
	element_counter = 0;
    }
    int result[4][4] = {0};
    
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4;)
	{
	    if (j+1 < 4 && arr[i][j] == arr[i][j+1])
	    {
		result[i][element_counter] = arr[i][j]*2;
		j+=2;
	    }
	    else
	    {
		result[i][element_counter] = arr[i][j];
		j++;
	    }
	    element_counter++;
	}
	element_counter = 0;
    }    
    memcpy(f, result, size_field);
}

void move_right(int f[4][4])
{
    rotate_matrix(f);
    move_left(f);
    rotate_matrix(f);
}

void move_down(int f[4][4])
{
    rotate_matrix_90_cw(f);

    move_left(f);
    rotate_matrix_90_ccw(f);
}

void move_up(int f[4][4])
{
    rotate_matrix_90_ccw(f);

    move_left(f);
    rotate_matrix_90_cw(f);       
}

int main(void)
{
    srand(time(NULL));
    prepare_field(field);
    print_field(field);
    move_up(field);
    print_field(field);

    return 0;
}
