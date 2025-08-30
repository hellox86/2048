#include "game.h"

void filling_field_with_numbers(int num_count, uint32_t** f)
{
    if (num_count > 0)
    {
	// simple probabillity
	uint32_t tmp_arr[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

	int min = 0;

	int max = 10;

	int res = min+rand() / (RAND_MAX / (max-min+1) + 1);
	uint32_t conveyor = 2;
	
	if (tmp_arr[res] == 0)
	{
	    conveyor = 4;
	}

	int min_index = 0;
	int max_index = 3;
	int index_col = min_index+rand() / (RAND_MAX/ (max_index-min_index+1) + 1);

	int index_row = min_index+rand() / (RAND_MAX/ (max_index-min_index+1) + 1);

	if (f[index_col][index_row] == 0)
	{
	    f[index_col][index_row] = conveyor;
	}
	else
	   ++num_count;
	filling_field_with_numbers(num_count-1, f);
    }
}


